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
/* lcGeneric.c 1.4 - Fujitsu source for CDEnext    96/02/29 18:02:54 	*/
/* $XConsortium: _fallcGeneric.c /main/2 1996/09/27 19:03:31 drk $ */
/*
 * Copyright 1992, 1993 by TOSHIBA Corp.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of TOSHIBA not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. TOSHIBA make no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * TOSHIBA DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * TOSHIBA BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *
 * Author: Katsuhisa Yano	TOSHIBA Corp.
 *			   	mopi@osa.ilab.toshiba.co.jp
 */
/*
 * Copyright 1995 by FUJITSU LIMITED
 * This is source code modified by FUJITSU LIMITED under the Joint
 * Development Agreement for the CDEnext PST.
 * This is unpublished proprietry source code of FUJITSU LIMITED
 *
 * Modifier: Takanori Tateno   FUJITSU LIMITED
 *
 */

#include <stdio.h>
#include "_fallibint.h"
#include "_fallcGeneric.h"

static XLCd create(char *name, XLCdMethods methods);
static Bool initialize(XLCd lcd);
static void destroy(XLCd lcd);

static XLCdPublicMethodsRec genericMethods = {
    { NULL },                   /* use default methods */
    {
	NULL,
	create,
	initialize,
	destroy,
	NULL
    }
};

XLCdMethods _fallcGenericMethods = (XLCdMethods) &genericMethods;

static XLCd
create(char *name, XLCdMethods methods)
{
    XLCd lcd;
    XLCdPublicMethods new;

    lcd = (XLCd) Xmalloc(sizeof(XLCdRec));
    if (lcd == NULL)
        return (XLCd) NULL;
    bzero((char *) lcd, sizeof(XLCdRec));

    lcd->core = (XLCdCore) Xmalloc(sizeof(XLCdGenericRec));
    if (lcd->core == NULL){
	Xfree(lcd);
	return (XLCd) NULL;
    }
    bzero((char *) lcd->core, sizeof(XLCdGenericRec));

    new = (XLCdPublicMethods) Xmalloc(sizeof(XLCdPublicMethodsRec));
    if (new == NULL){
	Xfree(lcd);
	return (XLCd) NULL;
    }
    *new = *((XLCdPublicMethods) methods);
    lcd->methods = (XLCdMethods) new;

    return lcd;
}

static Bool
string_to_encoding(char *str, char *encoding)
{
    char *next;
    long value;
    int base;

    while (*str) {
	if (*str == '\\') {
	    switch (*(str + 1)) {
		case 'x':
		case 'X':
		    base = 16;
		    break;
		default:
		    base = 8;
		    break;
	    }
	    value = strtol(str + 2, &next, base);
	    if (str + 2 != next) {
		*((unsigned char *) encoding++) = (unsigned char) value;
		str = next;
		continue;
	    }
	}
	*encoding++ = *str++;
    }

    *encoding = '\0';

    return True;
}

static Bool
string_to_ulong(char *str, unsigned long *value)
{
     char	*tmp1 = str;
     int	 base;

     if(*tmp1++ != '\\'){
	  tmp1--;
	  base = 10;
     }else{
	  switch(*tmp1++){
	  case 'x':
	       base = 16;
	       break;
	  case 'o':
	       base = 8;
	       break;
	  case 'd':
	       base = 10;
	       break;
	  default:
	       return(False);
	  }
     }
    *value = (unsigned) strtol(tmp1, NULL, base);
     return(True);
}


static Bool
add_charset(CodeSet codeset, XlcCharSet charset)
{
    XlcCharSet *new_list;
    int num;

    if (num = codeset->num_charsets)
        new_list = (XlcCharSet *) Xrealloc(codeset->charset_list,
                                        (num + 1) * sizeof(XlcCharSet));
    else
        new_list = (XlcCharSet *) Xmalloc(sizeof(XlcCharSet));

    if (new_list == NULL)
	return False;

    new_list[num] = charset;
    codeset->charset_list = new_list;
    codeset->num_charsets = num + 1;

    return True;
}

static CodeSet
add_codeset(XLCdGenericPart *gen)
{
    CodeSet new, *new_list;
    int num;

    new = (CodeSet) Xmalloc(sizeof(CodeSetRec));
    if (new == NULL)
        return NULL;
    bzero((char *) new, sizeof(CodeSetRec));

    if (num = gen->codeset_num)
        new_list = (CodeSet *) Xrealloc(gen->codeset_list,
                                        (num + 1) * sizeof(CodeSet));
    else
        new_list = (CodeSet *) Xmalloc(sizeof(CodeSet));

    if (new_list == NULL){
        Xfree(new);
	return NULL;
    }

    new_list[num] = new;
    gen->codeset_list = new_list;
    gen->codeset_num = num + 1;

    return new;
}

static Bool
add_parse_list(
    XLCdGenericPart *gen,
    EncodingType type,
    char *encoding,
    CodeSet codeset)
{
    ParseInfo new, *new_list;
    char *str;
    unsigned char ch;
    int num;

    str = (char *) Xmalloc(strlen(encoding) + 1);
    if (str == NULL)
        return False;
    strcpy(str, encoding);

    new = (ParseInfo) Xmalloc(sizeof(ParseInfoRec));
    if (new == NULL){
	Xfree(str);
	if (new)
            Xfree(new);

	return False;
    }
    bzero((char *) new, sizeof(ParseInfoRec));

    if (gen->mb_parse_table == NULL) {
        gen->mb_parse_table = (unsigned char *) Xmalloc(256); /* 2^8 */
        if (gen->mb_parse_table == NULL){
            Xfree(str);
	    if (new)
		Xfree(new);

	    return False;
	}
        bzero((char *) gen->mb_parse_table, 256);
    }

    if (num = gen->mb_parse_list_num)
        new_list = (ParseInfo *) Xrealloc(gen->mb_parse_list,
                                          (num + 2) * sizeof(ParseInfo));
    else {
        new_list = (ParseInfo *) Xmalloc(2 * sizeof(ParseInfo));
    }

    if (new_list == NULL){
        Xfree(str);
	if (new)
	    Xfree(new);

        return False;
    }

    new_list[num] = new;
    new_list[num + 1] = NULL;
    gen->mb_parse_list = new_list;
    gen->mb_parse_list_num = num + 1;

    ch = (unsigned char) *str;
    if (gen->mb_parse_table[ch] == 0)
        gen->mb_parse_table[ch] = num + 1;

    new->type = type;
    new->encoding = str;
    new->codeset = codeset;

    if (codeset->parse_info == NULL)
        codeset->parse_info = new;

    return True;
}

static void
free_charset(XLCd lcd)
{
    XLCdGenericPart *gen = XLC_GENERIC_PART(lcd);
    CodeSet *codeset;
    ParseInfo *parse_info;
    int num;

    if (gen->mb_parse_table)
        Xfree(gen->mb_parse_table);
    if (num = gen->mb_parse_list_num) {
        for (parse_info = gen->mb_parse_list; num-- > 0; parse_info++) {
            if ((*parse_info)->encoding)
                Xfree((*parse_info)->encoding);
            Xfree(*parse_info);
        }
        Xfree(gen->mb_parse_list);
    }

    if (num = gen->codeset_num)
        Xfree(gen->codeset_list);
}
/* For VW/UDC */

#define FORWARD  (unsigned long)'+'
#define BACKWARD (unsigned long)'-'

static char *getscope(char *str, FontScope scp)
{
    char buff[256],*next;
    unsigned long start=0,end=0,dest=0,shift=0,direction=0;
    sscanf(str,"[\\x%lx,\\x%lx]->\\x%lx", &start, &end, &dest);
    if( dest ){
        if(dest >= start ){
            shift = dest - start;
            direction = FORWARD ;
        } else {
            shift = start - dest;
            direction = BACKWARD;
        }
    }
    scp->start = start      ;
    scp->end   = end        ;
    scp->shift = shift      ;
    scp->shift_direction
               = direction  ;
    /* .......... */
    while(*str){
        if(*str == ',' && *(str+1) == '['){
            break;
        }
        str++;
    }
    next = str+1 ;
    return(next);
}
static int count_scopemap(char *str)
{
    char *ptr;
    int num=0;
    for(ptr=str;*ptr;ptr++){
        if(*ptr == ']'){
            num ++;
        }
    }
    return(num);
}
FontScope falparse_scopemaps(char *str, int *size)
{
        int num=0,i;
        FontScope scope,sc_ptr;
        char *str_sc;
        num = count_scopemap(str);
        scope = (FontScope )Xmalloc(num * sizeof(FontScopeRec));
        if(scope == NULL) {
                return (NULL);
        }
        for (i=0,str_sc=str,sc_ptr=scope;
                        i < num; i++,sc_ptr++){
                str_sc = getscope(str_sc,sc_ptr);
        }
        *size = num;
        return (scope);
}

void
dbg_printValue(char *str, char **value, int num)
{
#ifdef DEBUG
    int i;
    for(i=0;i<num;i++){
        fprintf(stderr,"%s value[%d] = %s\n",str,i,value[i]);
    }
#endif
}

void
dmpscope(char *name, FontScope sc, int num)
{
/* should this be protected by ifdef DEBUG?
    int i;
    fprintf(stderr,"dmpscope %s\n",name);
    for(i=0;i<num;i++){
        fprintf(stderr,"%x %x %x %x \n",
                sc[i].start,
                sc[i].end,
                sc[i].shift,
                sc[i].shift_direction);
    }
    fprintf(stderr,"dmpscope end\n");
*/
}

static XlcCharSet srch_charset_define(char *name, int *new)
{
    XlcCharSet charset = NULL;
    *new = 0;
    charset = _fallcGetCharSet(name);
    if (charset == NULL &&
        (charset = _fallcCreateDefaultCharSet(name, ""))) {
        _fallcAddCharSet(charset);
        *new = 1;
    }
    return(charset);
}

static int
read_charset_define(XLCd lcd, XLCdGenericPart *gen)
{
    int i=0;
    char csd[16],cset_name[256];
    char name[BUFSIZ];
    XlcCharSet charsetd;
    char **value;
    int num,new,side=0;
    char *tmp;

    for(i=0;;i++){ /* loop start */
        charsetd = 0;
        sprintf(csd, "csd%d", i);

        /* charset_name   */
        sprintf(name, "%s.%s", csd , "charset_name");
        _fallcGetResource(lcd, "XLC_CHARSET_DEFINE", name, &value, &num);
        dbg_printValue(name,value,num);
        if (num > 0) {
            snprintf(cset_name, sizeof(cset_name), "%s", value[0]);
            snprintf(name, sizeof(name), "%s.%s", csd , "side");
            _fallcGetResource(lcd, "XLC_CHARSET_DEFINE", name, &value, &num);
            if (num > 0) {
                dbg_printValue(name,value,num);
                if( !_fallcNCompareISOLatin1(value[0], "none", 4) ){
                    side =  XlcNONE ;
                    strcat(cset_name,":none");
                } else
                if( !_fallcNCompareISOLatin1(value[0], "GL", 2) ){
                    side =  XlcGL ;
                    strcat(cset_name,":GL");
                } else {
                    side =  XlcGR ;
                    strcat(cset_name,":GR");
                }
                if (charsetd == NULL &&
                    (charsetd = srch_charset_define(cset_name,&new)) == NULL)
                    return 0;
            }
        } else {
            if(i == 0){
                continue ;
            } else {
                break ;
            }
        }
        if(new){
            tmp = (char *)Xmalloc(strlen(cset_name)+1);
            if(tmp == NULL){
                return 0;
            }
            strcpy(tmp,cset_name);
            charsetd->name = tmp;
        }
        /* side   */
        charsetd->side =  side ;
        /* length */
        snprintf(name, sizeof(name), "%s.%s", csd , "length");
        _fallcGetResource(lcd, "XLC_CHARSET_DEFINE", name, &value, &num);
        if (num > 0) {
            dbg_printValue(name,value,num);
            charsetd->char_size = atoi(value[0]);
        }
        /* gc_number */
        snprintf(name, sizeof(name), "%s.%s", csd , "gc_number");
        _fallcGetResource(lcd, "XLC_CHARSET_DEFINE", name, &value, &num);
        if (num > 0) {
            dbg_printValue(name,value,num);
            charsetd->set_size = atoi(value[0]);
        }
        /* string_encoding */
        snprintf(name, sizeof(name), "%s.%s", csd , "string_encoding");
        _fallcGetResource(lcd, "XLC_CHARSET_DEFINE", name, &value, &num);
        if (num > 0) {
            dbg_printValue(name,value,num);
            if(!strcmp("False",value[0])){
                charsetd->string_encoding = False;
            } else {
                charsetd->string_encoding = True;
            }
        }
        /* sequence */
        snprintf(name, sizeof(name), "%s.%s", csd , "sequence");
        _fallcGetResource(lcd, "XLC_CHARSET_DEFINE", name, &value, &num);
        if (num > 0) {
            dbg_printValue(name,value,num);
/*
            if(charsetd->ct_sequence){
                Xfree(charsetd->ct_sequence);
            }
*/
            tmp = (char *)Xmalloc(strlen(value[0])+1);
            if(tmp == NULL){
                return 0;
            }
            charsetd->ct_sequence = tmp;
            string_to_encoding(value[0],tmp);
        }
        /* encoding_name */
        snprintf(name, sizeof(name), "%s.%s", csd , "encoding_name");
        _fallcGetResource(lcd, "XLC_CHARSET_DEFINE", name, &value, &num);
        if (num > 0) {
            dbg_printValue(name,value,num);
/*
            if(charsetd->encoding_name){
                Xfree(charsetd->encoding_name);
            }
*/
            tmp = (char *)Xmalloc(strlen(value[0]) + 1);
            strcpy(tmp,value[0]);
            charsetd->encoding_name = tmp;
            charsetd->xrm_encoding_name =
                falrmStringToQuark(tmp);
        }
    }
    return 1;
}

SegConv
faladd_conversion(XLCdGenericPart *gen)
{
    SegConv new_list;
    int num;

    if (num = gen->segment_conv_num){
        new_list = (SegConv) Xrealloc(gen->segment_conv,
                                        (num + 1) * sizeof(SegConvRec));
    } else {
        new_list = (SegConv) Xmalloc(sizeof(SegConvRec));
    }

    if (new_list == NULL)
        return False;

    gen->segment_conv = new_list;
    gen->segment_conv_num = num + 1;

    return (&new_list[num]);

}
static int
read_segmentconversion(XLCd lcd, XLCdGenericPart *gen)
{
    int i=0;
    char conv[16];
    char name[BUFSIZ];
    char **value;
    int num,new;
    SegConv conversion;
    for(i=0 ; ; i++){ /* loop start */
        conversion = 0;
        sprintf(conv, "conv%d", i);

        /* length                */
        sprintf(name, "%s.%s", conv , "length");
        _fallcGetResource(lcd, "XLC_SEGMENTCONVERSION", name, &value, &num);
        if (num > 0) {
            char *tmp;
            if (conversion == NULL &&
                (conversion = faladd_conversion(gen)) == NULL) {
                return 0;
            }
            dbg_printValue(name,value,num);
        } else {
            if(i == 0){
                continue;
            } else {
                break ;
            }
        }
        conversion->length = atoi(value[0]);

        /* source_encoding       */
        sprintf(name, "%s.%s", conv , "source_encoding");
        _fallcGetResource(lcd, "XLC_SEGMENTCONVERSION", name, &value, &num);
        if (num > 0) {
            char *tmp;
            dbg_printValue(name,value,num);
            tmp = (char *)Xmalloc(strlen(value[0])+1);
            if(tmp == NULL){
                return 0;
            }
            strcpy(tmp,value[0]);
            conversion->source_encoding = tmp;
            conversion->source = srch_charset_define(tmp,&new);
            if(new){
                tmp = (char *)Xmalloc(strlen(conversion->source_encoding)+1);
                if(tmp == NULL){
                    return 0;
                }
                strcpy(tmp,conversion->source_encoding);
                conversion->source->name = tmp;
            }
        }
        /* destination_encoding  */
        sprintf(name, "%s.%s", conv , "destination_encoding");
        _fallcGetResource(lcd, "XLC_SEGMENTCONVERSION", name, &value, &num);
        if (num > 0) {
            char *tmp;
            dbg_printValue(name,value,num);
            tmp = (char *)Xmalloc(strlen(value[0])+1);
            if(tmp == NULL){
                return 0;
            }
            strcpy(tmp,value[0]);
            conversion->destination_encoding = tmp;
            conversion->dest = srch_charset_define(tmp,&new);
            if(new){
                tmp = (char *)Xmalloc(
                    strlen(conversion->destination_encoding)+1);
                if(tmp == NULL){
                    return 0;
                }
                strcpy(tmp,conversion->destination_encoding);
                conversion->dest->name = tmp;
            }
        }
        /* range                 */
        sprintf(name, "%s.%s", conv , "range");
        _fallcGetResource(lcd, "XLC_SEGMENTCONVERSION", name, &value, &num);
        if (num > 0) {
            char *tmp;
            dbg_printValue(name,value,num);
            sscanf(value[0],"\\x%lx,\\x%lx",
                &(conversion->range.start),
                &(conversion->range.end));
        }
        /* conversion            */
        sprintf(name, "%s.%s", conv , "conversion");
        _fallcGetResource(lcd, "XLC_SEGMENTCONVERSION", name, &value, &num);
        if (num > 0) {
            char *tmp;
            dbg_printValue(name,value,num);
            conversion->conv =
                falparse_scopemaps(value[0],&conversion->conv_num);
        }
    }  /* loop end */

    return 1;
}

static ExtdSegment create_ctextseg(char **value, int num)
{
    ExtdSegment ret;
    char side_str[128],*ptr;
    char cset_name[128],*tmp;
    int i,new;
    FontScope scope;
    ret = (ExtdSegment)Xmalloc(sizeof(ExtdSegmentRec));
    if(ret == NULL){
        return (0);
    }
    if(strchr(value[0],':')){
        ret->name = (char *)Xmalloc(strlen(value[0])+1);
        if(ret->name == NULL){
            XFree(ret);
            return(NULL);
        }
        strcpy(ret->name,value[0]);
        ptr = strchr(ret->name,':');
        *ptr = 0;
        ptr++;
        if( !_fallcNCompareISOLatin1(ptr, "none", 4) ){
            ret->side =  XlcNONE ;
            snprintf(cset_name,sizeof(cset_name),"%s:%s",ret->name,"none");
        } else
        if( !_fallcNCompareISOLatin1(ptr, "GL", 2) ){
            ret->side =  XlcGL ;
            snprintf(cset_name,sizeof(cset_name),"%s:%s",ret->name,"GL");
        } else {
            ret->side =  XlcGR ;
            snprintf(cset_name,sizeof(cset_name),"%s:%s",ret->name,"GR");
        }
    } else {
        ret->name = (char *)Xmalloc(strlen(value[0])+1);
        if(ret->name == NULL){
            XFree(ret);
            return(NULL);
        }
        strcpy(ret->name,value[0]);
    }
    ret->area = (FontScope)Xmalloc((num - 1)*sizeof(FontScopeRec));
    if(ret->area == NULL){
        XFree(ret->name);
        XFree(ret);
        return(NULL);
    }
    ret->area_num  = num - 1;
    scope = ret->area ;
    for(i=1;i<num;i++){
        sscanf(value[i],"\\x%lx,\\x%lx", &scope[i-1].start, &scope[i-1].end);
    }
    ret->charset = srch_charset_define(cset_name,&new);
    if(new){
        tmp = (char *)Xmalloc(strlen(cset_name)+1);
        if(tmp == NULL){
            XFree(ret->area);
            XFree(ret->name);
            XFree(ret);
            return NULL;
        }
        strcpy(tmp,cset_name);
        ret->charset->name = tmp;
    }
    return(ret);
}
/* For VW/UDC end */

static Bool
load_generic(XLCd lcd)
{
    XLCdGenericPart *gen = XLC_GENERIC_PART(lcd);
    char **value;
    int num;
    unsigned long l;
    int i;
    int M,ii;

    gen->codeset_num = 0;

    /***** wc_encoding_mask *****/
    _fallcGetResource(lcd, "XLC_XLOCALE", "wc_encoding_mask", &value, &num);
    if (num > 0) {
	if (string_to_ulong(value[0], &l) == False){
	    free_charset(lcd);
            return False;
	}
	gen->wc_encode_mask = l;
    }
    /***** wc_shift_bits *****/
    _fallcGetResource(lcd, "XLC_XLOCALE", "wc_shift_bits", &value, &num);
    if (num > 0)
	gen->wc_shift_bits = atoi(value[0]);
    if (gen->wc_shift_bits < 1)
	gen->wc_shift_bits = 8;
#ifndef X_NOT_STDC_ENV
    /***** use_stdc_env *****/
    _fallcGetResource(lcd, "XLC_XLOCALE", "use_stdc_env", &value, &num);
    if (num > 0 && !_fallcCompareISOLatin1(value[0], "True"))
	gen->use_stdc_env = True;
    else
	gen->use_stdc_env = False;
    /***** force_convert_to_mb *****/
    _fallcGetResource(lcd, "XLC_XLOCALE", "force_convert_to_mb", &value, &num);
    if (num > 0 && !_fallcCompareISOLatin1(value[0], "True"))
	gen->force_convert_to_mb = True;
    else
	gen->force_convert_to_mb = False;
#endif

    for (i = 0; ; i++) {
	CodeSetRec *codeset = NULL;
	char cs[16];
	char name[BUFSIZ];

	sprintf(cs, "cs%d", i);

	/***** codeset.side *****/
	sprintf(name, "%s.%s", cs , "side");
	_fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);
	if (num > 0) {
	    char *tmp;

	    if (codeset == NULL && (codeset = add_codeset(gen)) == NULL){
		free_charset(lcd);
                return False;
	    }

            /* 3.4.1 side */
            if( !_fallcNCompareISOLatin1(value[0], "none", 4) ){
                codeset->side =  XlcNONE ;
            } else
            if( !_fallcNCompareISOLatin1(value[0], "GL", 2) ){
                codeset->side =  XlcGL ;
            } else {
                codeset->side =  XlcGR ;
            }

	    tmp = strrchr(value[0], ':');
	    if (tmp != NULL && !_fallcCompareISOLatin1(tmp + 1, "Default")) {
		if (codeset->side == XlcGR)
		    gen->initial_state_GR = codeset;
		else
		    gen->initial_state_GL = codeset;
	    }
	}

	/***** codeset.length *****/
	sprintf(name, "%s.%s", cs , "length");
	_fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);
	if (num > 0) {
	    if (codeset == NULL && (codeset = add_codeset(gen)) == NULL){
		free_charset(lcd);
                return False;
	    }
	    codeset->length = atoi(value[0]);
	    if (codeset->length < 1)
		codeset->length = 1;
	}

	/***** codeset.mb_encoding *****/
	sprintf(name, "%s.%s", cs, "mb_encoding");
	_fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);
	if (num > 0) {
	    static struct {
		char *str;
		int type;
	    } shifts[] = {
		{"<SS>", E_SS},
		{"<LSL>", E_LSL},
		{"<LSR>", E_LSR},
		0
	    };
	    int j;

	    if (codeset == NULL && (codeset = add_codeset(gen)) == NULL){
		free_charset(lcd);
                return False;
	    }
	    for ( ; num-- > 0; value++) {
		char encoding[256];
		char *tmp = *value;
		int type = E_SS;    /* for BC */
		for (j = 0; shifts[j].str; j++) {
		    if (!_fallcNCompareISOLatin1(tmp, shifts[j].str,
					       strlen(shifts[j].str))) {
			type = shifts[j].type;
			tmp += strlen(shifts[j].str);
			break;
		    }
		}
		if (string_to_encoding(tmp, encoding) == False){
		    free_charset(lcd);
	            return False;
		}
		add_parse_list(gen, type, encoding, codeset);
	    }
	}

	/***** codeset.wc_encoding *****/
	sprintf(name, "%s.%s", cs, "wc_encoding");
	_fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);
	if (num > 0) {
	    if ((codeset == NULL && (codeset = add_codeset(gen)) == NULL) || \
               (string_to_ulong(value[0], &l) == False)){
		free_charset(lcd);
		return False;
	    }
	    codeset->wc_encoding = l;
	}

	/***** codeset.ct_encoding *****/
	sprintf(name, "%s.%s", cs, "ct_encoding");
	_fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);
	if (num > 0) {
	    XlcCharSet charset;
	    char *encoding;

	    if (codeset == NULL && (codeset = add_codeset(gen)) == NULL){
		free_charset(lcd);
		return False;
	    }
	    for ( ; num-- > 0; value++) {
		string_to_encoding(*value, name);
		charset = NULL;
		if ((encoding = strchr(name, ':')) &&
		    (encoding = strchr(encoding + 1, ':'))) {
		    *encoding++ = '\0';
		    charset = _fallcAddCT(name, encoding);
		}
		if (charset == NULL) {
		    charset = _fallcGetCharSet(name);
		    if (charset == NULL &&
			(charset = _fallcCreateDefaultCharSet(name, ""))) {
			charset->side = codeset->side;
			charset->char_size = codeset->length;
			_fallcAddCharSet(charset);
		    }
		}
		if (charset) {
		    if (add_charset(codeset, charset) == False){
			free_charset(lcd);
			return False;
		    }
		}
	    }
	}

	if (codeset == NULL)
	    break;
	codeset->cs_num = i;
        /* For VW/UDC */
        /***** 3.4.2 byteM (1 <= M <= length)*****/
        for(M=1; M-1  < codeset->length; M++){
            long start,end;
            ByteInfo tmpb;

            sprintf(name,"%s.%s%d",cs,"byte",M);
            _fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);

            if( M == 1){
                if(num < 1) {
                    codeset->byteM = NULL ;
                    break ;
                }
                codeset->byteM =
                    (ByteInfoListRec *)Xmalloc(
                         (codeset->length)*sizeof(ByteInfoListRec));
                if(codeset->byteM == NULL){
                        free_charset(lcd);
			return False;
                }
            }

            if(num > 0){
                dbg_printValue(name,value,num);
                (codeset->byteM)[M-1].M = M;
                (codeset->byteM)[M-1].byteinfo_num = num;
                (codeset->byteM)[M-1].byteinfo =
                    (ByteInfo)Xmalloc( num * sizeof(ByteInfoRec));
                for(ii = 0 ; ii < num ; ii++){
                    char tmp[128];
                    tmpb = (codeset->byteM)[M-1].byteinfo ;
                    /* default 0x00 - 0xff */
                    sscanf(value[ii], "\\x%lx,\\x%lx", (long unsigned *) &start, (long unsigned *) &end);
                    tmpb[ii].start = (unsigned char)start;
                    tmpb[ii].end  = (unsigned char)end;
                }
            }
            /* .... */
        }


        /***** codeset.mb_conversion *****/
        sprintf(name, "%s.%s", cs, "mb_conversion");
        _fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);
        if (num > 0) {
                dbg_printValue(name,value,num);
                codeset->mbconv = Xmalloc(sizeof(ConversionRec));
                codeset->mbconv->convlist =
                falparse_scopemaps(value[0],&(codeset->mbconv->conv_num));
                dmpscope("mb_conv",codeset->mbconv->convlist,
                        codeset->mbconv->conv_num);
                /* [\x%x,\x%x]->\x%x,... */
        }
        /***** codeset.ct_conversion *****/
        sprintf(name, "%s.%s", cs, "ct_conversion");
        _fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);
        if (num > 0) {
                dbg_printValue(name,value,num);
                codeset->ctconv = Xmalloc(sizeof(ConversionRec));
                codeset->ctconv->convlist =
                falparse_scopemaps(value[0],&(codeset->ctconv->conv_num));
                dmpscope("ctconv",codeset->ctconv->convlist,
                        codeset->ctconv->conv_num);
                /* [\x%x,\x%x]->\x%x,... */
        }
        /***** codeset.ct_conversion_file *****/
        sprintf(name, "%s.%s", cs, "ct_conversion_file");
        _fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);
        if (num > 0) {
                dbg_printValue(name,value,num);
                /* [\x%x,\x%x]->\x%x,... */
        }
        /***** codeset.ct_extended_segment *****/
        sprintf(name, "%s.%s", cs, "ct_extended_segment");
        _fallcGetResource(lcd, "XLC_XLOCALE", name, &value, &num);
        if (num > 0) {
                dbg_printValue(name,value,num);
                codeset->ctextseg = create_ctextseg(value,num);
                /* [\x%x,\x%x]->\x%x,... */
        }
        /* For VW/UDC end */

    }

    read_charset_define(lcd,gen);       /* For VW/UDC */
    read_segmentconversion(lcd,gen);    /* For VW/UDC */

    return True;
}

static Bool
initialize(XLCd lcd)
{
    XLCdPublicMethods superclass = (XLCdPublicMethods) _fallcPublicMethods;

    XLC_PUBLIC_METHODS(lcd)->superclass = superclass;

    if (superclass->pub.initialize) {
	if ((*superclass->pub.initialize)(lcd) == False)
	    return False;
    }

    if(load_generic(lcd) == False)
	return False;

    return True;
}
/* VW/UDC start 95.01.08 */
static void
freeByteM(CodeSet codeset)
{
    int i;
    ByteInfoList blst;
    if(codeset->byteM == NULL) {
	return ;
    }
    blst = codeset->byteM;
    for(i=0;i<codeset->length;i++){
	if(blst[i].byteinfo){
	    Xfree(blst[i].byteinfo);
	    blst[i].byteinfo = NULL;
	}
    }
    Xfree(codeset->byteM);
    codeset->byteM = NULL;
}
static void
freeConversion(CodeSet codeset)
{
    int i;
    Conversion mbconv,ctconv;
    if( codeset->mbconv ) {
	mbconv = codeset->mbconv;
	/*  ...  */
	if(mbconv->convlist){
	    Xfree(mbconv->convlist);
	    mbconv->convlist = NULL;
	}
	Xfree(mbconv);
	codeset->mbconv = NULL;
    }
    if( codeset->ctconv ) {
	ctconv = codeset->ctconv;
	/*  ...  */
	if(ctconv->convlist){
	    Xfree(ctconv->convlist);
	    ctconv->convlist = NULL;
	}
	Xfree(ctconv);
	codeset->ctconv = NULL;
    }
}
static void
freeExtdSegment(CodeSet codeset)
{
    int i;
    ExtdSegment ctextseg;
    if(codeset->ctextseg == NULL) {
	return ;
    }
    ctextseg = codeset->ctextseg;
    if(ctextseg->name){
	Xfree(ctextseg->name);
	ctextseg->name = NULL;
    }
    if(ctextseg->area){
	Xfree(ctextseg->area);
	ctextseg->area = NULL;
    }
    Xfree(codeset->ctextseg);
    codeset->ctextseg = NULL;
}
static void
freeParseInfo(CodeSet codeset)
{
    int i;
    ParseInfo parse_info;
    if(codeset->parse_info == NULL) {
	return ;
    }
    parse_info = codeset->parse_info;
    if(parse_info->encoding){
	Xfree(parse_info->encoding);
	parse_info->encoding = NULL;
    }
    Xfree(codeset->parse_info);
    codeset->parse_info = NULL;
}
static void
destroy_CodeSetList(XLCdGenericPart *gen)
{
    CodeSet *codeset = gen->codeset_list;
    int i;
    if(gen->codeset_num == 0) {
	return;
    }
    for(i=0;i<gen->codeset_num;i++){
        freeByteM(codeset[i]);
	freeConversion(codeset[i]);
	freeExtdSegment(codeset[i]);
	freeParseInfo(codeset[i]);
	if(codeset[i]->charset_list){
	    Xfree(codeset[i]->charset_list);
	    codeset[i]->charset_list = NULL;
	}
	Xfree(codeset[i]); codeset[i]=NULL;
    }
    Xfree(codeset); gen->codeset_list = NULL;
}

static void
destroy_SegConv(XLCdGenericPart *gen)
{
    SegConv seg = gen->segment_conv;
    int i;
    if(gen->segment_conv_num == 0) {
	return;
    }
    for(i=0;i<gen->segment_conv_num;i++){
	if(seg[i].source_encoding){
	    Xfree(seg[i].source_encoding);
	    seg[i].source_encoding = NULL;
	}
	if(seg[i].destination_encoding){
	    Xfree(seg[i].destination_encoding);
	    seg[i].destination_encoding = NULL;
	}
	if(seg[i].conv){
	    Xfree(seg[i].conv); seg[i].conv = NULL;
	}
    }
    Xfree(seg); gen->segment_conv = NULL;
}

static void
destroy_gen(XLCd lcd)
{
    XLCdGenericPart *gen = XLC_GENERIC_PART(lcd);
    destroy_SegConv(gen);
    destroy_CodeSetList(gen);
    if(gen->mb_parse_table){
	Xfree(gen->mb_parse_table);
	gen->mb_parse_table = NULL;
    }
    if(gen->mb_parse_list){
	Xfree(gen->mb_parse_list);
	gen->mb_parse_list = NULL;
    }
}
/* VW/UDC end 95.01.08 */
static void
destroy(XLCd lcd)
{
    XLCdPublicMethods superclass = XLC_PUBLIC_METHODS(lcd)->superclass;

    destroy_gen(lcd); /* ADD 1996.01.08 */
    if (superclass && superclass->pub.destroy)
	(*superclass->pub.destroy)(lcd);
}
