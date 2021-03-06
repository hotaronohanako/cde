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
/* $XConsortium: csoset.c /main/2 1996/05/09 04:00:24 drk $ */
/*
 *   COMPONENT_NAME: austext
 *
 *   FUNCTIONS: d_csoset
 *
 *   ORIGINS: 157
 *
 *   OBJECT CODE ONLY SOURCE MATERIALS
 */
/*-----------------------------------------------------------------------
   csoset.c -- db_VISTA current set owner database address set module.

   (C) Copyright 1987 by Raima Corporation.
-----------------------------------------------------------------------*/

/* ********************** EDIT HISTORY *******************************

 SCR    DATE    INI                   DESCRIPTION
----- --------- --- -----------------------------------------------------
      04-Aug-88 RTK MULTI_TASK changes
*/

#include <stdio.h>
#include "vista.h"
#include "dbtype.h"


/* Set current set owner
*/
int
d_csoset(
int set,      /* Set table entry */
DB_ADDR *dba, /* db address of record to become current */
int dbn       /* database number */
)
{
   INT type;
   char *ptr;
   SET_ENTRY *set_ptr;

   DB_ENTER(DB_ID TASK_ID LOCK_SET(SET_IO));

   if (nset_check(set, &set, (SET_ENTRY * *)&set_ptr) != S_OKAY)
      RETURN( db_status );

   if ( dba == NULL ) {
      curr_own[set] = curr_mem[set] = NULL_DBA;
   }
   else if ( check_dba(*dba) == S_OKAY ) {
      /* get the record type */
      if ( dio_read( *dba, (char * *)&ptr , NOPGHOLD) ) RETURN( db_status );
      bytecpy( &type, ptr, sizeof(INT) );
      type &= ~RLBMASK;
      type += curr_db_table->rt_offset;

      if (set_ptr->st_own_rt != type)
	 RETURN( dberr( S_INVOWN ) );

      curr_own[set] = *dba;
      curr_mem[set] = NULL_DBA;
   }
   RETURN( db_status );
}
/* vpp -nOS2 -dUNIX -nBSD -nVANILLA_BSD -nVMS -nMEMLOCK -nWINDOWS -nFAR_ALLOC -f/usr/users/master/config/nonwin csoset.c */
