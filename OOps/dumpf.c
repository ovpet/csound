/*
    dumpf.c:

    Copyright (C) 1991 Barry Vercoe, John ffitch

    This file is part of Csound.

    The Csound Library is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    Csound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/

#include "cs.h"                                      /*  DUMPF.C  */
#include "dumpf.h"
#include <ctype.h>

int kdmpset(ENVIRON *csound, KDUMP *p)
{
    if (*p->ifilcod == SSTRCOD) {       /* open in curdir or pathname */
      char soundoname[1024];
      if (p->STRARG == NULL)
        strcpy(soundoname, unquote(csound->currevent->strarg));
      else strcpy(soundoname,unquote(p->STRARG));    /* unquote it, else use */

      if ((p->fdch.fdc = openout(soundoname,1)) < 0) {
        return csound->InitError(csound, Str("Cannot open %s"), soundoname);
      }
      p->fdch.fd = NULL;        /* Character file not audio */
      fdrecord(csound, &p->fdch);
      if ((p->format = (int)*p->iformat) < 1 || p->format > 8) {
        return csound->InitError(csound, Str("unknown format request"));
      }
      if (p->format == 2 || p->format == 3) {
        return csound->InitError(csound,
                                 Str("alaw and ulaw not implemented here"));
      }
      if ((p->timcount = (long)(*p->iprd * csound->ekr)) <= 0)
        p->timcount = 1;
      p->countdown = p->timcount;
    }
    else return csound->InitError(csound, Str("need quoted filename"));
    return OK;
}

int kdmp2set(ENVIRON *csound, KDUMP2 *p)
{
    if (*p->ifilcod == SSTRCOD) {       /* open in curdir or pathname */
      char soundoname[1024];
      if (p->STRARG == NULL)
        strcpy(soundoname, unquote(csound->currevent->strarg));
      else strcpy(soundoname,unquote(p->STRARG));    /* unquote it, else use */

      if ((p->fdch.fdc = openout(soundoname,1)) < 0) {
        return csound->InitError(csound, Str("Cannot open %s"), soundoname);
      }
      p->fdch.fd = NULL;        /* Character file not audio */
      fdrecord(csound, &p->fdch);
      if ((p->format = (int)*p->iformat) < 1 || p->format > 8) {
        return csound->InitError(csound, Str("unknown format request"));
      }
      if (p->format == 2 || p->format == 3) {
        return csound->InitError(csound,
                                 Str("alaw and ulaw not implemented here"));
      }
      if ((p->timcount = (long)(*p->iprd * csound->ekr)) <= 0)
        p->timcount = 1;
      p->countdown = p->timcount;
    }
    else return csound->InitError(csound, Str("need quoted filename"));
    return OK;
}

int kdmp3set(ENVIRON *csound, KDUMP3 *p)
{
    if (*p->ifilcod == SSTRCOD) {       /* open in curdir or pathname */
      char soundoname[1024];
      if (p->STRARG == NULL)
        strcpy(soundoname, unquote(csound->currevent->strarg));
      else strcpy(soundoname,unquote(p->STRARG));    /* unquote it, else use */

      if ((p->fdch.fdc = openout(soundoname,1)) < 0) {
        return csound->InitError(csound, Str("Cannot open %s"), soundoname);
      }
      p->fdch.fd = NULL;        /* Character file not audio */
      fdrecord(csound, &p->fdch);
      if ((p->format = (int)*p->iformat) < 1 || p->format > 8) {
        return csound->InitError(csound, Str("unknown format request"));
      }
      if (p->format == 2 || p->format == 3) {
        return csound->InitError(csound,
                                 Str("alaw and ulaw not implemented here"));
      }
      if ((p->timcount = (long)(*p->iprd * csound->ekr)) <= 0)
        p->timcount = 1;
      p->countdown = p->timcount;
    }
    else return csound->InitError(csound, Str("need quoted filename"));
    return OK;
}

int kdmp4set(ENVIRON *csound, KDUMP4 *p)
{
    if (*p->ifilcod == SSTRCOD) {       /* open in curdir or pathname */
      char soundoname[1024];
      if (p->STRARG == NULL)
        strcpy(soundoname, unquote(csound->currevent->strarg));
      else strcpy(soundoname,unquote(p->STRARG));    /* unquote it, else use */

      if ((p->fdch.fdc = openout(soundoname,1)) < 0) {
        return csound->InitError(csound, Str("Cannot open %s"), soundoname);
      }
      p->fdch.fd = NULL;        /* Character file not audio */
      fdrecord(csound, &p->fdch);
      if ((p->format = (int)*p->iformat) < 1 || p->format > 8) {
        return csound->InitError(csound, Str("unknown format request"));
      }
      if (p->format == 2 || p->format == 3) {
        return csound->InitError(csound,
                                 Str("alaw and ulaw not implemented here"));
      }
      if ((p->timcount = (long)(*p->iprd * csound->ekr)) <= 0)
        p->timcount = 1;
      p->countdown = p->timcount;
    }
    else return csound->InitError(csound, Str("need quoted filename"));
    return OK;
}

static void nkdump(ENVIRON *csound, MYFLT *kp, int ofd, int format, int nk)
{
    char  buf1[128], outbuf[256];
    int   len = 0;

    switch(format) {               /* place formatted kvals into outbuf */
    case 1: {
      int8_t *bp = (int8_t*) outbuf;
      len = nk;
      while (nk--)
        *bp++ = (int8_t) *kp++;
      break;
    }
    case 4: {
      int16_t *bp = (int16_t*) outbuf;
      len = nk * 2;
      while (nk--)
        *bp++ = (int16_t) *kp++;
      break;
    }
    case 5: {
      int32_t *bp = (int32_t*) outbuf;
      len = nk * 4;
      while (nk--)
        *bp++ = (int32_t) *kp++;
      break;
    }
    case 6: {
      float *bp = (float*) outbuf;
      len = nk * sizeof(float);
      while (nk--)
        *bp++ = (float) *kp++;
      break;
    }
    case 7:
      outbuf[0] = '\0';
      while (--nk) {
        sprintf(buf1, "%ld\t", (long) *kp++);
        strcat(outbuf, buf1);
      }
      sprintf(buf1, "%ld\n", (long) *kp);
      strcat(outbuf, buf1);
      len = strlen(outbuf);
      break;
    case 8: *outbuf = '\0';
      while (--nk) {
        sprintf(buf1, "%6.4f\t", *kp++);
        strcat(outbuf, buf1);
      }
      sprintf(buf1, "%6.4f\n", *kp);
      strcat(outbuf, buf1);
      len = strlen(outbuf);
      break;
    default: csound->Die(csound, Str("unknown kdump format"));
    }
    write(ofd, outbuf, len);            /* now write the buffer */
}


int kdump(ENVIRON *csound, KDUMP *p)
{
    MYFLT kval[4];

    if (--p->countdown <= 0) {
      p->countdown = p->timcount;
      kval[0] = *p->ksig;
      nkdump(csound, &(kval[0]), p->fdch.fdc, p->format, 1);
    }
    return OK;
}

int kdump2(ENVIRON *csound, KDUMP2 *p)
{
    MYFLT kval[4];

    if (--p->countdown <= 0) {
      p->countdown = p->timcount;
      kval[0] = *p->ksig1;
      kval[1] = *p->ksig2;
      nkdump(csound, &(kval[0]), p->fdch.fdc, p->format, 2);
    }
    return OK;
}

int kdump3(ENVIRON *csound, KDUMP3 *p)
{
    MYFLT kval[4];

    if (--p->countdown <= 0) {
      p->countdown = p->timcount;
      kval[0] = *p->ksig1;
      kval[1] = *p->ksig2;
      kval[2] = *p->ksig3;
      nkdump(csound, &(kval[0]), p->fdch.fdc, p->format, 3);
    }
    return OK;
}

int kdump4(ENVIRON *csound, KDUMP4 *p)
{
    MYFLT kval[4];

    if (--p->countdown <= 0) {
      p->countdown = p->timcount;
      kval[0] = *p->ksig1;
      kval[1] = *p->ksig2;
      kval[2] = *p->ksig3;
      kval[3] = *p->ksig4;
      nkdump(csound, &(kval[0]), p->fdch.fdc, p->format, 4);
    }
    return OK;
}


/* ******************************************************************** */
/* ******** READK and friends; new code 1999 Feb 14 by JPff    ******** */
/* ******************************************************************** */

int krdset(ENVIRON *csound, KREAD *p)
{
    if (*p->ifilcod == SSTRCOD) {       /* open in curdir or pathname */
      char soundiname[1024];
      if (p->STRARG == NULL)
        strcpy(soundiname, unquote(csound->currevent->strarg));
      else strcpy(soundiname,unquote(p->STRARG));    /* unquote it, else use */

      if ((p->fdch.fdc = openin(soundiname)) < 0) {
        return csound->InitError(csound, Str("Cannot open %s"), soundiname);
      }
      p->fdch.fd = NULL;        /* Character file not audio */
      fdrecord(csound, &p->fdch);
      if ((p->format = (int)*p->iformat) < 1 || p->format > 8) {
        return csound->InitError(csound, Str("unknown format request"));
      }
      if (p->format == 2 || p->format == 3) {
        return csound->InitError(csound,
                                 Str("alaw and ulaw not implemented here"));
      }
      if ((p->timcount = (long)(*p->iprd * csound->ekr)) <= 0)
        p->timcount = 1;
      p->countdown = 0;
    }
    else {
      return csound->InitError(csound, Str("need quoted filename"));
    }
    p->k[0] = p->k[1] = p->k[2] = p->k[3] = FL(0.0);
    return OK;
}

int krd2set(ENVIRON *csound, KREAD2 *p)
{
    if (*p->ifilcod == SSTRCOD) {       /* open in curdir or pathname */
      char soundiname[1024];
      if (p->STRARG == NULL)
        strcpy(soundiname, unquote(csound->currevent->strarg));
      else strcpy(soundiname,unquote(p->STRARG));    /* unquote it, else use */
      if ((p->fdch.fdc = openin(soundiname)) < 0) {
        return csound->InitError(csound, Str("Cannot open %s"), soundiname);
      }
      p->fdch.fd = NULL;        /* Character file not audio */
      fdrecord(csound, &p->fdch);
      if ((p->format = (int)*p->iformat) < 1 || p->format > 8) {
        return csound->InitError(csound, Str("unknown format request"));
      }
      if (p->format == 2 || p->format == 3) {
        return csound->InitError(csound,
                                 Str("alaw and ulaw not implemented here"));
      }
      if ((p->timcount = (long)(*p->iprd * csound->ekr)) <= 0)
        p->timcount = 1;
      p->countdown = 0;
    }
    else {
      return csound->InitError(csound, Str("need quoted filename"));
    }
    p->k[0] = p->k[1] = p->k[2] = p->k[3] = FL(0.0);
    return OK;
}

int krd3set(ENVIRON *csound, KREAD3 *p)
{
    if (*p->ifilcod == SSTRCOD) {       /* open in curdir or pathname */
      char soundiname[1024];
      if (p->STRARG == NULL)
        strcpy(soundiname, unquote(csound->currevent->strarg));
      else strcpy(soundiname,unquote(p->STRARG));    /* unquote it, else use */
      if ((p->fdch.fdc = openin(soundiname)) < 0) {
        return csound->InitError(csound, Str("Cannot open %s"), soundiname);
      }
      p->fdch.fd = NULL;        /* Character file not audio */
      fdrecord(csound, &p->fdch);
      if ((p->format = (int)*p->iformat) < 1 || p->format > 8) {
        return csound->InitError(csound, Str("unknown format request"));
      }
      if (p->format == 2 || p->format == 3) {
        return csound->InitError(csound,
                                 Str("alaw and ulaw not implemented here"));
      }
      if ((p->timcount = (long)(*p->iprd * csound->ekr)) <= 0)
        p->timcount = 1;
      p->countdown = 0;
    }
    else {
      return csound->InitError(csound, Str("need quoted filename"));
    }
    p->k[0] = p->k[1] = p->k[2] = p->k[3] = FL(0.0);
    return OK;
}

int krd4set(ENVIRON *csound, KREAD4 *p)
{
    if (*p->ifilcod == SSTRCOD) {       /* open in curdir or pathname */
      char soundiname[1024];
      if (p->STRARG == NULL)
        strcpy(soundiname, unquote(csound->currevent->strarg));
      else strcpy(soundiname,unquote(p->STRARG));    /* unquote it, else use */
      if ((p->fdch.fdc = openin(soundiname)) < 0) {
        return csound->InitError(csound, Str("Cannot open %s"), soundiname);
      }
      p->fdch.fd = NULL;        /* Character file not audio */
      fdrecord(csound, &p->fdch);
      if ((p->format = (int)*p->iformat) < 1 || p->format > 8) {
        return csound->InitError(csound, Str("unknown format request"));
      }
      if (p->format == 2 || p->format == 3) {
        return csound->InitError(csound,
                                 Str("alaw and ulaw not implemented here"));
      }
      if ((p->timcount = (long)(*p->iprd * csound->ekr)) <= 0)
        p->timcount = 1;
      p->countdown = 0;
    }
    else {
      return csound->InitError(csound, Str("need quoted filename"));
    }
    p->k[0] = p->k[1] = p->k[2] = p->k[3] = FL(0.0);
    return OK;
}

static void nkread(ENVIRON *csound, MYFLT *kp, int ifd, int format, int nk)
{
    int   len;
    char  inbuf[256];

    switch(format) {               /* place formatted kvals into outbuf */
    case 1: {
      int8_t *bp = (int8_t*) inbuf;
      len = nk;
      read(ifd, inbuf, len);            /* now read the buffer */
      while (nk--) {
        *kp++ = (MYFLT) *bp++;
        break;
      }
    }
    case 4: {
      int16_t *bp = (int16_t*) inbuf;
      len = nk * 2;
      read(ifd, inbuf, len);            /* now read the buffer */
      while (nk--)
        *kp++ = (MYFLT) *bp++;
      break;
    }
    case 5: {
      int32_t *bp = (int32_t*) inbuf;
      len = nk * 4;
      read(ifd, inbuf, len);            /* now read the buffer */
      while (nk--)
        *kp++ = (MYFLT) *bp++;
      break;
    }
    case 6: {
      float *bp = (float*) inbuf;
      len = nk * sizeof(float);
      read(ifd, inbuf, len);            /* now read the buffer */
      while (nk--)
        *kp++ = (MYFLT) *bp++;
      break;
    }
    case 7:
      while (nk--) {
        char *bp = inbuf;
        do {                  /* Skip whitespace */
          read(ifd, bp, 1);
        } while (isspace(*bp));
        do {                  /* Absorb digits */
          read(ifd, ++bp, 1);
        } while (isdigit(*bp));
        lseek(ifd, (off_t)(-1), SEEK_CUR);
        *bp = '\0';
#ifndef USE_DOUBLE
        sscanf(inbuf,"%f", kp);
#else
        sscanf(inbuf,"%lf", kp);
#endif
        kp++;
      }
      break;
    case 8:
      while (nk--) {
        char * bp = inbuf;
        do {                  /* Skip whitespace */
          read(ifd, bp, 1);
        } while (isspace(*bp));
        do {                  /* Absorb digits and such*/
          read(ifd, ++bp, 1);
        } while (!isspace(*bp));
        lseek(ifd, (off_t)(-1), SEEK_CUR);
        *bp = '\0';
#ifndef USE_DOUBLE
        sscanf(inbuf,"%f", kp);
#else
        sscanf(inbuf,"%lf", kp);
#endif
        kp++;
      }
      break;
    default: csound->Die(csound, Str("unknown kdump format"));
    }
}

int kread(ENVIRON *csound, KREAD *p)
{
    MYFLT kval[4];

    if (--p->countdown <= 0) {
      p->countdown = p->timcount;
      nkread(csound, &(kval[0]), p->fdch.fdc, p->format, 1);
      *p->k1 = p->k[0] = kval[0];
    }
    else *p->k1 = p->k[0];
    return OK;
}

int kread2(ENVIRON *csound, KREAD2 *p)
{
    MYFLT kval[4];

    if (--p->countdown <= 0) {
      p->countdown = p->timcount;
      nkread(csound, &(kval[0]), p->fdch.fdc, p->format, 2);
      *p->k1 = p->k[0] = kval[0];
      *p->k2 = p->k[1] = kval[1];
    }
    else {
      *p->k1 = p->k[0];
      *p->k2 = p->k[1];
    }
    return OK;
}

int kread3(ENVIRON *csound, KREAD3 *p)
{
    MYFLT kval[4];

    if (--p->countdown <= 0) {
      p->countdown = p->timcount;
      nkread(csound, &(kval[0]), p->fdch.fdc, p->format, 3);
      *p->k1 = p->k[0] = kval[0];
      *p->k2 = p->k[1] = kval[1];
      *p->k3 = p->k[2] = kval[2];
    }
    else {
      *p->k1 = p->k[0];
      *p->k2 = p->k[1];
      *p->k3 = p->k[2];
    }
    return OK;
}

int kread4(ENVIRON *csound, KREAD4 *p)
{
    MYFLT kval[4];

    if (--p->countdown <= 0) {
      p->countdown = p->timcount;
      nkread(csound, &(kval[0]), p->fdch.fdc, p->format, 4);
      *p->k1 = p->k[0] = kval[0];
      *p->k2 = p->k[1] = kval[1];
      *p->k3 = p->k[2] = kval[2];
      *p->k4 = p->k[3] = kval[3];
    }
    else {
      *p->k1 = p->k[0];
      *p->k2 = p->k[1];
      *p->k3 = p->k[2];
      *p->k4 = p->k[3];
    }
    return OK;
}

