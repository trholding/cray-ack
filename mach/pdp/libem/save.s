/ $Header$
.text
.globl save~,retu~,savearea

save~:
	mov	r5,savearea
	mov	$[savearea+2],r5
	mov	r4,(r5)+
	mov	r3,(r5)+
	mov	r2,(r5)+
	mov	(sp)+,r2
	mov	(sp)+,(r5)+
	jmp	(r2)
retu~:
	mov	-(r5),-(sp)
	mov	-(r5),r2
	mov	-(r5),r3
	mov	-(r5),r4
	mov	-(r5),r5
	rts	pc

.data
.even
savearea:
	.=.+12.
