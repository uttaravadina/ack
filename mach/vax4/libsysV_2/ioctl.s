.sect .text; .sect .rom; .sect .data; .sect .bss
.sect .text
ioctl = 54
.define	_ioctl

_ioctl:
	.data2	0x0000
	chmk	$ioctl
	bcc	1f
	jmp	cerror
1:
	ret
