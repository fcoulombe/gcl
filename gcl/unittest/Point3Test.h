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
void Test();
void Test()
{
	TEST_START
    {
        //equal test
        Point3<uint8_t> eqTest1(10,11,12);
        Point3<uint8_t> eqTest2;
        eqTest2 = eqTest1;
        Assert_Test(eqTest2 == eqTest1);
        eqTest2.x = 18;
        Assert_Test(eqTest2 != eqTest1);
    }
	Real arr[] = {1.0,1.0,1.0};
	WorldPoint3 t1(arr);
	WorldPoint3 t2(1.0,1.0,1.0);
	WorldPoint3 t3(1.0,1.0,1.0);
	WorldPoint3 t4(0.0,1.0,1.0);
	Real scalar = 2.0;
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

    //precision conversion test
    {
    WorldPoint3 lhs;
    Point3<float> rhs(1.0, 2.0, 3.0);
    lhs = rhs;
    Assert_Test(lhs == WorldPoint3(1.0, 2.0, 3.0));

    WorldPoint3 copyConstructor(rhs);

    Assert_Test(copyConstructor == WorldPoint3(1.0, 2.0, 3.0));
    }
}
}
