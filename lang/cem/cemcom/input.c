/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id$ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inputtype.h"
#include "file_info.h"
#include "input.h"
#define INP_TYPE	struct file_info
#define INP_VAR		finfo
struct file_info	finfo;
extern int		nestlevel;
#include "nopp.h"
#include <inp_pkg.body>
#include <alloc.h>

#include	"dbsymtab.h"
#ifndef NOPP
#ifdef DBSYMTAB
#include <stb.h>
#include <em.h>
extern int	IncludeLevel;
extern char	options[];
#endif
char *
getwdir(fn)
	register char *fn;
{
	register char *p;
	char *strrchr();

	p = strrchr(fn, '/');
	while (p && *(p + 1) == '\0') {	/* remove trailing /'s */
		*p = '\0';
		p = strrchr(fn, '/');
	}

	if (fn[0] == '\0' || (fn[0] == '/' && p == &fn[0])) /* absolute path */
		return "";
	if (p) {
		*p = '\0';
		fn = Salloc(fn, p - &fn[0] + 1);
		*p = '/';
		return fn;
	}
	return "";
}

int	InputLevel;
#endif /* NOPP */

int	NoUnstack;

AtEoIT()
{
#ifndef NOPP
	/* if (NoUnstack) lexwarning("unexpected EOF"); ??? */
	DoUnstack();
	InputLevel--;
#endif /* NOPP */
	return 0;
}

AtEoIF()
{
#ifndef NOPP

	if (nestlevel != nestlow) lexwarning("missing #endif");
	else
#endif /* NOPP */
	if (NoUnstack) lexerror("unexpected EOF");
#ifndef NOPP
	nestlevel = nestlow;
#ifdef DBSYMTAB
	if (options['g'] && IncludeLevel > 0) {
		C_ms_stb_cst(FileName, N_EINCL, 0, (arith) 0);
	}
	IncludeLevel--;
#endif
#endif
	return 0;
}
