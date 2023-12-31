/* w_lgammaf.c -- float version of w_lgamma.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include <sys/cdefs.h>
#if defined(LIBM_SCCS) && !defined(lint)
__RCSID("$NetBSD: w_lgammaf.c,v 1.7 2002/05/26 22:02:02 wiz Exp $");
#endif

#include "math.h"
#include "math_private.h"

float
lgammaf(float x)
{
#ifdef _IEEE_LIBM
	return __ieee754_lgammaf_r(x,&signgam);
#else
        float y;
        y = __ieee754_lgammaf_r(x,&signgam);
        if(_LIB_VERSION == _IEEE_) return y;
        if(!finitef(y)&&finitef(x)) {
            if(floorf(x)==x&&x<=(float)0.0)
	        /* lgamma pole */
                return (float)__kernel_standard((double)x,(double)x,115);
            else
	        /* lgamma overflow */
                return (float)__kernel_standard((double)x,(double)x,114);
        } else
            return y;
#endif
}
