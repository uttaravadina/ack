.define _gtty
.extern _gtty
.text
_gtty:
tst.b -40(sp)
link	a6,#-0
move.l 12(a6),-(sp)
move.l #29704,-(sp)
move.l 8(a6),-(sp)
jsr _ioctl
add.l #12,sp
unlk a6
rts
