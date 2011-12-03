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


#include <gcl/Curve.h>
#include <gcl/UnitTest.h>

using namespace GCL;
namespace CurveTest
{

void Test()
{
	TEST_START

	const WorldPoint3 p1(0.0,0.0,0.0);
	const WorldPoint3 p2(1.0,1.0,0.0);
	const WorldPoint3 p3(2.0,1.0,0.0);
	const WorldPoint3 p4(4.0,0.0,0.0);
	const WorldUnit t = 0.5;
	const WorldPoint3 pos1 = Curve::BezierCurve(p1,p2,p3,p4, t);
	std::stringstream s;
	s<<pos1<<"==WorldPoint3(1.625, 0.75, 0)";
	AssertMsg_Test(pos1==WorldPoint3(1.625, 0.75, 0), s.str().c_str());

	std::vector<WorldPoint3> p;
	p.push_back(p1);
	p.push_back(p2);
	p.push_back(p3);
	p.push_back(p4);
	WorldPoint3 pos2 = Curve::BezierCurvev(p, t);
	s.str("");
	s<<pos2<<"==WorldPoint3(2, 0.625, 0)";
	AssertMsg_Test(pos2==WorldPoint3(2, 0.625, 0), s.str().c_str());

	//TODO: those 2 bezier functions should probably return the same thing
}

}
