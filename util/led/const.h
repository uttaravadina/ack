/* $Header$ */

typedef int		bool;

#define FALSE		0
#define TRUE		1

#define WIDTH		8		/* Number of bits in a byte.	*/
#define BYTEMASK	0xFF		/* Mask to get low order byte.	*/

#define RFLAG		0x01		/* -r flag given.		*/
#define SFLAG		0x02		/* -s flag given.		*/
#define CFLAG		0x04		/* -c flag given.		*/

#define PLAIN		0		/* Input file is a normal file.	*/
#define ARCHIVE		1		/* Input file is an archive.	*/

#define FIRST		1		/* Pass number.			*/
#define SECOND		2		/* Idem.			*/

#define BADOFF		((ind_t)-1)
