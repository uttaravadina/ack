.sect .text; .sect .rom; .sect .data; .sect .bss
.sect .text
fstat = 28
.define	_fstat

_fstat:
	.data2	0x0000
	chmk	$fstat
	bcc 	1f
	jmp 	cerror
1:
	clrl	r0
	ret
