/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header$ */
/*  P R O T O T Y P E   F I D D L I N G  */

#include	"lint.h"
#include	"debug.h"
#include	"idfsize.h"
#include	"nparams.h"
#include	"botch_free.h"
#include	<alloc.h>
#include	"Lpars.h"
#include	"level.h"
#include	"arith.h"
#include	"align.h"
#include	"stack.h"
#include	"idf.h"
#include	"def.h"
#include	"type.h"
#include	"struct.h"
#include	"label.h"
#include	"expr.h"
#include	"declar.h"
#include	"decspecs.h"
#include	"proto.h"
#include	"assert.h"

extern char options[];

add_proto(pl, ds, dc, level)
	struct proto *pl;
	struct decspecs *ds;
	struct declarator *dc;
	int level;
{
	/*	The full typed identifier or abstract type, described
		by the structures decspecs and declarator are turned
		a into parameter type list structure.
		The parameters will be declared at level L_FORMAL2,
		later on it's decided whether they were prototypes
		or actual declarations.
	*/
	register struct idf *idf;
	register struct def *def = (struct def *)0;
	register int sc = ds->ds_sc;
	register struct type *type;
	char formal_array = 0;

	ASSERT(ds->ds_type != (struct type *)0);

	pl->pl_flag = FORMAL;
	if ((idf = dc->dc_idf) != (struct idf *)0)
		def = idf->id_def;
	type = declare_type(ds->ds_type, dc);
	if (type->tp_size < (arith)0 && actual_declaration(sc, type)) {
		extern char *symbol2str();
		error("unknown %s-type", symbol2str(type->tp_fund));
	} else if (type->tp_size == 0) {
		pl->pl_flag = VOID;
		if (idf != (struct idf *)0)
			strict("illegal use of void in argument list");
	}

	/*	Perform some special conversions for parameters.
	*/
	if (type->tp_fund == FUNCTION) {
		if (type->tp_proto)
			remove_proto_idfs(type->tp_proto);
		type = construct_type(POINTER, type, 0, (arith) 0, NO_PROTO);
	} else if (type->tp_fund == ARRAY) {
		type = construct_type(POINTER, type, 0, (arith) 0, NO_PROTO);
		formal_array = 1;
	}

	/*	According to the standard we should ignore the storage
		class of a parameter, unless it's part of a function
		definition.
		However, in the routine declare_protos we don't know decspecs,
		and therefore we can't complain up there. So we build up the
		storage class, and keep quiet until we reach declare_protos.
	*/
	sc = (ds->ds_sc_given && ds->ds_sc != REGISTER) ?
				0 : sc == 0 ? FORMAL : REGISTER;

	if (def && (def->df_level == level || def->df_level < L_PROTO)) {
		/* redeclaration at the same level */
		error("parameter %s redeclared", idf->id_text);
	} else if (idf != (struct idf *)0) {
		/*	New definition, redefinition hides earlier one
		*/
		register struct def *newdef = new_def();
		
		newdef->next = def;
		newdef->df_level = level;
		newdef->df_sc = sc;
		newdef->df_type = type;
		newdef->df_formal_array = formal_array;
		newdef->df_file = idf->id_file;
		newdef->df_line = idf->id_line;
#ifdef LINT
		newdef->df_set = (type->tp_fund == ARRAY);
		newdef->df_firstbrace = 0;
#endif
		/*	We can't put the idf onto the stack, since these kinds
			of declaration may occurs at any level, and the idf
			does not necessarily go at this level. E.g.

			f() {
			...
				{ int func(int a, int b);
				...

			The idf's a and b declared in the prototype declaration
			do not go at any level, they are simply ignored.
			However, in

			f(int a, int b) {
			...

			They should go at level L_FORMAL2. But at this stage
			we don't know whether we have a prototype or function
			definition. So, this process is postponed.
		*/
		idf->id_def = newdef;
		update_ahead(idf);
	}

	pl->pl_idf = idf;
	pl->pl_type = type;
}

declare_protos(idf, dc)
	register struct idf *idf;
	register struct declarator *dc;
{
	/*	At this points we know that the idf's in protolist are formal
		parameters. So it's time to declare them at level L_FORMAL2.
	*/
	struct stack_level *stl = stack_level_of(L_FORMAL1);
	register struct decl_unary *du;
	register struct type *type;
	register struct proto *pl;
	register struct def *def;

#ifdef	DEBUG
	if (options['t'])
		dumpidftab("start declare_protos", 0);
#endif	DEBUG
	du = dc->dc_decl_unary;
	while (du && du->du_fund != FUNCTION)
		du = du->next;
	pl = du ? du->du_proto : NO_PROTO;
	if (pl) {
		idf->id_proto = 0;
		do {
			type = pl->pl_type;

			/* `...' only for type checking */
			if (pl->pl_flag == ELLIPSIS) {
				pl = pl->next;
				continue;
			}

			/* special case: int f(void) { ; } */
			if (type->tp_fund == VOID)
				break;

			if (!pl->pl_idf || !(def = pl->pl_idf->id_def)) {
				error("no parameter supplied");
				pl = pl->next;
				continue;
			}

			/*	Postponed storage class checking.
			*/
			if (def->df_sc == 0)
				error("illegal storage class in parameter declaration");

			def->df_level = L_FORMAL2;
			stack_idf(pl->pl_idf, stl);
			pl = pl->next;
		} while (pl);
	}
#ifdef	DEBUG
	if (options['t'])
		dumpidftab("end declare_protos", 0);
#endif	DEBUG
}


def_proto(dc)
	register struct declarator *dc;
{
	/*	Prototype declarations may have arguments, but the idf's
		in the parameter type list can be ignored.
	*/
	register struct decl_unary *du = dc->dc_decl_unary;

	while (du) {
		if (du->du_fund == FUNCTION)
			remove_proto_idfs(du->du_proto);
		du = du->next;
	}
}

update_proto(tp, otp)
	register struct type *tp, *otp;
{
	/*	This routine performs the proto type updates.
		Consider the following code:

		int f(double g());
		int f(double g(int f(), int));
		int f(double g(int f(long double), int));

		The most accurate definition is the third line.
		This routine will silently update all lists,
		and removes the redundant occupied space.
	*/
	register struct proto *pl, *opl;

#if 0
	/*	THE FOLLOWING APPROACH IS PRESUMABLY WRONG.
		THE ONLY THING THIS CODE IS SUPPOSED TO DO
		IS TO UPDATE THE PROTOTYPELISTS, I HAVEN'T
		EVEN CONSIDERED THE DISPOSAL OF REDUNDANT
		SPACE !!.
		THIS ROUTINE DUMPS CORE. SORRY, BUT IT'S 10
		P.M. AND I'M SICK AN TIRED OF THIS PROBLEM.
	*/
	print("Entering\n");
	if (tp == otp) {
		print("OOPS - they are equal\n");
		return;
	}
	if (!tp || !otp) {
		print("OOPS - Nil pointers tp=@%o otp=@%o\n", tp, otp);
		return;
	}

	print("Search function\n");
	while (tp && tp->tp_fund != FUNCTION) {
		if (!(tp->tp_up)) {
			print("TP is NIL\n");
			return;
		}
		tp = tp->tp_up;
		if (!(otp->tp_up)) {
			print("OTP is NIL\n");
			return;
		}
		otp = otp->tp_up;
		if (!tp) return;
	}

	print("Do it\n");
	pl = tp->tp_proto;
	opl = otp->tp_proto;
	if (pl && opl) {
		/* both have prototypes */
		print("Both have proto type\n");
		print("New proto type list\n");
		dump_proto(pl);
		print("Old proto type list\n");
		dump_proto(opl);
		while (pl && opl) {
			update_proto(pl->pl_type, opl->pl_type);
			pl = pl->next;
			opl = pl->next;
		}
		/*free_proto_list(tp->tp_proto);*/
		tp->tp_proto = otp->tp_proto;
	} else if (opl) {
		/* old decl has type */
		print("Old decl has type\n");
		print("Old proto type list\n");
		dump_proto(opl);
		tp->tp_proto = opl;
	} else if (pl) {
		/* new decl has type */
		print("New decl has type\n");
		print("New proto type list\n");
		dump_proto(pl);
		print("otp = @%o\n", otp);
		otp->tp_proto = pl;
		print("after assign\n");
	} else
		print("none has prototype\n");

	print("Going for another top type\n");
	update_proto(tp->tp_up, otp->tp_up);
# endif
}

free_proto_list(pl)
	register struct proto *pl;
{
	while (pl) {
		register struct proto *tmp = pl->next;
		free_proto(pl);
		pl = tmp;
	}
}

remove_proto_idfs(pl)
	register struct proto *pl;
{
	/*	Remove all the identifier definitions from the
		prototype list. Keep in account the recursive
		function definitions.
	*/
	register struct def *def;

	while (pl) {
		if (pl->pl_idf) {
#ifdef DEBUG
			if (options['t'])
				print("Removing idf %s from list\n",
					pl->pl_idf->id_text);
#endif
			/*	Remove all the definitions made within
				a prototype.
			*/
			if (pl->pl_flag == FORMAL) {
				register struct type *tp = pl->pl_type;

				while (tp && tp->tp_fund != FUNCTION)
					tp = tp->tp_up;
				if (tp)
					remove_proto_idfs(tp->tp_proto);
			}
			def = pl->pl_idf->id_def;
			if (def && def->df_level <= L_PROTO){
				pl->pl_idf->id_def = def->next;
				free_def(def);
			}
			pl->pl_idf = (struct idf *) 0;
		}
		pl = pl->next;
	}
}

call_proto(expp)
	register struct expr **expp;
{
	/*	If the function specified by (*expp)->OP_LEFT has a prototype,
		the parameters are converted according the rules specified in
		par. 3.3.2.2. E.i. the parameters are converted to the prototype
		counter parts as if by assignment. For the parameters falling
		under ellipsis clause the old parameters conversion stuff
		applies.
	*/
	register struct expr *left = (*expp)->OP_LEFT;
	register struct expr *right = (*expp)->OP_RIGHT;
	register struct proto *pl = NO_PROTO;

	if (left != NILEXPR) {	/* in case of an error */
		register struct type *tp = left->ex_type;

		while (tp && tp->tp_fund != FUNCTION)
			tp = tp->tp_up;
		pl = (tp && tp->tp_proto) ? tp->tp_proto : NO_PROTO;
	}

	if (right != NILEXPR) { /* function call with parameters */
		register struct expr *ex = right;
		register struct expr **ep = &((*expp)->OP_RIGHT);
		register int ecnt = 0, pcnt = 0;
		struct expr **estack[NPARAMS];
		struct proto *pstack[NPARAMS];

		if (pl == NO_PROTO) {
			register struct idf *idf;

			if (left->ex_class != Value || left->VL_CLASS != Name) {
				strict("no prototype supplied");
				return;
			}
			if ((idf = left->VL_IDF)->id_proto)
				return;
			strict("'%s' no prototype supplied", idf->id_text);
			idf->id_proto++;
			return;
		}

		/* stack up the parameter expressions */
		while (ex->ex_class == Oper && ex->OP_OPER == PARCOMMA) {
			if (ecnt == STDC_NPARAMS)
				strict("number of parameters exceeds ANSI limit");
			if (ecnt >= NPARAMS-1) {
				error("too many parameters");
				return;
			}
			estack[ecnt++] = &(ex->OP_RIGHT);
			ep = &(ex->OP_LEFT);
			ex = ex->OP_LEFT;
		}
		estack[ecnt++] = ep;

		/*	Declarations like int f(void) do not expect any
			parameters.
		*/
		if (pl && pl->pl_flag == VOID) {
			strict("no parameters expected");
			return;
		}

		/* stack up the prototypes */
		while (pl) {
			/* stack prototypes */
			pstack[pcnt++] = pl;
			pl = pl->next;
		}
		pcnt--;

		for (--ecnt; ecnt >= 0; ecnt--) {
			/*	Only the parameters specified in the prototype
				are checked and converted. The parameters that
				fall under the ellipsis clause are neither
				checked nor converted !
			*/
			if (pcnt < 0) {
				error("more parameters than specified in prototype");
				break;
			}
			if (pstack[pcnt]->pl_flag != ELLIPSIS) {
				ch7cast(estack[ecnt],CASTAB,pstack[pcnt]->pl_type);
				pcnt--;
			} else
				break;	/* against unnecessary looping */
		}
		if (pcnt >= 0 && pstack[0]->pl_flag != ELLIPSIS)
			error("less parameters than specified in prototype");

	} else {
		if (pl && pl->pl_flag != VOID)
			error("less parameters than specified in prototype");
	}
}
