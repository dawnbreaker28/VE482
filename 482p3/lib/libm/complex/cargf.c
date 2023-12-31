/* $NetBSD: cargf.c,v 1.1 2007/08/20 16:01:31 drochner Exp $ */

/*
 * Written by Matthias Drochner <drochner@NetBSD.org>.
 * Public domain.
 */

#include "../src/namespace.h"
#include <complex.h>
#include <math.h>

float
cargf(float complex z)
{

	return atan2f(__imag__ z, __real__ z);
}
