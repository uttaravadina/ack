/*
 * (c) copyright 1990 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#define RCSID3 "$Id$"

/*
 * VAX-11 keywords
 */

{0,		REG,		0,		"r0"},
{0,		REG,		1,		"r1"},
{0,		REG,		2,		"r2"},
{0,		REG,		3,		"r3"},
{0,		REG,		4,		"r4"},
{0,		REG,		5,		"r5"},
{0,		REG,		6,		"r6"},
{0,		REG,		7,		"r7"},
{0,		REG,		8,		"r8"},
{0,		REG,		9,		"r9"},
{0,		REG,		10,		"r10"},
{0,		REG,		11,		"r11"},
{0,		REG,		12,		"r12"},
{0,		REG,		12,		"ap"},
{0,		REG,		13,		"r13"},
{0,		REG,		13,		"fp"},
{0,		REG,		14,		"r14"},
{0,		REG,		14,		"sp"},
{0,		REG,		15,		"r15"},
{0,		REG,		15,		"pc"},

/* For immediate mode, we need the size as specified by the instruction.
   Ordinary operands are therefore encoded as _w, _b, and _l to indicate
   size.
   For now, immediate floating point and immediate values of size > 4 are not
   implemented. _u is used for this.
   The valu_t field is used for the opcode. Most opcodes take one byte.
   The ones that don't take two bytes.
*/

/* integer arithmetic and logical instructions */

{0,		OP2_w_w,	0x58,		"adawi"},
{0,		OP2_b_b,	0x80,		"addb2"},
{0,		OP3_b_b_b,	0x81,		"addb3"},
{0,		OP2_w_w,	0xa0,		"addw2"},
{0,		OP3_w_w_w,	0xa1,		"addw3"},
{0,		OP2_l_l,	0xc0,		"addl2"},
{0,		OP3_l_l_l,	0xc1,		"addl3"},
{0,		OP2_l_l,	0xd8,		"adwc"},
{0,		OP3_b_l_l,	0x78,		"ashl"},
{0,		OP3_b_u_u,	0x79,		"ashq"},
{0,		OP2_b_b,	0x8a,		"bicb2"},
{0,		OP3_b_b_b,	0x8b,		"bicb3"},
{0,		OP2_w_w,	0xaa,		"bicw2"},
{0,		OP3_w_w_w,	0xab,		"bicw3"},
{0,		OP2_l_l,	0xca,		"bicl2"},
{0,		OP3_l_l_l,	0xcb,		"bicl3"},
{0,		OP2_b_b,	0x88,		"bisb2"},
{0,		OP3_b_b_b,	0x89,		"bisb3"},
{0,		OP2_w_w,	0xa8,		"bisw2"},
{0,		OP3_w_w_w,	0xa9,		"bisw3"},
{0,		OP2_l_l,	0xc8,		"bisl2"},
{0,		OP3_l_l_l,	0xc9,		"bisl3"},
{0,		OP2_b_b,	0x93,		"bitb"},
{0,		OP2_w_w,	0xb3,		"bitw"},
{0,		OP2_l_l,	0xd3,		"bitl"},
{0,		OP1_X,		0x94|(1L<<16),	"clrb"},
{0,		OP1_X,		0xb4|(2L<<16),	"clrw"},
{0,		OP1_X,		0xd4|(4L<<16),	"clrl"},
{0,		OP1_u,		0x7c,		"clrq"},
{0,		OP1_u,		0x7cfd,		"clro"},
{0,		OP2_b_b,	0x91,		"cmpb"},
{0,		OP2_w_w,	0xb1,		"cmpw"},
{0,		OP2_l_l,	0xd1,		"cmpl"},
{0,		OP2_b_w,	0x99,		"cvtbw"},
{0,		OP2_b_l,	0x98,		"cvtbl"},
{0,		OP2_w_b,	0x33,		"cvtwb"},
{0,		OP2_w_l,	0x32,		"cvtwl"},
{0,		OP2_l_b,	0xf6,		"cvtlb"},
{0,		OP2_l_w,	0xf7,		"cvtlw"},
{0,		OP1_X,		0x97|(1L<<16),	"decb"},
{0,		OP1_X,		0xb7|(2L<<16),	"decw"},
{0,		OP1_X,		0xd7|(4L<<16),	"decl"},
{0,		OP2_b_b,	0x86,		"divb2"},
{0,		OP3_b_b_b,	0x87,		"divb3"},
{0,		OP2_w_w,	0xa6,		"divw2"},
{0,		OP3_w_w_w,	0xa7,		"divw3"},
{0,		OP2_l_l,	0xc6,		"divl2"},
{0,		OP3_l_l_l,	0xc7,		"divl3"},
{0,		OP4_l_u_l_l,	0x7b,		"ediv"},
{0,		OP4_l_l_l_u,	0x7a,		"emul"},
{0,		OP1_X,		0x96|(1L<<16),	"incb"},
{0,		OP1_X,		0xb6|(2L<<16),	"incw"},
{0,		OP1_X,		0xd6|(4L<<16),	"incl"},
{0,		OP2_b_b,	0x92,		"mcomb"},
{0,		OP2_w_w,	0xb2,		"mcomw"},
{0,		OP2_l_l,	0xd2,		"mcoml"},
{0,		OP2_b_b,	0x8e,		"mnegb"},
{0,		OP2_w_w,	0xae,		"mnegw"},
{0,		OP2_l_l,	0xce,		"mnegl"},
{0,		OP2_b_b,	0x90,		"movb"},
{0,		OP2_w_w,	0xb0,		"movw"},
{0,		OP2_l_l,	0xd0,		"movl"},
{0,		OP2_u_u,	0x7d,		"movq"},
{0,		OP2_u_u,	0x7dfd,		"movo"},
{0,		OP2_b_w,	0x9b,		"movzbw"},
{0,		OP2_b_l,	0x9a,		"movzbl"},
{0,		OP2_w_l,	0x3c,		"movzwl"},
{0,		OP2_b_b,	0x84,		"mulb2"},
{0,		OP3_b_b_b,	0x85,		"mulb3"},
{0,		OP2_w_w,	0xa4,		"mulw2"},
{0,		OP3_w_w_w,	0xa5,		"mulw3"},
{0,		OP2_l_l,	0xc4,		"mull2"},
{0,		OP3_l_l_l,	0xc5,		"mull3"},
{0,		OP1_X,		0xdd|(4L<<16),	"pushl"},
{0,		OP3_b_l_l,	0x9c,		"rotl"},
{0,		OP2_l_l,	0xd9,		"sbwc"},
{0,		OP2_b_b,	0x82,		"subb2"},
{0,		OP3_b_b_b,	0x83,		"subb3"},
{0,		OP2_w_w,	0xa2,		"subw2"},
{0,		OP3_w_w_w,	0xa3,		"subw3"},
{0,		OP2_l_l,	0xc2,		"subl2"},
{0,		OP3_l_l_l,	0xc3,		"subl3"},
{0,		OP1_X,		0x95|(1L<<16),	"tstb"},
{0,		OP1_X,		0xb5|(2L<<16),	"tstw"},
{0,		OP1_X,		0xd5|(4L<<16),	"tstl"},
{0,		OP2_b_b,	0x8c,		"xorb2"},
{0,		OP3_b_b_b,	0x8d,		"xorb3"},
{0,		OP2_w_w,	0xac,		"xorw2"},
{0,		OP3_w_w_w,	0xad,		"xorw3"},
{0,		OP2_l_l,	0xcc,		"xorl2"},
{0,		OP3_l_l_l,	0xcd,		"xorl3"},

/* Address instructions */

{0,		OP2_A_l,	0x9e,		"movab"},
{0,		OP2_A_l,	0x3e,		"movaw"},
{0,		OP2_A_l,	0xde,		"moval"},
{0,		OP2_A_l,	0xde,		"movaf"},
{0,		OP2_A_l,	0x7e,		"movaq"},
{0,		OP2_A_l,	0x7e,		"movad"},
{0,		OP2_A_l,	0x7e,		"movag"},
{0,		OP2_A_l,	0x7efd,		"movah"},
{0,		OP2_A_l,	0x7efd,		"movao"},
{0,		OP1_A,		0x9f,		"pushab"},
{0,		OP1_A,		0x3f,		"pushaw"},
{0,		OP1_A,		0xdf,		"pushal"},
{0,		OP1_A,		0xdf,		"pushaf"},
{0,		OP1_A,		0x7f,		"pushaq"},
{0,		OP1_A,		0x7f,		"pushad"},
{0,		OP1_A,		0x7f,		"pushag"},
{0,		OP1_A,		0x7ffd,		"pushah"},
{0,		OP1_A,		0x7ffd,		"pushao"},

/* Variable length bit-field instructions */

{0,		OP4_l_b_V_l,	0xec,		"cmpv"},
{0,		OP4_l_b_V_l,	0xed,		"cmpzv"},
{0,		OP4_l_b_V_l,	0xee,		"extv"},
{0,		OP4_l_b_V_l,	0xef,		"extzv"},
{0,		OP4_l_b_V_l,	0xeb,		"ffc"},
{0,		OP4_l_b_V_l,	0xea,		"ffs"},
{0,		OP4_l_l_b_V,	0xf0,		"insv"},

/* Control instructions */

{0,		OP4_b_b_b_Bw,	0x9d,		"acbb"},
{0,		OP4_w_w_w_Bw,	0x3d,		"acbw"},
{0,		OP4_l_l_l_Bw,	0xf1,		"acbl"},
{0,		OP4_u_u_u_Bw,	0x4f,		"acbf"},
{0,		OP4_u_u_u_Bw,	0x6f,		"acbd"},
{0,		OP4_u_u_u_Bw,	0x4ffd,		"acbg"},
{0,		OP4_u_u_u_Bw,	0x6ffd,		"acbh"},
{0,		OP3_l_l_Bb,	0xf3,		"aobleq"},
{0,		OP3_l_l_Bb,	0xf2,		"aoblss"},
{0,		OP1_BX,		0x14|(1L<<16),	"bgtr"},
{0,		OP1_BX,		0x15|(1L<<16),	"bleq"},
{0,		OP1_BX,		0x12|(1L<<16),	"bneq"},
{0,		OP1_BX,		0x12|(1L<<16),	"bnequ"},
{0,		OP1_BX,		0x13|(1L<<16),	"beql"},
{0,		OP1_BX,		0x13|(1L<<16),	"beqlu"},
{0,		OP1_BX,		0x18|(1L<<16),	"bgeq"},
{0,		OP1_BX,		0x19|(1L<<16),	"blss"},
{0,		OP1_BX,		0x1a|(1L<<16),	"bgtru"},
{0,		OP1_BX,		0x1b|(1L<<16),	"blequ"},
{0,		OP1_BX,		0x1c|(1L<<16),	"bvc"},
{0,		OP1_BX,		0x1d|(1L<<16),	"bvs"},
{0,		OP1_BX,		0x1e|(1L<<16),	"bgequ"},
{0,		OP1_BX,		0x1e|(1L<<16),	"bcc"},
{0,		OP1_BX,		0x1f|(1L<<16),	"blssu"},
{0,		OP1_BX,		0x1f|(1L<<16),	"bcs"},
{0,		OP3_l_V_Bb,	0xe0,		"bbs"},
{0,		OP3_l_V_Bb,	0xe1,		"bbc"},
{0,		OP3_l_V_Bb,	0xe2,		"bbss"},
{0,		OP3_l_V_Bb,	0xe3,		"bbcs"},
{0,		OP3_l_V_Bb,	0xe4,		"bbsc"},
{0,		OP3_l_V_Bb,	0xe5,		"bbcc"},
{0,		OP3_l_V_Bb,	0xe6,		"bbssi"},
{0,		OP3_l_V_Bb,	0xe7,		"bbcci"},
{0,		OP2_l_Bb,	0xe8,		"blbs"},
{0,		OP2_l_Bb,	0xe9,		"blbc"},
{0,		OP1_Be,		0x14,		"jgtr"},
{0,		OP1_Be,		0x15,		"jleq"},
{0,		OP1_Be,		0x12,		"jneq"},
{0,		OP1_Be,		0x12,		"jnequ"},
{0,		OP1_Be,		0x13,		"jeql"},
{0,		OP1_Be,		0x13,		"jeqlu"},
{0,		OP1_Be,		0x18,		"jgeq"},
{0,		OP1_Be,		0x19,		"jlss"},
{0,		OP1_Be,		0x1a,		"jgtru"},
{0,		OP1_Be,		0x1b,		"jlequ"},
{0,		OP1_Be,		0x1c,		"jvc"},
{0,		OP1_Be,		0x1d,		"jvs"},
{0,		OP1_Be,		0x1e,		"jgequ"},
{0,		OP1_Be,		0x1e,		"jcc"},
{0,		OP1_Be,		0x1f,		"jlssu"},
{0,		OP1_Be,		0x1f,		"jcs"},
{0,		OP2_l_Be,	0xe8,		"jlbs"},
{0,		OP2_l_Be,	0xe9,		"jlbc"},
{0,		OP3_l_V_Be,	0xe0,		"jbs"},
{0,		OP3_l_V_Be,	0xe1,		"jbc"},
{0,		OP3_l_V_Be,	0xe2,		"jbss"},
{0,		OP3_l_V_Be,	0xe3,		"jbcs"},
{0,		OP3_l_V_Be,	0xe4,		"jbsc"},
{0,		OP3_l_V_Be,	0xe5,		"jbcc"},
{0,		OP3_l_V_Be,	0xe6,		"jbssi"},
{0,		OP3_l_V_Be,	0xe7,		"jbcci"},
{0,		OP1_Bx,		0x11,		"br"},
{0,		OP1_BX,		0x11|(1L<<16),	"brb"},
{0,		OP1_BX,		0x31|(2L<<16),	"brw"},
{0,		OP1_Be,		0x11,		"jbr"},
{0,		OP1_Bx,		0x10,		"bsb"},
{0,		OP1_BX,		0x10|(1L<<16),	"bsbb"},
{0,		OP1_BX,		0x30|(2L<<16),	"bsbw"},
{0,		CASE_X_X_X,	0x8f|(1L<<16),	"caseb"},
{0,		CASE_X_X_X,	0xaf|(2L<<16),	"casew"},
{0,		CASE_X_X_X,	0xcf|(4L<<16),	"casel"},
{0,		OP1_A,		0x17,		"jmp"},
{0,		OP1_A,		0x16,		"jsb"},
{0,		OP0,		0x05,		"rsb"},
{0,		OP2_l_Bb,	0xf4,		"sobgeq"},
{0,		OP2_l_Bb,	0xf5,		"sobgtr"},

/* Procedure call instructions */

{0,		OP2_A_A,	0xfa,		"callg"},
{0,		OP2_l_A,	0xfb,		"calls"},
{0,		OP0,		0x04,		"ret"},

/* Miscellaneous instructions */

{0,		OP1_X,		0xb9|(2L<<16),	"bicpsw"},
{0,		OP1_X,		0xb8|(2L<<16),	"bispsw"},
{0,		OP0,		0x03,		"bpt"},
{0,		OP0,		0x00,		"halt"},
{0,		OP6_l_l_l_l_l_l,0x0a,		"index"},
{0,		OP1_X,		0xdc|(4L<<16),	"movpsl"},
{0,		OP0,		0x01,		"nop"},
{0,		OP1_X,		0xba|(2L<<16),	"popr"},
{0,		OP1_X,		0xbb|(2L<<16),	"pushr"},
{0,		OP0,		0xfc,		"xfc"},

/* Queue instructions */

{0,		OP2_A_A,	0x5c,		"insqhi"},
{0,		OP2_A_A,	0x5d,		"insqti"},
{0,		OP2_A_A,	0x0e,		"insque"},
{0,		OP2_A_l,	0x5e,		"remqhi"},
{0,		OP2_A_l,	0x5f,		"remqti"},
{0,		OP2_A_l,	0x0f,		"remque"},

/* Floating point instructions */

{0,		OP2_u_u,	0x40,		"addf2"},
{0,		OP3_u_u_u,	0x41,		"addf3"},
{0,		OP2_u_u,	0x60,		"addd2"},
{0,		OP3_u_u_u,	0x61,		"addd3"},
{0,		OP2_u_u,	0x40fd,		"addg2"},
{0,		OP3_u_u_u,	0x41fd,		"addg3"},
{0,		OP2_u_u,	0x60fd,		"addh2"},
{0,		OP3_u_u_u,	0x61fd,		"addh3"},
{0,		OP1_u,		0xd4,		"clrf"},
{0,		OP1_u,		0x7c,		"clrd"},
{0,		OP1_u,		0x7c,		"clrg"},
{0,		OP1_u,		0x7cfd,		"clrh"},
{0,		OP2_u_u,	0x51,		"cmpf"},
{0,		OP2_u_u,	0x71,		"cmpd"},
{0,		OP2_u_u,	0x51fd,		"cmpg"},
{0,		OP2_u_u,	0x71fd,		"cmph"},
{0,		OP2_b_u,	0x4c,		"cvtbf"},
{0,		OP2_b_u,	0x6c,		"cvtbd"},
{0,		OP2_b_u,	0x4cfd,		"cvtbg"},
{0,		OP2_b_u,	0x6cfd,		"cvtbh"},
{0,		OP2_w_u,	0x4d,		"cvtwf"},
{0,		OP2_w_u,	0x6d,		"cvtwd"},
{0,		OP2_w_u,	0x4dfd,		"cvtwg"},
{0,		OP2_w_u,	0x6dfd,		"cvtwh"},
{0,		OP2_l_u,	0x4e,		"cvtlf"},
{0,		OP2_l_u,	0x6e,		"cvtld"},
{0,		OP2_l_u,	0x4efd,		"cvtlg"},
{0,		OP2_l_u,	0x6efd,		"cvtlh"},
{0,		OP2_u_b,	0x48,		"cvtfb"},
{0,		OP2_u_b,	0x68,		"cvtdb"},
{0,		OP2_u_b,	0x48fd,		"cvtgb"},
{0,		OP2_u_b,	0x68fd,		"cvthb"},
{0,		OP2_u_w,	0x49,		"cvtfw"},
{0,		OP2_u_w,	0x69,		"cvtdw"},
{0,		OP2_u_w,	0x49fd,		"cvtgw"},
{0,		OP2_u_w,	0x69fd,		"cvthw"},
{0,		OP2_u_l,	0x4a,		"cvtfl"},
{0,		OP2_u_l,	0x6a,		"cvtdl"},
{0,		OP2_u_l,	0x4afd,		"cvtgl"},
{0,		OP2_u_l,	0x6afd,		"cvthl"},
{0,		OP2_u_l,	0x4b,		"cvtrfl"},
{0,		OP2_u_l,	0x6b,		"cvtrdl"},
{0,		OP2_u_l,	0x4bfd,		"cvtrgl"},
{0,		OP2_u_l,	0x6bfd,		"cvtrhl"},
{0,		OP2_u_u,	0x56,		"cvtfd"},
{0,		OP2_u_u,	0x99fd,		"cvtfg"},
{0,		OP2_u_u,	0x98fd,		"cvtfh"},
{0,		OP2_u_u,	0x76,		"cvtdf"},
{0,		OP2_u_u,	0x32fd,		"cvtdh"},
{0,		OP2_u_u,	0x33fd,		"cvtgf"},
{0,		OP2_u_u,	0x56fd,		"cvtgh"},
{0,		OP2_u_u,	0xf6fd,		"cvthf"},
{0,		OP2_u_u,	0xf7fd,		"cvthd"},
{0,		OP2_u_u,	0x76fd,		"cvthg"},
{0,		OP2_u_u,	0x46,		"divf2"},
{0,		OP3_u_u_u,	0x47,		"divf3"},
{0,		OP2_u_u,	0x66,		"divd2"},
{0,		OP3_u_u_u,	0x67,		"divd3"},
{0,		OP2_u_u,	0x46fd,		"divg2"},
{0,		OP3_u_u_u,	0x47fd,		"divg3"},
{0,		OP2_u_u,	0x66fd,		"divh2"},
{0,		OP3_u_u_u,	0x67fd,		"divh3"},
{0,		OP5_u_b_u_l_u,	0x54,		"emodf"},
{0,		OP5_u_b_u_l_u,	0x74,		"emodd"},
{0,		OP5_u_w_u_l_u,	0x54fd,		"emodg"},
{0,		OP5_u_w_u_l_u,	0x74fd,		"emodh"},
{0,		OP2_u_u,	0x52,		"mnegf"},
{0,		OP2_u_u,	0x72,		"mnegd"},
{0,		OP2_u_u,	0x52fd,		"mnegg"},
{0,		OP2_u_u,	0x72fd,		"mnegh"},
{0,		OP2_u_u,	0x50,		"movf"},
{0,		OP2_u_u,	0x70,		"movd"},
{0,		OP2_u_u,	0x50fd,		"movg"},
{0,		OP2_u_u,	0x70fd,		"movh"},
{0,		OP2_u_u,	0x44,		"mulf2"},
{0,		OP3_u_u_u,	0x45,		"mulf3"},
{0,		OP2_u_u,	0x64,		"muld2"},
{0,		OP3_u_u_u,	0x65,		"muld3"},
{0,		OP2_u_u,	0x44fd,		"mulg2"},
{0,		OP3_u_u_u,	0x45fd,		"mulg3"},
{0,		OP2_u_u,	0x64fd,		"mulh2"},
{0,		OP3_u_u_u,	0x65fd,		"mulh3"},
{0,		OP3_u_w_A,	0x55,		"polyf"},
{0,		OP3_u_w_A,	0x75,		"polyd"},
{0,		OP3_u_w_A,	0x55fd,		"polyg"},
{0,		OP3_u_w_A,	0x75fd,		"polyh"},
{0,		OP2_u_u,	0x42,		"subf2"},
{0,		OP3_u_u_u,	0x43,		"subf3"},
{0,		OP2_u_u,	0x62,		"subd2"},
{0,		OP3_u_u_u,	0x63,		"subd3"},
{0,		OP2_u_u,	0x42fd,		"subg2"},
{0,		OP3_u_u_u,	0x43fd,		"subg3"},
{0,		OP2_u_u,	0x62fd,		"subh2"},
{0,		OP3_u_u_u,	0x63fd,		"subh3"},
{0,		OP1_u,		0x53,		"tstf"},
{0,		OP1_u,		0x73,		"tstd"},
{0,		OP1_u,		0x53fd,		"tstg"},
{0,		OP1_u,		0x73fd,		"tsth"},

/* Character string instructions */

{0,		OP3_w_A_A,	0x29,		"cmpc3"},
{0,		OP5_w_A_b_w_A,	0x2d,		"cmpc5"},
{0,		OP3_b_w_A,	0x3a,		"locc"},
{0,		OP4_w_A_w_A,	0x39,		"matchc"},
{0,		OP3_w_A_A,	0x28,		"movc3"},
{0,		OP5_w_A_b_w_A,	0x2c,		"movc5"},
{0,		OP6_w_A_b_A_w_A,0x2e,		"movtc"},
{0,		OP6_w_A_b_A_w_A,0x2f,		"movtuc"},
{0,		OP4_w_A_A_b,	0x2a,		"scanc"},
{0,		OP3_b_w_A,	0x3b,		"skpc"},
{0,		OP4_w_A_A_b,	0x2b,		"spanc"},

/* Cyclic redundancy check instructions */

{0,		OP4_A_l_w_A,	0x0b,		"crc"},

/* Decimal string instructions */

{0,		OP4_w_A_w_A,	0x20,		"addp4"},
{0,		OP6_w_A_w_A_w_A,0x21,		"addp6"},
{0,		OP6_b_w_A_b_w_A,0xf8,		"ashp"},
{0,		OP3_w_A_A,	0x35,		"cmpp3"},
{0,		OP4_w_A_w_A,	0x37,		"cmpp4"},
{0,		OP3_l_w_A,	0xf9,		"cvtlp"},
{0,		OP3_w_A_l,	0x36,		"cvtpl"},
{0,		OP4_w_A_w_A,	0x08,		"cvtps"},
{0,		OP5_w_A_A_w_A,	0x24,		"cvtpt"},
{0,		OP4_w_A_w_A,	0x09,		"cvtsp"},
{0,		OP5_w_A_A_w_A,	0x26,		"cvttp"},
{0,		OP6_w_A_w_A_w_A,0x27,		"divp"},
{0,		OP3_w_A_A,	0x34,		"movp"},
{0,		OP6_w_A_w_A_w_A,0x25,		"mulp"},
{0,		OP4_w_A_w_A,	0x22,		"subp4"},
{0,		OP6_w_A_w_A_w_A,0x23,		"subp6"},

/* Edit instruction */

{0,		OP4_w_A_A_A,	0x38,		"editpc"},

/* Other VAX-11 instructions */

/* BSD 4.3 adb has a different opinion of the bugw and bugl instructions:
   it thinks that an addressing mode byte is required. However, according
   to the VAX-11 Architecture Reference Manual, Revision 6.1, 1982, the
   access type is b, which means that the operand is a branch displacement.
*/
{0,		OP1_BX,		0xfeff|(2L<<16),"bugw"},
{0,		OP1_BX,		0xfdff|(4L<<16),"bugl"},

{0,		OP3_b_w_A,	0x0c,		"prober"},
{0,		OP3_b_w_A,	0x0d,		"probew"},

{0,		OP0,		0x02,		"rei"},
{0,		OP1_X,		0xbc|(2L<<16),	"chmk"},
{0,		OP1_X,		0xbd|(2L<<16),	"chme"},
{0,		OP1_X,		0xbe|(2L<<16),	"chms"},
{0,		OP1_X,		0xbf|(2L<<16),	"chmu"},

{0,		OP0,		0x06,		"ldpctx"},
{0,		OP0,		0x07,		"svpctx"},
{0,		OP2_l_l,	0xda,		"mtpr"},
{0,		OP2_l_l,	0xdb,		"mfpr"},
