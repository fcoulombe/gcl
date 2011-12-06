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


#include <gcl/Matrix44.h>
#include <gcl/Math.h>

#include <gcl/UnitTest.h>
#include <iomanip>

using namespace GCL;
namespace Matrix44Test
{
    void Test();
void Test()
{
	TEST_START
	Matrix44 myMat;
	WorldPoint3 myVec;

	//equal test
	myMat = Matrix44::IDENTITY;
	const WorldUnit testIdentityMatrix[] =  {
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1};
	Assert_Test(myMat == Matrix44(testIdentityMatrix));

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

	//inverse tests
	Matrix44 tempMatrix;
	//asserting that inverse throws an exception when diving by zero
	memset(&tempMatrix, 0, sizeof(Matrix44));
	bool exceptZero = false;
	try
	{
	tempMatrix = Inverse(tempMatrix);
	}
	catch (GCLException &e)
	{
		exceptZero = true;
	}
	Assert_Test(exceptZero);

	//proper inverse
	tempMatrix = Inverse(myMat);
	const WorldUnit testMatrix[] =  {
			1.794896737e-09, 1, 0, 0,
			-1, 1.794896737e-09, 0, 0,
			0, -0, 1, 0,
			0, 0, 0, 1};

	std::stringstream s;
	s << tempMatrix << std::endl << "==" << std::endl << Matrix44(testMatrix);
	AssertMsg_Test(tempMatrix==Matrix44(testMatrix), s.str().c_str());

	//perspective test
	Matrix44 perspective;
	perspective.SetPerspective( 45.0,640.0/480.0,0.1,100.0);

	Matrix44 testPerspective;
	testPerspective[0] = WorldPoint4(1.810660174077882, 0.0, 0.0, 0.0);
	testPerspective[1] = WorldPoint4(0.0, 2.414213565437175, 0.0, 0.0);
	testPerspective[2] = WorldPoint4(0.0, 0.0, -1.002002002002002, -1.0);
	testPerspective[3] = WorldPoint4(-0.0, -0.0, -0.2002002002002002, -0.0);
	s.str("");
	s <<std::setprecision(16)<< std::endl<<perspective << std::endl << "==" << std::endl << testPerspective;
	AssertMsg_Test(perspective==testPerspective, s.str().c_str());


	{

		const float fidentity[16] = {1.0f,0.f,0.f,0.f,
									0.f,1.0f,0.f,0.f,
									0.f,0.f,1.f,0.f,
									0.f,0.f,0.f,1.0f};
		Matrix44 matIdentity(fidentity);
		s.str("");
		s<<std::endl<<matIdentity<<std::endl<<"=="<<std::endl<<Matrix44::IDENTITY;
		AssertMsg_Test(matIdentity==Matrix44::IDENTITY, s.str().c_str());
	}
}

}
