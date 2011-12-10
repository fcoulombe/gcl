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
#include <gcl/Point4.h>

using namespace GCL;
namespace Point4Test
{
void Test();
void Test()
{
	TEST_START

	Real arr[] = {1.0,1.0,1.0, 1.0};
	WorldPoint4 t1(arr);
	WorldPoint4 t2(1.0,1.0,1.0,1.0);
	WorldPoint4 t3(1.0,1.0,1.0,1.0);
	WorldPoint4 t4(0.0,1.0,1.0,1.0);
	Real scalar = 2.0;
	int iscalar =5;

	Assert_Test(t1+t2 == WorldPoint4(2,2,2,2));
	Assert_Test(t2-t3 == WorldPoint4(0,0,0,0));
	Assert_Test(t1*t2 == WorldPoint4(1,1,1,1));
	Assert_Test(t1/t2 == WorldPoint4(1,1,1,1));
	Assert_Test(t1%t2 == 4);

	t1+=t2;
	Assert_Test(t1 == WorldPoint4(2,2,2,2));

	t2-=t3 ;
	Assert_Test(t2 == WorldPoint4(0,0,0,0));

	t1*=t4 ;
	Assert_Test(t1 == WorldPoint4(0,2,2,2));

	t4/=t3 ;
	Assert_Test(t4 == WorldPoint4(0,1,1,1));

	t1 = WorldPoint4(10,2,-2,2);

	Assert_Test(t1*scalar == WorldPoint4(20,4,-4,4));
	Assert_Test(t1*iscalar == WorldPoint4(50,10,-10,10));
	Assert_Test(t1/scalar == WorldPoint4(5,1,-1,1));
	Assert_Test(t1/iscalar == WorldPoint4(2,0.4,-0.4,0.4));
	Assert_Test(scalar*t1 == WorldPoint4(20,4,-4,4));

	t4.Normalize();

	std::stringstream s;
	s<<std::endl<<t4 <<"== WorldPoint4(0, 0.5773502692, 0.5773502692, 0.5773502692)";
	AssertMsg_Test(t4 == WorldPoint4(0, 0.5773502692, 0.5773502692, 0.5773502692), s.str().c_str());

	s.str("");
	s<<std::endl<<t3.Length() <<"==2.0";
	AssertMsg_Test(abseq(t3.Length(),2.0, DBL_PRECISION_TOLERANCE), s.str().c_str());

	s.str("");
	s<<std::endl<<t3.LengthSqr()<<" == 4.0";
	AssertMsg_Test(abseq(t3.LengthSqr(), 4.0,DBL_PRECISION_TOLERANCE),s.str().c_str());

	s.str("");
	const float floatInit[] = {1.0f,0.5f,0.2f, 0.1f};
	WorldPoint4 wp4FloatInit(floatInit);
	s<<wp4FloatInit<<" == " << WorldPoint4(1.0,0.5,0.2, 0.1);
	AssertMsg_Test(wp4FloatInit==WorldPoint4(1.0,0.5,0.2, 0.1),s.str().c_str());

}
}
