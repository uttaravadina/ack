.sect .text; .sect .rom; .sect .data; .sect .bss
.sect .text
exece = 59
.define	_execve

_execve:
	.data2	0x0000
	chmk	$exece
	jmp 	cerror
