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
/* $XConsortium: signals.c /main/5 1996/09/06 17:03:12 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*        THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF        *
*                    AT&T BELL LABORATORIES                    *
*         AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN         *
*            ACCORDANCE WITH APPLICABLE AGREEMENTS             *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*              Unpublished & Not for Publication               *
*                     All Rights Reserved                      *
*                                                              *
*       The copyright notice above does not evidence any       *
*      actual or intended publication of such source code      *
*                                                              *
*               This software was created by the               *
*           Advanced Software Technology Department            *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                    {research,attmail}!dgk                    *
*                                                              *
***************************************************************/

/* : : generated by proto : : */

#if !defined(__PROTO__)
#if defined(__STDC__) || defined(__cplusplus) || defined(_proto) || defined(c_plusplus)
#if defined(__cplusplus)
#define __MANGLE__	"C"
#else
#define __MANGLE__
#endif
#define __STDARG__
#define __PROTO__(x)	x
#define __OTORP__(x)
#define __PARAM__(n,o)	n
#if !defined(__STDC__) && !defined(__cplusplus)
#if !defined(c_plusplus)
#define const
#endif
#define signed
#define void		int
#define volatile
#define __V_		char
#else
#define __V_		void
#endif
#else
#define __PROTO__(x)	()
#define __OTORP__(x)	x
#define __PARAM__(n,o)	o
#define __MANGLE__
#define __V_		char
#define const
#define signed
#define void		int
#define volatile
#endif
#if defined(__cplusplus) || defined(c_plusplus)
#define __VARARG__	...
#else
#define __VARARG__
#endif
#if defined(__STDARG__)
#define __VA_START__(p,a)	va_start(p,a)
#else
#define __VA_START__(p,a)	va_start(p)
#endif
#endif
#include	<ast.h>
#include	"shtable.h"
#include	"fault.h"

#if defined(SIGCLD) && !defined(SIGCHLD)
#   define SIGCHLD	SIGCLD
#endif

#define VAL(sig,mode)	((sig+1)|(mode)<<SH_SIGBITS)
#define TRAP(n)		(((n)|SH_TRAP)-1)

/*
 * This is a table that gives numbers and default settings to each signal
 * The signal numbers go in the low bits and the attributes go in the high bits
 */

static struct shtable2 _shtab_signals[] =
{
#ifdef SIGABRT
	"ABRT",		VAL(SIGABRT,SH_SIGDONE), 	"Abort",
#endif /*SIGABRT */
#ifdef SIGAIO
	"AIO",		VAL(SIGAIO,SH_SIGIGNORE), 	"Asynchronous I/O",
#endif /*SIGAIO */
#ifdef SIGALRM
	"ALRM",		VAL(SIGALRM,SH_SIGFAULT),	"Alarm call",
#endif /* SIGALRM */
#ifdef SIGBUS
	"BUS",		VAL(SIGBUS,SH_SIGDONE),		"Bus error",
#endif /* SIGBUS */
#ifdef SIGCHLD
	"CHLD",		VAL(SIGCHLD,SH_SIGFAULT), 	"Death of Child",
#   ifdef SIGCLD
#	if SIGCLD!=SIGCHLD
	    "CLD",	VAL(SIGCLD,SH_SIGFAULT),	"Death of Child",
#	endif
#   endif	/* SIGCLD */
#else
#   ifdef SIGCLD
	"CLD",		VAL(SIGCLD,SH_SIGFAULT),	"Death of Child",
#   endif	/* SIGCLD */
#endif	/* SIGCHLD */
#ifdef SIGCONT
	"CONT",		VAL(SIGCONT,SH_SIGIGNORE),	"Stopped process continued",
#endif	/* SIGCONT */
	"DEBUG",	VAL(TRAP(SH_DEBUGTRAP),0),	"",
#ifdef SIGDIL
	"DIL",		VAL(SIGDIL,0),			"DIL signal",
#endif	/* SIGDIL */
#ifdef SIGEMT
	"EMT",		VAL(SIGEMT,SH_SIGDONE),		"EMT trap",
#endif	/* SIGEMT */
	"ERR",		VAL(TRAP(SH_ERRTRAP),0),	"",
	"EXIT",		VAL(0,0),			"",
	"FPE",		VAL(SIGFPE,SH_SIGDONE),		"Floating exception",
#ifdef SIGFREEZE
	"FREEZE",	VAL(SIGFREEZE,SH_SIGIGNORE),	"Special signal used by CPR",
#endif	/* SIGFREEZE */
	"HUP",		VAL(SIGHUP,SH_SIGDONE),		"Hangup",
	"ILL",		VAL(SIGILL,SH_SIGDONE),		"Illegal instruction",
#ifdef JOBS
	"INT",		VAL(SIGINT,SH_SIGINTERACTIVE),	"Interrupt",
#else
	"INT",		VAL(SIGINT,SH_SIGINTERACTIVE),	"",
#endif /* JOBS */
#ifdef SIGIO
	"IO",		VAL(SIGIO,SH_SIGIGNORE),	"IO signal",
#endif	/* SIGIO */
#ifdef SIGIOT
	"IOT",		VAL(SIGIOT,SH_SIGDONE),		"Abort",
#endif	/* SIGIOT */
	"KEYBD",	VAL(TRAP(SH_KEYTRAP),0),	"",
#ifdef SIGKILL
	"KILL",		VAL(SIGKILL,0),			"Killed",
#endif /* SIGKILL */
#ifdef SIGLAB
	"LAB",		VAL(SIGLAB,0),			"Security label changed",
#endif	/* SIGLAB */
#ifdef SIGLOST
	"LOST",		VAL(SIGLOST,SH_SIGDONE),	"Resources lost",
#endif	/* SIGLOST */
#ifdef SIGLWP
	"LWP",		VAL(SIGLWP,SH_SIGIGNORE),	"Special signal used by thread library",
#endif	/* SIGLWP */
#ifdef SIGPHONE
	"PHONE",	VAL(SIGPHONE,0),		"Phone interrupt",
#endif	/* SIGPHONE */
#ifdef SIGPIPE
#ifdef JOBS
	"PIPE",		VAL(SIGPIPE,SH_SIGDONE),	"Broken Pipe",
#else
	"PIPE",		VAL(SIGPIPE,SH_SIGDONE),	 "",
#endif /* JOBS */
#endif /* SIGPIPE */
#ifdef SIGPOLL
	"POLL",		VAL(SIGPOLL,SH_SIGDONE),	"Polling alarm",
#endif	/* SIGPOLL */
#ifdef SIGPROF
	"PROF",		VAL(SIGPROF,SH_SIGDONE), 	"Profiling time alarm",
#endif	/* SIGPROF */
#ifdef SIGPWR
#   if SIGPWR>0
	"PWR",		VAL(SIGPWR,SH_SIGIGNORE),	"Power fail",
#   endif
#endif	/* SIGPWR */
#ifdef SIGQUIT
	"QUIT",		VAL(SIGQUIT,SH_SIGDONE|SH_SIGINTERACTIVE),	"Quit",
#if defined(_SIGRTMAX) || defined(SIGRTMAX)
	"RTMAX",	0 /* Filled in at run-time */,	"Lowest priority realtime signal",
#endif	/* _SIGRTMAX || SIGRTMAX */
#if defined(_SIGRTMIN) || defined(SIGRTMIN)
	"RTMIN",	0 /* Filled in at run-time */,	"Highest priority realtime signal",
#endif	/* _SIGRTMIN || SIGRTMIN */
#endif	/* SIGQUIT */
	"SEGV",		VAL(SIGSEGV,0),			"Memory fault",
#ifdef SIGSTOP
	"STOP",		VAL(SIGSTOP,0),			"Stopped (SIGSTOP)",
#endif	/* SIGSTOP */
#ifdef SIGSYS
	"SYS",		VAL(SIGSYS,SH_SIGDONE),		"Bad system call",
#endif	/* SIGSYS */
	"TERM",		VAL(SIGTERM,SH_SIGDONE|SH_SIGINTERACTIVE),	"Terminated",
#ifdef SIGTINT
#   ifdef JOBS
	"TINT",		VAL(SIGTINT,0),			"Interrupt",
#   else
	"TINT",		VAL(SIGTINT,0),			"".
#   endif /* JOBS */
#endif	/* SIGTINT */
#ifdef SIGTRAP
	"TRAP",		VAL(SIGTRAP,SH_SIGDONE),	"Trace/BPT trap",
#endif	/* SIGTRAP */
#ifdef SIGTSTP
	"TSTP",		VAL(SIGTSTP,0),			"Stopped",
#endif	/* SIGTSTP */
#ifdef SIGTTIN
	"TTIN",		VAL(SIGTTIN,0),			"Stopped (SIGTTIN)",
#endif	/* SIGTTIN */
#ifdef SIGTTOU
	"TTOU",		VAL(SIGTTOU,0),			"Stopped(SIGTTOU)",
#endif	/* SIGTTOU */
#ifdef SIGURG
	"URG",		VAL(SIGURG,SH_SIGIGNORE),	"Socket interrupt",
#endif	/* SIGURG */
#ifdef SIGUSR1
	"USR1",		VAL(SIGUSR1,SH_SIGDONE),	 "User signal 1",
#endif	/* SIGUSR1 */
#ifdef SIGUSR2
	"USR2",		VAL(SIGUSR2,SH_SIGDONE),	 "User signal 2",
#endif	/* SIGUSR2 */
#ifdef SIGVTALRM
	"VTALRM",	VAL(SIGVTALRM,SH_SIGDONE),	"Virtual time alarm",
#endif	/* SIGVTALRM */
#ifdef SIGWINCH
	"WINCH",	VAL(SIGWINCH,SH_SIGIGNORE),	"Window size change",
#endif	/* SIGWINCH */
#ifdef SIGWINDOW
	"WINDOW",	VAL(SIGWINDOW,SH_SIGIGNORE),	"Window size change",
#endif	/* SIGWINDOW */
#ifdef SIGWIND
	"WIND",		VAL(SIGWIND,SH_SIGIGNORE),	"Window size change",
#endif	/* SIGWIND */
#ifdef SIGMIGRATE
	"MIGRATE",		VAL(SIGMIGRATE,0),	"Migrate process",
#endif	/* SIGMIGRATE */
#ifdef SIGDANGER
	"DANGER",		VAL(SIGDANGER,0),	"System crash soon",
#endif	/* SIGDANGER */
#ifdef SIGSOUND
	"SOUND",		VAL(SIGSOUND,0),	"Sound completed",
#endif	/* SIGSOUND */
#ifdef SIGTHAW
	"THAW",			VAL(SIGTHAW,SH_SIGIGNORE),	"Special signal used by CPR",
#endif	/* SIGTHAW */
#ifdef SIGWAITING
	"WAITING",		VAL(SIGWAITING,SH_SIGIGNORE),	"Process lpws are blocked",
#endif	/* SIGWAITING */
#ifdef SIGXCPU
	"XCPU",		VAL(SIGXCPU,SH_SIGDONE|SH_SIGINTERACTIVE),	"Exceeded CPU time limit",
#endif	/* SIGXCPU */
#ifdef SIGXFSZ
	"XFSZ",		VAL(SIGXFSZ,SH_SIGDONE|SH_SIGINTERACTIVE),	"Exceeded file size limit",
#endif	/* SIGXFSZ */
	"",	0,	0
};

const struct shtable2 *shtab_signals = _shtab_signals;

/*
 * Fill entries whose values can be determined at run-time
 * rather than at compile time.  Currently only SIGRTMAX/MIN.
 */
void init_shtab_signals __PARAM__((void), ())
{
    struct shtable2 *tp = _shtab_signals;
    static char init_done = 0;

    if (init_done)
	return;

#if defined(_SIGRTMAX) || defined(SIGRTMAX)
    while (tp->sh_number)
	tp++;

    /* First one alphabetically is RTMAX. */
# ifdef _SIGRTMAX
    tp->sh_number = VAL(_SIGRTMAX, 0);
# else /* SIGRTMAX */
    tp->sh_number = VAL(SIGRTMAX, 0);
# endif
    tp++;

#endif /* _SIGRTMAX || SIGRTMAX */

#if defined(_SIGRTMIN) || defined(SIGRTMIN)
    while (tp->sh_number)
	tp++;

    /* Second is RTMIN */
# ifdef _SIGRTMIN
    tp->sh_number = VAL(_SIGRTMIN, 0);
# else /* SIGRTMIN */
    tp->sh_number = VAL(SIGRTMIN, 0);
# endif

#endif	/* _SIGRTMIN || SIGRTMIN */

    init_done = 1;
}