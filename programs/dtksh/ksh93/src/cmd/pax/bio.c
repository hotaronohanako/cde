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
/* $XConsortium: bio.c /main/3 1995/11/01 16:58:37 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*         THIS IS PROPRIETARY SOURCE CODE LICENSED BY          *
*                          AT&T CORP.                          *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*                     All Rights Reserved                      *
*                                                              *
*           This software is licensed by AT&T Corp.            *
*       under the terms and conditions of the license in       *
*       http://www.research.att.com/orgs/ssr/book/reuse        *
*                                                              *
*               This software was created by the               *
*           Software Engineering Research Department           *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                     gsf@research.att.com                     *
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
#include "pax.h"

#include "FEATURE/mtio"
#if _sys_mtio
#include <ast_tty.h>
#include <sys/mtio.h>
#endif
#ifdef MTIOCTOP
#if defined(MTIOBSF) && !defined(MTBSF)
#define MTBSF	MTIOBSF
#endif
#if defined(MTIOBSR) && !defined(MTBSR)
#define MTBSR	MTIOBSR
#endif
#if defined(MTIOEOM) && !defined(MTEOM)
#define MTEOM	MTIOEOM
#endif
#if defined(MTIOFSF) && !defined(MTFSF)
#define MTFSF	MTIOFSF
#endif
#if defined(MTIOWEOF) && !defined(MTWEOF)
#define MTWEOF	MTIOWEOF
#endif
#if !defined(MTBSF) || !defined(MTBSR) || !defined(MTWEOF) || defined(__hppa)/*hppa-compiler-signal-10*/
#undef	MTIOCTOP
#endif
#endif

#if 0 && DEBUG

/*
 * -o blok=i	input is BLOK file
 * -o blok=o	output file is BLOK file
 */

static int
blokread __PARAM__((Archive_t* ap, char* buf, int n), (ap, buf, n)) __OTORP__(Archive_t* ap; char* buf; int n;){
	int		i;
	int		j;
	char			c;

	static int		eof;

	if (!ap->io.blokflag)
	{
		ap->io.blokflag = 1;
		eof = 0;
		if ((i = read(ap->io.fd, buf, ap->io.blok ? 4 : n)) < 4 || !strneq(buf, "\002\014\017\013", 4))
		{
			if (ap->io.blok) error(3, "%s: input archive is not a BLOK file", ap->name);
			return(i);
		}
		if (i > 4 && lseek(ap->io.fd, 4L, SEEK_SET) != 4L)
			error(3, "%s: cannot seek on input archive BLOK file -- use -o blok=i", ap->name);
		ap->io.blok = 1;
	}
	if (ap->io.blok)
	{
		j = 0;
		do
		{
			if ((i = read(ap->io.fd, &c, 1)) < 1)
				return(i < 0 && ++eof == 1 ? 0 : -1);
			j <<= 7;
			j |= c & 0177;
		} while (c & 0200);
		if (j > 0)
		{
			if (j > n)
				error(2, "%s: blokread buffer overflow (%d>%d)", ap->name, j, n);
			if ((i = read(ap->io.fd, buf, j)) != j)
				error(2, "%s: blokread blocking error", ap->name);
		}
		else i = 0;
	}
	else i = read(ap->io.fd, buf, n);
	return(i);
}

static int
blokwrite __PARAM__((Archive_t* ap, char* buf, int n), (ap, buf, n)) __OTORP__(Archive_t* ap; char* buf; int n;){
	char*	s;
	int	i;
	int	j;
	char		blk[9];

	if (ap->io.blok)
	{
		s = blk;
		if (!ap->io.blokflag)
		{
			ap->io.blokflag = 1;
			*s++ = 002;
			*s++ = 014;
			*s++ = 017;
			*s++ = 013;
		}
		i = 0;
		if (j = (n >> 21) & 0177)
		{
			*s++ = j | 0200;
			i = 1;
		}
		if ((j = (n >> 14) & 0177) || i)
		{
			*s++ = j | 0200;
			i = 1;
		}
		if ((j = (n >> 7) & 0177) || i)
		{
			*s++ = j | 0200;
			i = 1;
		}
		*s++ = n & 0177;
		j = s - blk;
		if ((i = write(ap->io.fd, blk, j)) != j)
			error(ERROR_SYSTEM|3, "%s: blokwrite count write error (%d!=%d)", ap->name, i, j);
		if (n <= 0) i = n;
		else if ((i = write(ap->io.fd, buf, n)) != n)
			error(ERROR_SYSTEM|3, "%s: blokwrite data write error (%d!=%d", ap->name, i, n);
	}
	else i = write(ap->io.fd, buf, n);
	return(i);
}

#define read(f,b,n)	blokread(f,b,n)
#define write(f,b,n)	blokwrite(f,b,n)

#endif

/*
 * initialize buffered io
 */

void
binit __PARAM__((Archive_t* ap), (ap)) __OTORP__(Archive_t* ap;){
	unsigned long	n;

	if (ap->delta)
		ap->delta->hdr = ap->delta->hdrbuf;
	n = 2 * state.buffersize;
	if (!(ap->io.mode & O_WRONLY))
		n += MAXUNREAD;
	else if (!(format[ap->format].flags & OUT))
		error(3, "%s: archive format not supported on output" , format[ap->format].name);
	if (!(ap->io.buffer = newof(0, char, n, 0)))
		error(3, "%s: cannot allocate buffer", ap->name);
	ap->io.next = ap->io.last = ap->io.buffer;
}

/*
 * skip files on tape fd
 */

int
bskip __PARAM__((Archive_t* ap), (ap)) __OTORP__(Archive_t* ap;){
	long		c;
	int		skip = ap->io.skip;
#ifdef MTIOCTOP
	struct mtop	mt;
#ifdef MTEOM
	int		mteom = 1;
#endif
#ifdef MTFSF
	int		mtfsf = 1;
#endif
#endif

	if (ap->io.mode)
	{
		ap->io.next = ap->io.last = ap->io.buffer + MAXUNREAD;
		ap->io.eof = 0;
	}
	while (skip)
	{
#ifdef MTIOCTOP
#ifdef MTEOM
		if (skip < 0 && mteom)
		{
			mt.mt_op = MTEOM;
			mt.mt_count = 1;
			if (ioctl(ap->io.fd, MTIOCTOP, &mt) >= 0)
			{
				if (ap->io.mode) ap->io.eof = 1;
				break;
			}
			mteom = 0;
		}
#endif
#ifdef MTFSF
		if (mtfsf)
		{
			mt.mt_op = MTFSF;
			mt.mt_count = 1;
			if (ioctl(ap->io.fd, MTIOCTOP, &mt) >= 0)
			{
				skip--;
				continue;
			}
			if (errno != ENOTTY)
			{
				if (ap->io.mode) ap->io.eof = 1;
				break;
			}
			mtfsf = 0;
		}
#endif
#endif
		while ((c = read(ap->io.fd, state.tmp.buffer, state.tmp.buffersize)) > 0);
		if (c < 0)
		{
			if (ap->io.mode) ap->io.eof = 1;
			break;
		}
		skip--;
	}
	return(0);
}

/*
 * fill input buffer at ap->io.last
 * if must!=0 then EOF causes query for next input volume file
 */

static int
bfill __PARAM__((Archive_t* ap, int must), (ap, must)) __OTORP__(Archive_t* ap; int must;){
	int	c;

	if (ap->io.eof) return(-1);
	if (ap->io.skip) ap->io.skip = bskip(ap);
	while ((c = read(ap->io.fd, ap->io.last, state.buffersize)) <= 0)
	{
		if (must) newio(ap, c, 0);
		else
		{
			ap->io.eof = 1;
			return(-1);
		}
	}
	message((-8, "read(%s,%d): %-.*s%s", ap->name, c, c > 32 ? 32 : c, ap->io.last, c > 32 ? "..." : ""));
	ap->io.eof = 0;
	ap->io.last += c;
	return(0);
}

/*
 * buffered char input
 * at least n chars required, m chars max
 * if b is 0 then n chars are skipped
 * if must!=0 then EOF causes query for next input volume file
 */

int
bread __PARAM__((Archive_t* ap, __V_* ab, long n, long m, int must), (ap, ab, n, m, must)) __OTORP__(Archive_t* ap; __V_* ab; long n; long m; int must;){
	char*	b = (char*)ab;
	int	c;
	char*	ob;

	if (ap->io.eof) return(-1);
	if (m <= 0) return(0);
	ob = b;
	if (ap->io.blocked)
	{
		if (!b) b = state.tmp.buffer;
		while ((c = read(ap->io.fd, b, m)) <= 0)
		{
			if (must) newio(ap, c, 0);
			else if (ap->io.empty)
			{
				ap->io.eof = 1;
				return(-1);
			}
			else
			{
				if (c < 0) ap->io.eof = 1;
				else
				{
					ap->io.empty = 1;
#if DEBUG
					if (ob) message((-7, "bread(%s,%d@%ld):", ap->name, c, ap->io.count));
#endif
				}
				return(c);
			}
		}
		ap->io.empty = 0;
		if (must && c < n) return(-1);
		ap->io.count += c;
		if (ap->sum > 0)
		{
			ap->memsum = memsum(b, c, ap->memsum);
			ap->old.memsum = omemsum(b, c, ap->old.memsum);
		}
#if DEBUG
		if (ob) message((-7, "bread(%s,%d@%ld): %-.*s%s", ap->name, c, ap->io.count, c > 32 ? 32 : c, ob, c > 32 ? "..." : ""));
#endif
		return(c);
	}
	else
	{
		if (n <= 0) n = m;
		else m = n;
		for (;;)
		{
			if (n > (c = ap->io.last - ap->io.next))
			{
				if (c > 0)
				{
					if (ap->sum > 0)
					{
						ap->memsum = memsum(ap->io.next, c, ap->memsum);
						ap->old.memsum = omemsum(ap->io.next, c, ap->old.memsum);
					}
					if (ob) memcpy(b, ap->io.next, c);
					b += c;
					n -= c;
					ap->io.count += c;
				}
				ap->io.next = ap->io.last = ap->io.buffer + MAXUNREAD;
				if (!ob && ap->sum <= 0)
				{
					if (!ap->io.seekcheck)
					{
						struct stat	st;

						ap->io.seekcheck = 1;
						if (lseek(ap->io.fd, 0L, SEEK_CUR) == (ap->io.count + ap->io.last - ap->io.next) && fstat(ap->io.fd, &st) != -1 && st.st_size > 0)
							ap->io.seekable = 1;
					}
					if (ap->io.seekable && (c = n / BUFFERSIZE) && lseek(ap->io.fd, (long)(c *= BUFFERSIZE), SEEK_CUR) != -1)
					{
						b += c;
						n -= c;
						ap->io.count += c;
						message((-7, "bread(%s) skip(%d@%ld) [%ld]", ap->name, c, ap->io.count));
					}
				}
				if (bfill(ap, must) < 0)
				{
					if (ob && (c = (b - ob)))
					{
						bunread(ap, ob, c);
						return(0);
					}
					return(-1);
				}
			}
			else
			{
				if (ap->sum > 0)
				{
					ap->memsum = memsum(ap->io.next, n, ap->memsum);
					ap->old.memsum = omemsum(ap->io.next, n, ap->old.memsum);
				}
				if (ob) memcpy(b, ap->io.next, n);
				ap->io.next += n;
				ap->io.count += n;
#if DEBUG
				if (ob)
				{
					n += b - ob;
					message((-7, "bread(%s,%d@%ld): %-.*s%s", ap->name, n, ap->io.count, n > 32 ? 32 : n, ob, n > 32 ? "..." : ""));
				}
#endif
				return(m);
			}
		}
	}
}

/*
 * pushback for next bread()
 */

void
bunread __PARAM__((Archive_t* ap, __V_* ab, int n), (ap, ab, n)) __OTORP__(Archive_t* ap; __V_* ab; int n;){
	char*	b = (char*)ab;

	ap->io.eof = 0;
	ap->io.count -= n;
	if ((ap->io.next -= n) < ap->io.buffer + MAXUNREAD)
	{
		if (ap->io.next < ap->io.buffer)
			error(PANIC, "bunread(%s,%d): too much pushback", ap->name, n);
		memcpy(ap->io.next, b, n);
	}
	message((-7, "bunread(%s,%d@%ld): %-.*s%s", ap->name, n, ap->io.count, n > 32 ? 32 : n, b, n > 32 ? "..." : ""));
}

/*
 * bread() n chars and return a pointer to the char buffer
 */

char*
bget __PARAM__((Archive_t* ap, int n), (ap, n)) __OTORP__(Archive_t* ap; int n;){
	char*	s;

	ap->io.count += n;
	s = ap->io.next;
	ap->io.next += n;
	while (ap->io.next > ap->io.last)
	{
		if (ap->io.last > ap->io.buffer + MAXUNREAD + state.buffersize)
		{
                        char*  b;
                        int    k;
                        int    m;

                        k = ap->io.last - s;
			m = roundof(k, IOALIGN) - k;
#if DEBUG
			if (m) message((-8, "bget(%s) buffer alignment offset=%d", ap->name, m));
#endif
                        b = ap->io.next = ap->io.buffer + MAXUNREAD + m;
                        ap->io.last = b + k;
                        m = s - b;
                        while (k > m)
                        {
                                message((-8, "bget(%s) overlapping memcpy n=%d k=%d m=%d", ap->name, n, k, m));
                                memcpy(b, s, m);
                                b += m;
                                s += m;
                                k -= m;
                        }
                        memcpy(b, s, k);
			s = ap->io.next;
			ap->io.next += n;
		}
		if (bfill(ap, 1) < 0) return(0);
	}
	if (ap->sum > 0)
	{
		ap->memsum = memsum(s, n, ap->memsum);
		ap->old.memsum = omemsum(s, n, ap->old.memsum);
	}
	message((-7, "bget(%s,%d@%ld): %-.*s%s", ap->name, n, ap->io.count, n > 32 ? 32 : n, s, n > 32 ? "..." : ""));
	return(s);
}

/*
 * back up input to bsave()'d position and prime output buffer
 */

void
backup __PARAM__((Archive_t* ap), (ap)) __OTORP__(Archive_t* ap;){
	long	n;
	long	m;
#ifdef MTIOCTOP
	struct mtop	mt;
#endif

	switch (ap->format)
	{
	case ALAR:
	case IBMAR:
#ifdef MTIOCTOP
		mt.mt_op = MTBSF;
		mt.mt_count = 1;
		if (!(ioctl(ap->io.fd, MTIOCTOP, &mt))) return;
#endif
		break;
	default:
		m = ap->io.next - (ap->io.buffer + MAXUNREAD);
		if ((n = ap->io.count - m) > state.backup.count)
		{
			message((-1, "backup(%s): reread %ld", ap->name, n + m));
			m = state.backup.last - (state.backup.buffer + MAXUNREAD);
			if (lseek(ap->io.fd, -(n + m), SEEK_CUR) == -1L)
			{
#ifdef MTIOCTOP
				mt.mt_op = MTBSR;
				mt.mt_count = 2;
				if (ioctl(ap->io.fd, MTIOCTOP, &mt)) break;
#else
				break;
#endif
			}
			if (read(ap->io.fd, ap->io.buffer + MAXUNREAD, m) != m) break;
		}
		else m = ap->io.last - (ap->io.buffer + MAXUNREAD);
		message((-1, "backup(%s): %ld", ap->name, m));
		if ((m = lseek(ap->io.fd, -m, SEEK_CUR)) == -1L)
		{
#ifdef MTIOCTOP
			mt.mt_op = MTBSR;
			mt.mt_count = 1;
			if (ioctl(ap->io.fd, MTIOCTOP, &mt)) break;
#else
			break;
#endif
		}
		if (state.backup.next < state.backup.last)
			bwrite(ap, ap->io.buffer + MAXUNREAD, state.backup.next - (state.backup.buffer + MAXUNREAD));
		return;
	}
	error(3, "%s: cannot position %s archive for append", ap->name, format[ap->format].name);
}

/*
 * flush buffered input
 */

void
bflushin __PARAM__((Archive_t* ap), (ap)) __OTORP__(Archive_t* ap;){
	ap->io.count += ap->io.last - ap->io.next;
	ap->io.next = ap->io.last = ap->io.buffer + MAXUNREAD;
	if (!ap->io.eof)
	{
		while (read(ap->io.fd, state.tmp.buffer, state.buffersize) > 0);
		ap->io.eof = 1;
	}
}

/*
 * rudimentary buffered seek -- force re-read
 */

off_t
bseek __PARAM__((Archive_t* ap, off_t pos, int op), (ap, pos, op)) __OTORP__(Archive_t* ap; off_t pos; int op;){
	ap->io.next = ap->io.last = ap->io.buffer + MAXUNREAD;
	if ((pos = lseek(ap->io.fd, pos, op)) >= 0)
	{
		ap->io.empty = 0;
		ap->io.eof = 0;
		ap->io.count = pos - ap->io.offset;
	}
	return(pos);
}

/*
 * flush buffered output
 */

void
bflushout __PARAM__((Archive_t* ap), (ap)) __OTORP__(Archive_t* ap;){
	int	n;
	int	c;

	if (n = ap->io.next - ap->io.buffer)
	{
		ap->io.next = ap->io.buffer;
		while ((c = write(ap->io.fd, ap->io.next, n)) != n)
		{
			if (c <= 0) newio(ap, c, n);
			else
			{
				ap->io.next += c;
				n -= c;
			}
		}
		ap->io.next = ap->io.buffer;
	}
}

/*
 * buffered output
 */

void
bwrite __PARAM__((Archive_t* ap, __V_* ab, int n), (ap, ab, n)) __OTORP__(Archive_t* ap; __V_* ab; int n;){
	char*	b = (char*)ab;
	int	c;

	if (ap->sum > 0)
		ap->memsum = memsum(b, n, ap->memsum);
	if (ap->io.skip)
		ap->io.skip = bskip(ap);
	if (state.maxout && ap->io.count >= state.maxout)
	{
		bflushout(ap);
		newio(ap, 0, 0);
	}
	ap->io.count += n;
	if (ap->io.blocked)
	{
#if DEBUG
		if (n > 0) message((-7, "bwrite(%s,%d@%ld): %-.*s...", ap->name, n, ap->io.count + n, n > 32 ? 32 : n, b));
		else message((-7, "bwrite(%s,%d@%ld):", ap->name, n, ap->io.count + n));
#endif
		while ((c = write(ap->io.fd, b, n)) != n)
		{
			if (n <= 0)
			{
#ifdef MTIOCTOP
				{
					struct mtop	mt;

					mt.mt_op = MTWEOF;
					mt.mt_count = 1;
					if (ioctl(ap->io.fd, MTIOCTOP, &mt) >= 0) break;
				}
#endif
				error(3, "%s: cannot write tape EOF marks", ap->name);
			}
			if (c <= 0) newio(ap, c, n);
			else if ((n -= c) > 0) b += c;
			else break;
		}
	}
	else
	{
#if DEBUG
		if (n > 0) message((-7, "bwrite(%s,%d@%ld): %-.*s...", ap->name, n, ap->io.count + n, n > 32 ? 32 : n, b));
		else message((-7, "bwrite(%s,%d@%ld):", ap->name, n, ap->io.count + n));
#endif
		for (;;)
		{
			if ((c = ap->io.buffer + state.blocksize - ap->io.next) <= n)
			{
				if (c)
				{
					memcpy(ap->io.next, b, c);
					n -= c;
					b += c;
				}
				ap->io.next = ap->io.buffer;
				while ((c = write(ap->io.fd, ap->io.next, state.blocksize)) != state.blocksize)
				{
					if (c <= 0) newio(ap, c, n);
					else
					{
						memcpy(state.tmp.buffer, ap->io.buffer + c, state.blocksize - c);
						memcpy(ap->io.buffer, state.tmp.buffer, state.blocksize - c);
						ap->io.next = ap->io.buffer + state.blocksize - c;
						break;
					}
				}
				message((-8, "write(%s,%d): %-.32s...", ap->name, c, ap->io.buffer));
			}
			else
			{
				memcpy(ap->io.next, b, n);
				ap->io.next += n;
				break;
			}
		}
	}
}

/*
 * bwrite() n chars that have been placed in ap->io.next
 */

void
bput __PARAM__((Archive_t* ap, int n), (ap, n)) __OTORP__(Archive_t* ap; int n;){
	ap->io.count += n;
	message((-7, "bput(%s,%d@%ld): %-.*s%s", ap->name, n, ap->io.count, n > 32 ? 32 : n, ap->io.next, n > 32 ? "..." : ""));
	if (ap->sum > 0)
		ap->memsum = memsum(ap->io.next, n, ap->memsum);
	if ((ap->io.next += n) > ap->io.buffer + state.blocksize)
	{
		n = (ap->io.next - ap->io.buffer) - state.blocksize;
		ap->io.count -= n;

		/*
		 * flush out the buffer and slide over the remains
		 */

		ap->sum--;
		bwrite(ap, ap->io.next = ap->io.buffer + state.blocksize, n);
		ap->sum++;
	}
}

static struct
{
	char*		path;
	struct stat*	st;
} dev;

/*
 * find path name in /dev for <dev.st->st_dev,dev.st->st_ino>
 * called by ftwalk()
 */

static int
devpath __PARAM__((Ftw_t* ftw), (ftw)) __OTORP__(Ftw_t* ftw;){
	if (ftw->info == FTW_F && ftw->statb.st_dev == dev.st->st_dev && ftw->statb.st_ino == dev.st->st_ino)
	{
		message((-1, "device name is %s", ftw->path));
		dev.path = strdup(ftw->path);
		return(1);
	}
	return(0);
}

/*
 * initilize tty file pointers for interactive prompting
 */

void
interactive __PARAM__((void), ()){
	int	fd;

	if (!state.rtty)
	{
		fd = dup(2);
		if (!(state.rtty = sfopen(NiL, "/dev/tty", "r")) || !(state.wtty = sfopen(NiL, "/dev/tty", "w")))
			error(ERROR_SYSTEM|3, "cannot prompt for interactive input");
		sfsetbuf(state.rtty, NiL, 0);
		sfsetbuf(state.wtty, NiL, 0);
		if (fd >= 0) close(fd);
	}
}

/*
 * check for new input or output stream
 * c is the io count causing the newio()
 * n is the pending buffered io count
 */

void
newio __PARAM__((Archive_t* ap, int c, int n), (ap, c, n)) __OTORP__(Archive_t* ap; int c; int n;){
	char*	s;
	char*	rw;
	char*		file;
	char*		io;
	char*		t;
	int		vol;
	long		z;
	struct stat	st;

	static int	locked;
	static long	total;

	vol = 0;
	if (ap->io.mode)
	{
		rw = "write";
		io = "output";
		ap->io.offset += ap->io.count - n;
		ap->io.count = n;
		z = ap->io.offset + ap->io.count;
		if (ap->io.blocked && state.record.file) switch (ap->format)
		{
		case ALAR:
		case IBMAR:
			if (locked) return;
			locked = 1;
			putlabels(ap, state.record.file, "EOV");
			locked = 0;
			vol = 1;
			break;
		}
	}
	else
	{
		rw = "read";
		io = "input";
		z = ap->io.offset + ap->io.count;
	}
	if (fstat(ap->io.fd, &st) < 0)
		error(ERROR_SYSTEM|3, "%s: cannot stat %s", ap->name, io);
	st.st_mode = modex(st.st_mode);
	switch (X_ITYPE(st.st_mode))
	{
	case X_IFBLK:
	case X_IFCHR:
		file = 0;
		break;
	default:
		if (ap->io.mode) switch (c < 0 ? errno : 0)
		{
		case 0:
#ifdef EFBIG
		case EFBIG:
#endif
#ifdef EDQUOT
		case EDQUOT:
#endif
			file = "file";
			break;
		default:
			error(ERROR_SYSTEM|3, "%s: %s %s error -- cannot recover", ap->name, io, rw);
			break;
		}
		else file = "file";
		break;
	}
	switch (c < 0 ? errno : 0)
	{
	case 0:
	case ENOSPC:
	case ENXIO:
		error(1, "%s: end of %s medium", ap->name, io);
		break;
	default:
		error(ERROR_SYSTEM|1, "%s: %s %s error", ap->name, io, rw);
		break;
	}
	if (total == z) error(1, "%s: no %s on part %d", ap->name, io, ap->part--);
	else total = z;
	if (!file && ap->name != definput && ap->name != defoutput)
	{
		dev.path = 0;
		dev.st = &st;
		ftwalk("/dev", devpath, 0, NiL);
		ap->name = dev.path;
	}
	close(ap->io.fd);
	if (file && ap->name != definput && ap->name != defoutput && strmatch(ap->name, "*.+([0-9])") && (s = strrchr(ap->name, '.')) && ((c = strtol(++s, NiL, 10)) == ap->part || c == (ap->part - 1)))
	{
		if (ap->part == 1 && (!(ap->name = strdup(ap->name)) || !(s = strrchr(ap->name, '.'))))
			error(3, "out of space");
		s += strlen(s);
		while (*--s != '.')
		{
			if (*s < '9')
			{
				(*s)++;
				break;
			}
			*s = '0';
		}
		if (*s != '.')
		{
			if ((ap->io.fd = open(ap->name, ap->io.mode, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)) >= 0)
			{
				ap->part++;
				error(1, "continuing %s %d %s on %s", ap->part == ap->volume + 1 ? "volume" : "part", ap->part, io, ap->name);
				return;
			}
		}
		error(ERROR_SYSTEM|1, "%s: cannot %s", ap->name, rw);
	}
	if (file || ap->name == definput || ap->name == defoutput)
	{
		for (;;)
		{
			interactive();
			sfputc(state.wtty, '\007');
			sfprintf(state.wtty, "Enter part %d %s %s name: ", ap->part + 1, io, file ? file : "device");
			if (!(s = sfgetr(state.rtty, '\n', 1)))
			{
				sfputc(state.wtty, '\n');
				finish(2);
			}
			if (*s)
			{
				if (!file) break;
				if ((ap->io.fd = open(s, ap->io.mode, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)) >= 0) break;
				error(ERROR_SYSTEM|1, "%s: cannot open", s);
			}
		}
		ap->name = strdup(s);
	}
	if (!file)
	{
		for (;;)
		{
			interactive();
			sfputc(state.wtty, '\007');
			sfprintf(state.wtty, eomprompt, ap->part + 1);
			if (!(s = sfgetr(state.rtty, '\n', 1)))
			{
				sfputc(state.wtty, '\n');
				finish(2);
			}
			if (*s == '!')
			{
				static char*	last;

				if (*++s)
				{
					if (last) free(last);
					last = strdup(s);
				}
				else s = last;
				if (!s) error(1, "no previous command");
				else if (n = system(s)) error(1, "exit status %d", n);
			}
			else
			{
				file = *s ? s : ap->name;
				if ((ap->io.fd = open(file, ap->io.mode)) >= 0) break;
				file = strtape(file, &t);
				if (!*t && (ap->io.fd = open(file, ap->io.mode)) >= 0) break;
				error(ERROR_SYSTEM|1, "cannot %s %s", rw, *s ? s : ap->name);
			}
		}
		if (ap->name != file) ap->name = strdup(file);
	}
	ap->part++;
	if (vol && !locked)
	{
		locked = 1;
		putprologue(ap);
		putlabels(ap, state.record.file, "HDR");
		locked = 0;
	}
}