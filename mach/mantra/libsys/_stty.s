.define __stty
.extern __stty
.sect .text
.sect .rom
.sect .data
.sect .bss
.sect .text
__stty:
tst.b -40(sp)
link	a6,#-0
move.l 12(a6),-(sp)
move.l #29705,-(sp)
move.l 8(a6),-(sp)
jsr __ioctl
add.l #12,sp
unlk a6
rts
