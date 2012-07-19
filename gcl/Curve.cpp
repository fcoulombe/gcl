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

#include "gcl/Curve.h"


using namespace GCL;


WorldPoint3 Curve::BezierCurve(const WorldPoint3& p1, const WorldPoint3& p2, const WorldPoint3& p3, const WorldPoint3& p4, Real t)
{
   Real mum1,mum13,mu3;
   mum1 = 1.0 - t;
   mum13 = mum1 * mum1 * mum1;
   mu3 = t * t * t;

   WorldPoint3 p;
   p.x = mum13*p1.x + 3*t*mum1*mum1*p2.x + 3*t*t*mum1*p3.x + mu3*p4.x;
   p.y = mum13*p1.y + 3*t*mum1*mum1*p2.y + 3*t*t*mum1*p3.y + mu3*p4.y;
   p.z = mum13*p1.z + 3*t*mum1*mum1*p2.z + 3*t*t*mum1*p3.z + mu3*p4.z;

   return p;
}

WorldPoint3 Curve::BezierCurvev(const std::vector<WorldPoint3 >& p, Real t)
{

	Real blend,muk,munk;
	size_t count = p.size();
	WorldPoint3 b(0.0, 0.0, 0.0);

	muk = 1.0;
	munk = pow((Real)1.0-t,(Real)count);

	for(size_t k=0;k<count;k++)
	{
		int kn,nn,nkn;
		nn = count;
		kn = k;
		nkn = count - k;
		blend = muk * munk;
		muk *= t;
		munk /= (1.0-t);
		while (nn >= 1)
		{
			blend *= (Real)nn;
			--nn;
			if(kn > 1)
			{
				blend /= (Real)kn;
				--kn;
			}
			if (nkn > 1)
			{
				blend /= (Real)nkn;
				--nkn;
			}
		}
		b.x += p[k].x * blend;
		b.y += p[k].y * blend;
		b.z += p[k].z * blend;
	}
	return b;
}
