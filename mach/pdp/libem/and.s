/ $Header$
.text
.globl and~

/ size in r0
and~:
	mov	(sp)+,r3
	mov	sp,r1
	add	r0,r1
	asr	r0
1:	com	(sp)
	bic	(sp)+,(r1)+
	sob	r0,1b
	jmp	(r3)
