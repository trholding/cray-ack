/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*
	chtabgen - character table generator 

	Author: Erik Baalbergen (..tjalk!erikb)
	Many mods by Ceriel Jacobs
*/

#include <stdio.h> 

#ifndef NORCSID
static char *RcsId = "$Header$";
#endif

#define MAXBUF	256
#define MAXTAB 10000
#define COMCOM	'-'
#define FILECOM	'%'

int InputForm = 'c';	/* default input format (and, currently, only one) */
char OutputForm[MAXBUF] = "%s,\n";
			/* format for spitting out a string */
char *Table[MAXTAB];
char *ProgCall;		/* callname of this program */
int signedch = 0;	/* set if characters are signed */
int TabSize = 128;	/* default size of generated table */
char *InitialValue;	/* initial value of all table entries */
#define CHROFFSETFILE	"charoffset.h"
char *chroffsetfile = 0;

extern char *malloc(), *strcpy();

main(argc, argv)
	char *argv[];
{
	if (((char) -1) < 0) signedch = 1;

	ProgCall = *argv++;
	argc--;
	while (argc-- > 0) {
		if (**argv == COMCOM) {
			option(*argv++);
		}
		else {
			if (! process(*argv++, InputForm)) {
				exit(1);
			}
		}
	}
	if (chroffsetfile) MkCharIndex();
	exit(0);
}

MkCharIndex()
{
	/*	Assumption: 8 bit bytes, ASCII character set */
	FILE *fp;

	if ((fp = fopen(chroffsetfile, "w")) == NULL) {
		fprintf(stderr, "%s: cannot write file %s\n", ProgCall, chroffsetfile);
		exit(1);
	}
	if (signedch) {
		fputs("#define CharOffset	128\n", fp);
	}
	else	fputs("#define CharOffset	0\n", fp);
	fclose(fp);
}

char *
Salloc(s)
	char *s;
{
	char *ns = malloc((unsigned)strlen(s) + 1);

	if (ns) {
		strcpy(ns, s);
	}
	else {
		fprintf(stderr, "%s: out of memory\n", ProgCall);
		exit(1);
	}
	return ns;
}

option(str)
	char *str;
{
	/*	note that *str indicates the source of the option:
		either COMCOM (from command line) or FILECOM (from a file).
	*/
	switch (*++str) {

	case ' ':	/* command */
	case '\t':
	case '\0':
		break;
	case 'I':	/* for future extension */
		InputForm = *++str;
		break;
	case 'f':	/* input from file ... */
		if (*++str == '\0') {
			fprintf(stderr, "%s: -f: name expected\n", ProgCall);
			exit(1);
		}
		DoFile(str);
		break;
	case 'F':	/* new output format string */
		sprintf(OutputForm, "%s\n", ++str);
		break;
	case 'T':	/* insert text literally */
		printf("%s\n", ++str);
		break;
	case 'p':	/* print table */
		PrintTable();
		break;
	case 'C':	/* clear table */
		InitTable((char *)0);
		break;
	case 'i':	/* initialize table with given value */
		if (*++str == '\0') {
			InitTable((char *)0);
		}
		else	InitTable(str);
		break;
	case 'H':	/* create include file for character offset,
			   and create tables which can be indexed by the
			   full range of characters, rather than 0..127,
			   by adding "CharOffset" to the base.
			*/
		if (*++str == '\0') {
			chroffsetfile = CHROFFSETFILE;
		}
		else	chroffsetfile = ++str;
		break;
	case 'S':
	{
		register i = atoi(++str);

		if (i <= 0 || i > MAXTAB) {
			fprintf(stderr, "%s: size would exceed maximum\n",
				ProgCall);
		}
		else {
			TabSize = i;
		}
		break;
	}
	default:
		fprintf(stderr, "%s: bad option -%s\n", ProgCall, str);
	}
}

InitTable(ival)
	char *ival;
{
	register i;

	for (i = 0; i < TabSize; i++) {
		Table[i] = 0;
	}
	InitialValue = 0;
	if (ival) {
		InitialValue = Salloc(ival);
	}
}

PrintTable()
{
	register i;

	for (i = 0; i < TabSize; i++) {
		if (Table[i]) {
			printf(OutputForm, Table[i]);
		}
		else if (InitialValue) {
			printf(OutputForm, InitialValue);
		}
		else {
			printf(OutputForm, "0");
		}
	}
}

int
process(str, format)
	char *str;
{
	char *cstr = str;
	char *Name = cstr;	/* overwrite original string!	*/

	/* strip of the entry name
	*/
	while (*str && *str != ':') {
		if (*str == '\\') {
			++str;
		}
		*cstr++ = *str++;
	}

	if (*str != ':') {
		fprintf(stderr, "%s: bad specification: \"%s\", ignored\n",
			ProgCall, Name);
		return 0;
	}
	*cstr = '\0';
	str++;

	switch (format) {

	case 'c':
		return c_proc(str, Name);
	default:
		fprintf(stderr, "%s: bad input format\n", ProgCall);
	}
	return 0;
}

c_proc(str, Name)
	char *str;
	char *Name;
{
	int ch, ch2;
	int quoted();
	char *name = Salloc(Name);

	while (*str)	{
		if (*str == '\\')	{
			ch = quoted(&str);
		}
		else	{
			ch = *str++;
		}
		if (*str == '-')	{
			if (*++str == '\\')	{
				ch2 = quoted(&str);
			}
			else	{
				if (ch2 = *str++);
				else str--;
			}
			if (ch > ch2) {
				fprintf(stderr, "%s: bad range\n", ProgCall);
				return 0;
			}
			while (ch <= ch2) {
				if (! setval(ch, name)) return 0;
				ch++;
			}
		}
		else	{
			if (! setval(ch, name)) return 0;
		}
	}
	if (chroffsetfile) Table[256] = Table[0];
	return 1;
}

#define ind(X)	(chroffsetfile && signedch?(X>=128?X-128:X+128):X)

int
setval(ch, nm)
	char *nm;
{
	register char **p = &Table[ind(ch)];

	if (ch < 0 || ch >= TabSize) {
		fprintf(stderr, "Illegal index: %d\n", ch);
		return 0;
	}
	if (*(p = &Table[ind(ch)])) {
		fprintf(stderr, "Warning: redefinition of index %d\n", ch);
	}
	*p = nm;
	return 1;
}

int
quoted(pstr)
	char **pstr;
{
	register int ch;
	register int i;
	register char *str = *pstr;

	if ((*++str >= '0') && (*str <= '9'))	{
		ch = 0;
		for (i = 0; i < 3; i++)	{
			ch = 8 * ch + (*str - '0');
			if (*++str < '0' || *str > '9')
				break;
		}
	}
	else	{
		switch (*str++)	{

		case 'n':
			ch = '\n';
			break;
		case 't':
			ch = '\t';
			break;
		case 'b':
			ch = '\b';
			break;
		case 'r':
			ch = '\r';
			break;
		case 'f':
			ch = '\f';
			break;
		default :
			ch = *str;
		}
	}
	*pstr = str;
	return ch & 0377;
}

char *
getline(s, n, fp)
	char *s;
	FILE *fp;
{
	register c = getc(fp);
	char *str = s;

	while (n--) {
		if (c == EOF) {
			return NULL;
		}
		else
		if (c == '\n') {
			*str++ = '\0';
			return s;
		}
		*str++ = c;
		c = getc(fp);
	}
	s[n - 1] = '\0';
	return s;
}

#define BUFSIZE 1024

DoFile(name)
	char *name;
{
	char text[BUFSIZE];
	FILE *fp;

	if ((fp = fopen(name, "r")) == NULL) {
		fprintf(stderr, "%s: cannot read file %s\n", ProgCall, name);
		exit(1);
	}
	while (getline(text, BUFSIZE, fp) != NULL) {
		if (text[0] == FILECOM) {
			option(text);
		}
		else {
			if (! process(text, InputForm)) {
				exit(1);
			}
		}
	}
}