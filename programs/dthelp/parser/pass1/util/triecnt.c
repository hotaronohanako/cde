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
/* $XConsortium: triecnt.c /main/3 1995/11/08 10:37:45 rswiston $ */
/*
                   Copyright 1986, 1987, 1988, 1989 Hewlett-Packard Co.
*/

/* Triecnt.c contains procedures for writing out a trie structure */

#include <stdio.h>
#include "basic.h"
#include "trie.h"

void countdown(M_TRIE *parent, int *count);

void dumpnode(LOGICAL *first, FILE *file, M_TRIE *trieptr, int *count,
    void (*proc)(FILE *file, void *value));

void printval(FILE *file, void *value);

/* Count the descendants of a node in order to generate declarations for
   the packed form of a trie*/
void countdown(M_TRIE *parent, int *count)
  {
    M_TRIE *child ;

    for (child = parent->data ; child ; child = child->next) {
      (*count)++ ;
      if (child->symbol) countdown(child, count) ;
      }
    }

/* Output descendants of a node for the declaration of a trie, in packed
   or normal format*/
void dumpnode(LOGICAL *first, FILE *file, M_TRIE *trieptr, int *count,
              void (*proc) (FILE *file, void *value))
  {
    M_TRIE *p ;
    int savecount ;

    for (p = trieptr->data ; p ; p = p->next) (*count)++ ;
    savecount = *count ;

    for (p = trieptr->data ; p ; p = p->next) {
      /* generate a child */
      if (*first) *first = FALSE ;
      else fprintf(file, ",\n") ;
      fprintf(file, "  {") ;
      if (p->next) fprintf(file, "TRUE, ") ;
      else fprintf(file, "FALSE, ") ;
      fprintf(file, "%d", (int)p->symbol) ;
      if (p->symbol) fprintf(file, ", %d}", *count) ;
      else { (*proc)(file, p->data) ; fprintf(file, "}") ; }

      /* count the children of the child*/
      if (p->symbol) countdown(p, count) ;
      }

    *count = savecount ;
    for (p = trieptr->data ; p ; p = p->next)
      if (p->symbol) dumpnode(first, file, p, count, proc) ;
    }


/* Most common procedure passed to dumpptrie */
void printval(FILE *file, void *value)
  {
    fprintf(file, ", %ld", (long) value) ;
    }
