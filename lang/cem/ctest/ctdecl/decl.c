/*
 * (c) copyright 1983 by the Vrije Universiteit, Amsterdam, The Netherlands.
 *
 *          This product is part of the Amsterdam Compiler Kit.
 *
 * Permission to use, sell, duplicate or disclose this software must be
 * obtained in writing. Requests for such permissions may be sent to
 *
 *      Dr. Andrew S. Tanenbaum
 *      Wiskundig Seminarium
 *      Vrije Universiteit
 *      Postbox 7161
 *      1007 MC Amsterdam
 *      The Netherlands
 *
 */

/* Author: E.G. Keizer */

char rcs_id[] = "$Header$" ;

/* Test a few declaration features */
/* Such as:
	forward function declarations,
	redeclarations,
	pointer to function declarations.
*/

static int	sqr() ; /* forward declarations */
extern int	sqrt();

main() {
	fdcl() ;
	hidden() ;
	return 0 ;
}

fdcl() {
	int (*a[2])() ;

	printf("sqr(4) %d\n",sqr(4)) ;

	a[0]=sqr ; a[1]=sqrt ;
	printf("(*a[0])(16) %d\n",(*a[0])(16) ) ;
	printf("(*a[1])( (*a[0])(3) ) %d\n", (*a[1])( (*a[0])(3) ) ) ;
}

static int sqr(par) int par ; {
	return par*par ;
}

int sqrt(par) int par ; {
	int x1,x2 ;
	int i ;

	if ( par<0 ) return -1 ;
	x1 = par ;
	i=0 ;
	do {
		x2 = x1 ;
		x1 = ( x2*x2 + par ) / (2*x2) ;
		if ( i++>=100 ) return -2 ;
	} while ( ( x2<x1 ? x1-x2 : x2-x1 ) > 0 ) ;
	return (x1+x2)/2 ;
}

int a = -8 ;

hidden() {
	hide() ;
	printf("a outside hide %d\n",a) ;
}

int hide() {
	int a ;

	a = 4 ;
	printf("a in hide %d\n",a) ;
	{
		int a ;

		a = 16 ;
		printf("a in in hide %d\n",a) ;

	}
	printf("a in hide %d\n",a) ;
}
