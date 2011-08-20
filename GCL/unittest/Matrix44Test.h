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


#include <GCL/Matrix44.h>
#include <GCL/Math.h>

#include <GCL/UnitTest.h>

using namespace GCL;
namespace Matrix44Test
{
TEST_START
void Test()
{

	Matrix44 myMat;
	WorldPoint3 myVec;

	//rot x test
	myMat.SetRotationX(DegreeToRadian(90.0));
	myMat =  Matrix44::IDENTITY*myMat;
	myVec = WorldPoint3(0,1,0);
	WorldPoint3 out = myVec * myMat;
	Assert_Test(out == WorldPoint3(0,0,-1));

	//rot y test
	myMat.SetRotationY(DegreeToRadian(90.0));
	myMat =  Matrix44::IDENTITY*myMat ;
	myVec = WorldPoint3(1,0,0);
	out = myVec * myMat;
	Assert_Test(out == WorldPoint3(0,0,1));

	//rot z test
	myMat.SetRotationZ(DegreeToRadian(90.0));
	myMat =  Matrix44::IDENTITY*myMat ;
	myVec = WorldPoint3(1,0,0);
	out = myVec * myMat;
	Assert_Test(out == WorldPoint3(0,-1,0));




}

}
