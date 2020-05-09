/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $TOG: cppsetup.c /main/18 1998/02/06 11:09:35 kaleb $ */
/*

Copyright (c) 1993, 1994, 1998  The Open Group

All Rights Reserved.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

#include "def.h"

#ifdef	CPP
/*
 * This file is strictly for the sake of cpy.y and yylex.c (if
 * you indeed have the source for cpp).
 */
#define IB 1
#define SB 2
#define NB 4
#define CB 8
#define QB 16
#define WB 32
#define SALT '#'
#if pdp11 | vax | ns16000 | mc68000 | ibm032
#define COFF 128
#else
#define COFF 0
#endif
/*
 * These variables used by cpy.y and yylex.c
 */
extern char	*outp, *inp, *newp, *pend;
extern char	*ptrtab;
extern char	fastab[];
extern char	slotab[];

/*
 * cppsetup
 */
struct filepointer	*currentfile;
struct inclist		*currentinc;

cppsetup(line, filep, inc)
	char	*line;
	struct filepointer	*filep;
	struct inclist		*inc;
{
	char *p, savec;
	static boolean setupdone = FALSE;
	boolean	value;

	if (!setupdone) {
		cpp_varsetup();
		setupdone = TRUE;
	}

	currentfile = filep;
	currentinc = inc;
	inp = newp = line;
	for (p=newp; *p; p++)
		;

	/*
	 * put a newline back on the end, and set up pend, etc.
	 */
	*p++ = '\n';
	savec = *p;
	*p = '\0';
	pend = p;

	ptrtab = slotab+COFF;
	*--inp = SALT; 
	outp=inp; 
	value = yyparse();
	*p = savec;
	return(value);
}

struct symtab **lookup(symbol)
	char	*symbol;
{
	static struct symtab    *undefined;
	struct symtab   **sp;

	sp = isdefined(symbol, currentinc, NULL);
	if (sp == NULL) {
		sp = &undefined;
		(*sp)->s_value = NULL;
	}
	return (sp);
}

pperror(tag, x0,x1,x2,x3,x4)
	int	tag,x0,x1,x2,x3,x4;
{
	warning("\"%s\", line %d: ", currentinc->i_file, currentfile->f_line);
	warning(x0,x1,x2,x3,x4);
}


yyerror(s)
	char	*s;
{
	fatalerr("Fatal error: %s\n", s);
}
#else /* not CPP */

#include "ifparser.h"
struct _parse_data {
    struct filepointer *filep;
    struct inclist *inc;
    const char *line;
};

static const char *
my_if_errors (ip, cp, expecting)
    IfParser *ip;
    const char *cp;
    const char *expecting;
{
    struct _parse_data *pd = (struct _parse_data *) ip->data;
    int lineno = pd->filep->f_line;
    char *filename = pd->inc->i_file;
    char prefix[300];
    int prefixlen;
    int i;

    snprintf (prefix, 300, "\"%s\":%d", filename, lineno);
    prefixlen = strlen(prefix);
    fprintf (stderr, "%s:  %s", prefix, pd->line);
    i = cp - pd->line;
    if (i > 0 && pd->line[i-1] != '\n') {
	putc ('\n', stderr);
    }
    for (i += prefixlen + 3; i > 0; i--) {
	putc (' ', stderr);
    }
    fprintf (stderr, "^--- expecting %s\n", expecting);
    return NULL;
}


#define MAXNAMELEN 256

static struct symtab **
lookup_variable (ip, var, len)
    IfParser *ip;
    const char *var;
    int len;
{
    char tmpbuf[MAXNAMELEN + 1];
    struct _parse_data *pd = (struct _parse_data *) ip->data;

    if (len > MAXNAMELEN)
	return 0;

    strncpy (tmpbuf, var, len);
    tmpbuf[len] = '\0';
    return isdefined (tmpbuf, pd->inc, NULL);
}


static int
my_eval_defined (ip, var, len)
    IfParser *ip;
    const char *var;
    int len;
{
    if (lookup_variable (ip, var, len))
	return 1;
    else
	return 0;
}

#define isvarfirstletter(ccc) (isalpha(ccc) || (ccc) == '_')

static long
my_eval_variable (ip, var, len)
    IfParser *ip;
    const char *var;
    int len;
{
    long val;
    struct symtab **s;

    s = lookup_variable (ip, var, len);
    if (!s)
	return 0;
    do {
	var = (*s)->s_value;
	if (!isvarfirstletter((int)*var) || !strcmp((*s)->s_name, var))
	    break;
	s = lookup_variable (ip, var, strlen(var));
    } while (s);

    var = ParseIfExpression(ip, var, &val);
    if (var && *var) debug(4, ("extraneous: '%s'\n", var));
    return val;
}


int cppsetup(line, filep, inc)
	char	*line;
	struct filepointer	*filep;
	struct inclist		*inc;
{
    IfParser ip;
    struct _parse_data pd;
    long val = 0;

    pd.filep = filep;
    pd.inc = inc;
    pd.line = line;
    ip.funcs.handle_error = my_if_errors;
    ip.funcs.eval_defined = my_eval_defined;
    ip.funcs.eval_variable = my_eval_variable;
    ip.data = (char *) &pd;

    (void) ParseIfExpression (&ip, line, &val);
    if (val)
	return IF;
    else
	return IFFALSE;
}
#endif /* CPP */
