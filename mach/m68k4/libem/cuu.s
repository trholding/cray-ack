.define	.ciu
.define	.cui
.define	.cuu

	.text
.ciu:
.cui:
.cuu:
	move.l	(sp)+,a0	! return address
	move	(sp)+,d0	! destination size
	sub	(sp)+,d0
	bgt	1f
	sub	d0,sp
	jmp	(a0)
1:
	asr	#1,d0
2:
	clr	-(sp)
	dbf	d0,2b
	jmp	(a0)
.align 2
