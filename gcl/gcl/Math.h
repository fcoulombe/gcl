/*
 * Copyright (C) 2011 by Francois Coulombe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once
#include <math.h>
#include <stdlib.h>

#include "gcl/Macro.h"
#include "gcl/WorldUnit.h"

namespace GCL
{

const Real PI = 3.14159265;
const Real RADIAN = 57.2957795;
const Real DEGREE = 0.0174532925;

GCLINLINE Real DegreeToRadian(Real degree) { return degree * PI/180.0; }
GCLINLINE Real RadianToDegree(Real radian) { return radian * 180.0/PI; }


GCLINLINE Real Randf(Real vmin, Real vmax)
{
	return vmin + ((Real)rand() / (Real)RAND_MAX) * (vmax - vmin);
}

GCLINLINE size_t UpgradeToNextPowerOf2(size_t value)
{
    Real c = ceil(log(value)/log(2));

	return (size_t)pow(2, c);
}

}
