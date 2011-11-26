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

#include <gcl/UnitTest.h>
#include <gcl/Point3.h>

using namespace GCL;
namespace Point3Test
{

void Test()
{
	TEST_START

	double arr[] = {1.0,1.0,1.0};
	WorldPoint3 t1(arr);
	WorldPoint3 t2(1.0,1.0,1.0);
	WorldPoint3 t3(1.0,1.0,1.0);
	WorldPoint3 t4(0.0,1.0,1.0);
	double scalar = 2.0;
	int iscalar =5;

	Assert_Test(t1+t2 == WorldPoint3(2,2,2));
	Assert_Test(t2-t3 == WorldPoint3(0,0,0));
	Assert_Test(t1*t2 == WorldPoint3(1,1,1));
	Assert_Test(t1/t2 == WorldPoint3(1,1,1));
	Assert_Test(t1%t2 == 3);

	WorldPoint3 res = t1^t4 ;
	Assert_Test(res == WorldPoint3(0,-1,1));

	t1+=t2;
	Assert_Test(t1 == WorldPoint3(2,2,2));

	t2-=t3 ;
	Assert_Test(t2 == WorldPoint3(0,0,0));

	t1*=t4 ;
	Assert_Test(t1 == WorldPoint3(0,2,2));

	t4/=t3 ;
	Assert_Test(t4 == WorldPoint3(0,1,1));

	t1^=WorldPoint3(1,-2,3) ;
	Assert_Test(t1 == WorldPoint3(10,2,-2));

	Assert_Test(t1*scalar == WorldPoint3(20,4,-4));
	Assert_Test(t1*iscalar == WorldPoint3(50,10,-10));
	Assert_Test(t1/scalar == WorldPoint3(5,1,-1));
	Assert_Test(t1/iscalar == WorldPoint3(2,0.4,-0.4));
	Assert_Test(scalar*t1 == WorldPoint3(20,4,-4));

	t4.Normalize();

	Assert_Test(t4 == WorldPoint3(0, 0.7071067812, 0.7071067812));
	Assert_Test(abseq(t3.Length(),1.732050808, DBL_PRECISION_TOLERANCE));
	Assert_Test(t3.LengthSqr() == 3);
}
}
