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

#include <gcl/Point2.h>

using namespace GCL;
namespace Point2Test
{

void Test()
{
	TEST_START

	double arr[] = {1.0,1.0};
	WorldPoint2 t1(arr);
	WorldPoint2 t2(1.0,1.0);
	WorldPoint2 t3(1.0,1.0);
	WorldPoint2 t4(0.0,1.0);
	double scalar = 2.0;
	int iscalar =5;

	Assert_Test(t1+t2 == WorldPoint2(2,2));
	Assert_Test(t2-t3 == WorldPoint2(0,0));
	Assert_Test(t1*t2 == WorldPoint2(1,1));
	Assert_Test(t1/t2 == WorldPoint2(1,1));
	Assert_Test(t1%t2 == 2);



	t1+=t2;
	Assert_Test(t1 == WorldPoint2(2,2));

	t2-=t3 ;
	Assert_Test(t2 == WorldPoint2(0,0));

	t1*=t4 ;
	Assert_Test(t1 == WorldPoint2(0,2));

	t4/=t3 ;
	Assert_Test(t4 == WorldPoint2(0,1));

	t1=WorldPoint2(10,2);

	Assert_Test(t1*scalar == WorldPoint2(20,4));
	Assert_Test(t1*iscalar == WorldPoint2(50,10));
	Assert_Test(t1/scalar == WorldPoint2(5,1));
	Assert_Test(t1/iscalar == WorldPoint2(2,0.4));
	Assert_Test(scalar*t1 == WorldPoint2(20,4));

	t4.Normalize();

	Assert_Test(t4 == WorldPoint2(0, 1));

	std::stringstream s1;
	s1<<t3.Length()<<"==1.414213562";
	AssertMsg_Test(abseq(t3.Length(),1.414213562, DBL_PRECISION_TOLERANCE), s1.str().c_str());


	std::stringstream s2;
	s2<<t3.LengthSqr()<<"==2.0";
	AssertMsg_Test(abseq(t3.LengthSqr(),2.0, DBL_PRECISION_TOLERANCE), s2.str().c_str());
}
}
