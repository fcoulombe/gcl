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

#include <sstream>
#include <gcl/UnitTest.h>
#include <gcl/Math.h>


using namespace GCL;
namespace MathTest
{
void Test();
void Test()
{
	TEST_START
	std::stringstream s;

	Real radTest = DegreeToRadian(90.0) ;
	s.str("");
	s<< radTest << " == " << PI/2.0<<std::endl;
	AssertMsg_Test(abseq(radTest, PI/2.0, DBL_PRECISION_TOLERANCE), s.str().c_str());
	Real degTest = RadianToDegree(PI/2.0) ;
	s.str("");
	s<< degTest << " == " << 90.0<<std::endl;
	AssertMsg_Test(abseq(degTest, 90.0, DBL_PRECISION_TOLERANCE), s.str().c_str());


	Real randTest = Randf(1.0, 4.0);
	(void)randTest;


	size_t nextPOTTest1 = UpgradeToNextPowerOf2(3);
	Assert_Test(nextPOTTest1 == 4);
	size_t nextPOTTest2 = UpgradeToNextPowerOf2(6);
	Assert_Test(nextPOTTest2 == 8);
	size_t nextPOTTest3 = UpgradeToNextPowerOf2(12);
	Assert_Test(nextPOTTest3 == 16);
}
}
