/* $Header$ */
/*		    L E X I C A L   A N A L Y Z E R			*/

#include	"idfsize.h"
#include	"numsize.h"
#include	"debug.h"
#include	"strsize.h"
#include	"nopp.h"

#include	"input.h"
#include	"alloc.h"
#include	"arith.h"
#include	"def.h"
#include	"idf.h"
#include	"LLlex.h"
#include	"Lpars.h"
#include	"class.h"
#include	"assert.h"
#include	"sizes.h"

/* Data about the token yielded */
struct token dot, ahead, aside;

unsigned int LineNumber = 0;	/* current LineNumber	*/
char *FileName = 0;		/* current filename	*/

int ReplaceMacros = 1;		/* replacing macros			*/
int EoiForNewline = 0;		/* return EOI upon encountering newline	*/
int PreProcKeys = 0;		/* return preprocessor key		*/
int AccFileSpecifier = 0;	/* return filespecifier <...>		*/
int AccDefined = 0;		/* accept "defined(...)"		*/
int UnknownIdIsZero = 0;	/* interpret unknown id as integer 0	*/
int SkipEscNewline = 0;		/* how to interpret backslash-newline	*/

#define MAX_LL_DEPTH	2

static struct token LexStack[MAX_LL_DEPTH];
static LexSP = 0;

/*	In PushLex() the actions are taken in order to initialise or
	re-initialise the lexical scanner.
	E.g. at the invocation of a sub-parser that uses LLlex(), the
	state of the current parser should be saved.
*/
PushLex()
{
	ASSERT(LexSP < 2);
	ASSERT(ASIDE == 0);	/* ASIDE = 0;	*/
	GetToken(&ahead);
	ahead.tk_line = LineNumber;
	ahead.tk_file = FileName;
	LexStack[LexSP++] = dot;
}

PopLex()
{
	ASSERT(LexSP > 0);
	dot = LexStack[--LexSP];
}

int
LLlex()
{
	/*	LLlex() plays the role of Lexical Analyzer for the C parser.
		The look-ahead and putting aside of tokens are taken into
		account.
	*/
	if (ASIDE) {	/* a token is put aside		*/
		dot = aside;
		ASIDE = 0;
	}
	else {		/* read ahead and return the old one	*/
		dot = ahead;
		/*	the following test is performed due to the dual
			task of LLlex(): it is also called for parsing the
			restricted constant expression following a #if or
			#elif.  The newline character causes EOF to be
			returned in this case to stop the LLgen parsing task.
		*/
		if (DOT != EOI)
			GetToken(&ahead);
		else
			DOT = EOF;
	}
	/* keep track of the place of the token in the file	*/
	ahead.tk_file = FileName;
	ahead.tk_line = LineNumber;
	return DOT;
}

char *string_token();

int
GetToken(ptok)
	register struct token *ptok;
{
	/*	GetToken() is the actual token recognizer. It calls the
		control line interpreter if it encounters a "\n#"
		combination. Macro replacement is also performed if it is
		needed.
	*/
	char buf[(IDFSIZE > NUMSIZE ? IDFSIZE : NUMSIZE) + 1];
	register int ch, nch;

again:	/* rescan the input after an error or replacement	*/
	LoadChar(ch);
go_on:	/* rescan, the following character has been read	*/
	/* The following test is made to strip off the nonascii's	 */
	if ((ch & 0200) && ch != EOI) {
		/*	this is the only user-error which causes the
			process to stop abruptly.
		*/
		fatal("non-ascii '\\%03o' read", ch & 0377);
	}
	switch (class(ch)) {	/* detect character class	*/
	case STNL:		/* newline, vertical space or formfeed	*/
		LineNumber++;			/* also at vs and ff	*/
		if (EoiForNewline)	/* called in control line	*/
			/*	a newline in a control line indicates the
				end-of-information of the line.
			*/
			return ptok->tk_symb = EOI;
		while (LoadChar(ch), ch == '#') /* a control line follows */
			domacro();
			/*	We have to loop here, because in
				`domacro' the nl, vt or ff is read. The
				character following it may again be a `#'.
			*/
		goto go_on;
	case STSKIP:		/* just skip the skip characters	*/
		goto again;
	case STGARB:		/* garbage character			*/
#ifndef NOPP
		if (SkipEscNewline && (ch == '\\')) {
			/* a '\\' is allowed in #if/#elif expression	*/
			LoadChar(ch);
			if (class(ch) == STNL) {	/* vt , ff ?	*/
				++LineNumber;
				goto again;
			}
			PushBack();
			ch = '\\';
		}
#endif NOPP
		if (040 < ch && ch < 0177)
			lexerror("garbage char %c", ch);
		else
			lexerror("garbage char \\%03o", ch);
		goto again;
	case STSIMP:	/* a simple character, no part of compound token*/
		if (ch == '/') { /* probably the start of comment	*/
			LoadChar(ch);
			if (ch == '*') {
				/* start of comment	*/
				skipcomment();
				goto again;
			}
			else {
				PushBack();
				ch = '/';	/* restore ch	*/
			}
		}
		return ptok->tk_symb = ch;
	case STCOMP:	/* maybe the start of a compound token		*/
		LoadChar(nch);			/* character lookahead	*/
		switch (ch) {
		case '!':
			if (nch == '=')
				return ptok->tk_symb = NOTEQUAL;
			PushBack();
			return ptok->tk_symb = ch;
		case '&':
			if (nch == '&')
				return ptok->tk_symb = AND;
			PushBack();
			return ptok->tk_symb = ch;
		case '+':
			if (nch == '+')
				return ptok->tk_symb = PLUSPLUS;
			PushBack();
			return ptok->tk_symb = ch;
		case '-':
			if (nch == '-')
				return ptok->tk_symb = MINMIN;
			if (nch == '>')
				return ptok->tk_symb = ARROW;
			PushBack();
			return ptok->tk_symb = ch;
		case '<':
			if (AccFileSpecifier) {
				PushBack();	/* pushback nch */
				ptok->tk_bts =
					string_token(
						"file specifier",
						'>',
						&(ptok->tk_len)
					);
				return ptok->tk_symb = FILESPECIFIER;
			}
			if (nch == '<')
				return ptok->tk_symb = LEFT;
			if (nch == '=')
				return ptok->tk_symb = LESSEQ;
			PushBack();
			return ptok->tk_symb = ch;
		case '=':
			if (nch == '=')
				return ptok->tk_symb = EQUAL;
			/*	The following piece of code tries to recognise
				old-fashioned assignment operators `=op'
			*/
			switch (nch) {
			case '+':
				return ptok->tk_symb = PLUSAB;
			case '-':
				return ptok->tk_symb = MINAB;
			case '*':
				return ptok->tk_symb = TIMESAB;
			case '/':
				return ptok->tk_symb = DIVAB;
			case '%':
				return ptok->tk_symb = MODAB;
			case '>':
			case '<':
				LoadChar(ch);
				if (ch != nch) {
					PushBack();
					lexerror("illegal combination '=%c'",
						nch);
				}
				return ptok->tk_symb = 
					nch == '<' ? LEFTAB : RIGHTAB;
			case '&':
				return ptok->tk_symb = ANDAB;
			case '^':
				return ptok->tk_symb = XORAB;
			case '|':
				return ptok->tk_symb = ORAB;
			}
			PushBack();
			return ptok->tk_symb = ch;
		case '>':
			if (nch == '=')
				return ptok->tk_symb = GREATEREQ;
			if (nch == '>')
				return ptok->tk_symb = RIGHT;
			PushBack();
			return ptok->tk_symb = ch;
		case '|':
			if (nch == '|')
				return ptok->tk_symb = OR;
			PushBack();
			return ptok->tk_symb = ch;
		}
	case STIDF:
	{
		register char *tg = &buf[0];
		register int pos = -1;
		register int hash;
		register struct idf *idef;
		extern int idfsize;		/* ??? */

		hash = STARTHASH();
		do	{			/* read the identifier	*/
			if (++pos < idfsize) {
				*tg++ = ch;
				hash = ENHASH(hash, ch, pos);
			}
			LoadChar(ch);
		} while (in_idf(ch));
		hash = STOPHASH(hash);
		if (ch != EOI)
			PushBack();
		*tg++ = '\0';	/* mark the end of the identifier	*/
		idef = ptok->tk_idf = idf_hashed(buf, tg - buf, hash);
#ifndef NOPP
		if (idef->id_macro && ReplaceMacros && replace(idef))
			/* macro replacement should be performed	*/
			goto again;
		if (UnknownIdIsZero) {
			ptok->tk_ival = (arith)0;
			ptok->tk_fund = INT;
			return ptok->tk_symb = INTEGER;
		}
#endif NOPP
		ptok->tk_symb = (
			idef->id_reserved ?
				idef->id_reserved :
			idef->id_def && idef->id_def->df_sc == TYPEDEF ?
				TYPE_IDENTIFIER :
			IDENTIFIER
		);
		return IDENTIFIER;
	}
	case STCHAR:				/* character constant	*/
	{
		register arith val = 0, size = 0;

		LoadChar(ch);
		if (ch == '\'')
			lexerror("character constant too short");
		else
		while (ch != '\'') {
			if (ch == '\n') {
				lexerror("newline in character constant");
				LineNumber++;
				break;
			}
			if (ch == '\\') {
				LoadChar(ch);
				if (ch == '\n')
					LineNumber++;
				ch = quoted(ch);
			}
			val = val*256 + ch;
			size++;
			LoadChar(ch);
		}
		if (size > int_size)
			lexerror("character constant too long");
		ptok->tk_ival = val;
		ptok->tk_fund = INT;
		return ptok->tk_symb = INTEGER;
	}
	case STSTR:					/* string	*/
		ptok->tk_bts = string_token("string", '"', &(ptok->tk_len));
		return ptok->tk_symb = STRING;
	case STNUM:				/* a numeric constant	*/
	{
		/*	It should be noted that 099 means 81(decimal) and
			099.5 means 99.5 . This severely limits the tricks
			we can use to scan a numeric value.
		*/
		register char *np = &buf[1];
		register int base = 10;
		register int vch;
		register arith val = 0;

		if (ch == '.') {	/* an embarrassing ambiguity */
			LoadChar(vch);
			PushBack();
			if (!is_dig(vch))	/* just a `.'	*/
				return ptok->tk_symb = ch;
			*np++ = '0';
			/*	in the rest of the compiler, all floats
				have to start with a digit.
			*/
		}
		if (ch == '0') {
			*np++ = ch;
			LoadChar(ch);
			if (ch == 'x' || ch == 'X') {
				base = 16;
				LoadChar(ch);
			}
			else
				base = 8;
		}
		while (vch = val_in_base(ch, base), vch >= 0) {
			val = val*base + vch;
			if (np < &buf[NUMSIZE])
				*np++ = ch;
			LoadChar(ch);
		}
		if (ch == 'l' || ch == 'L') {
			ptok->tk_ival = val;
			ptok->tk_fund = LONG;
			return ptok->tk_symb = INTEGER;
		}
		if (base == 16 || !(ch == '.' || ch == 'e' || ch == 'E')) {
			PushBack();
			ptok->tk_ival = val;
			/*	The semantic analyser must know if the
				integral constant is given in octal/hexa-
				decimal form, in which case its type is
				UNSIGNED, or in decimal form, in which case
				its type is signed, indicated by
				the fund INTEGER.
			*/
			ptok->tk_fund = 
				(base == 10 || (base == 8 && val == (arith)0))
					? INTEGER : UNSIGNED;
			return ptok->tk_symb = INTEGER;
		}
		/* where's the test for the length of the integral ???	*/
		if (ch == '.'){
			if (np < &buf[NUMSIZE])
				*np++ = ch;
			LoadChar(ch);
		}
		while (is_dig(ch)){
			if (np < &buf[NUMSIZE])
				*np++ = ch;
			LoadChar(ch);
		}
		if (ch == 'e' || ch == 'E') {
			if (np < &buf[NUMSIZE])
				*np++ = ch;
			LoadChar(ch);
			if (ch == '+' || ch == '-') {
				if (np < &buf[NUMSIZE])
					*np++ = ch;
				LoadChar(ch);
			}
			if (!is_dig(ch)) {
				lexerror("malformed floating constant");
				if (np < &buf[NUMSIZE])
					*np++ = ch;
			}
			while (is_dig(ch)) {
				if (np < &buf[NUMSIZE])
					*np++ = ch;
				LoadChar(ch);
			}
		}
		PushBack();
		*np++ = '\0';
		buf[0] = '-';	/* good heavens...	*/
		if (np == &buf[NUMSIZE+1]) {
			lexerror("floating constant too long");
			ptok->tk_fval = Salloc("0.0", 5) + 1;
		}
		else
			ptok->tk_fval = Salloc(buf, np - buf) + 1;
		return ptok->tk_symb = FLOATING;
	}
	case STEOI:			/* end of text on source file	*/
		return ptok->tk_symb = EOI;
	default:				/* this cannot happen	*/
		crash("bad class for char 0%o", ch);
	}
	/*NOTREACHED*/
}

skipcomment()
{
	/*	The last character read has been the '*' of '/_*'.  The
		characters, except NL and EOI, between '/_*' and the first
		occurring '*_/' are not interpreted.
		NL only affects the LineNumber.  EOI is not legal.

		Important note: it is not possible to stop skipping comment
		beyond the end-of-file of an included file.
		EOI is returned by LoadChar only on encountering EOF of the
		top-level file...
	*/
	register int c;

	NoUnstack++;
	LoadChar(c);
	do {
		while (c != '*') {
			if (class(c) == STNL)
				++LineNumber;
			else
			if (c == EOI) {
				NoUnstack--;
				return;
			}
			LoadChar(c);
		}
		/* Last Character seen was '*' */
		LoadChar(c);
	} while (c != '/');
	NoUnstack--;
}

char *
string_token(nm, stop_char, plen)
	char *nm;
	int *plen;
{
	register int ch;
	register int str_size;
	register char *str = Malloc(str_size = ISTRSIZE);
	register int pos = 0;
	
	LoadChar(ch);
	while (ch != stop_char) {
		if (ch == '\n') {
			lexerror("newline in %s", nm);
			LineNumber++;
			break;
		}
		if (ch == EOI) {
			lexerror("end-of-file inside %s", nm);
			break;
		}
		if (ch == '\\') {
			LoadChar(ch);
			if (ch == '\n')
				LineNumber++;
			ch = quoted(ch);
		}
		str[pos++] = ch;
		if (pos == str_size)
			str = Srealloc(str, str_size += RSTRSIZE);
		LoadChar(ch);
	}
	str[pos++] = '\0'; /* for filenames etc. */
	*plen = pos;
	return str;
}

int
quoted(ch)
	register int ch;
{	
	/*	quoted() replaces an escaped character sequence by the
		character meant.
	*/
	/* first char after backslash already in ch */
	if (!is_oct(ch)) {		/* a quoted char */
		switch (ch) {
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
		}
	}
	else {				/* a quoted octal */
		register int oct = 0, cnt = 0;

		do {
			oct = oct*8 + (ch-'0');
			LoadChar(ch);
		} while (is_oct(ch) && ++cnt < 3);
		PushBack();
		ch = oct;
	}
	return ch&0377;
}

/* provisional */
int
val_in_base(ch, base)
	register int ch;
{
	return
		is_dig(ch) ? ch - '0' :
		base != 16 ? -1 :
		is_hex(ch) ? (ch - 'a' + 10) & 017 :
		-1;
}
