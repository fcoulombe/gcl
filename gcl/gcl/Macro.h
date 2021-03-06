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

#include <limits>
#include <cmath>
#include <stdint.h>
#define GCLINLINE inline
#define GCLEXPORT

namespace GCL
{

template <class T>
GCLINLINE bool eq(T lhs, T rhs)
{
  return lhs ==rhs;
}

template <typename T, typename T2>
GCLINLINE bool abseq(T lhs, T2 rhs, T epsilon = std::numeric_limits<T>::epsilon())
{
  return fabs(lhs - rhs) < epsilon;
}

template <typename T>
GCLINLINE const T clamp(const T val, const T mininum, const T maximum)
{
	return val < mininum ? mininum : (val > maximum ? maximum : val);
}

}
