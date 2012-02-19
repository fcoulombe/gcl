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

#include <iomanip>
#include <sstream>

#include <gcl/Matrix44.h>
#include <gcl/Math.h>

#include <gcl/UnitTest.h>


using namespace GCL;
namespace Matrix44Test
{
void Test();
void Test()
{
	TEST_START
	Matrix44 myMat;

	//equal test
	myMat = Matrix44::IDENTITY;
	const Real testIdentityMatrix[] =  {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1};
	Assert_Test(myMat == Matrix44(testIdentityMatrix));

	std::stringstream s;
	//set
	{
		const Real mat[] = {1.0, 2.0, 3.0, 4.0,
				5.0, 6.0, 7.0, 8.0,
				9.0, 10.0, 11.0, 12.0,
				13.0, 14.0, 15.0, 16.0};
		Matrix44 myMat2(mat);
		myMat.Set(myMat2);
		s.str("");
		s<<std::endl<<myMat[0].x<<" == 1.0"<<std::endl;
		s<<myMat[0].y<<" == 2.0"<<std::endl;
		s<<myMat[0].z<<" == 3.0"<<std::endl;
		s<<myMat[0].w<<" == 4.0"<<std::endl;
		s<<	myMat[1].x<<" == 5.0"<<std::endl;
		s<<	myMat[1].y<<" == 6.0"<<std::endl;
		s<<	myMat[1].z<<" == 7.0"<<std::endl;
		s<<	myMat[1].w<<" == 8.0"<<std::endl;
		s<<	myMat[2].x<<" == 9.0"<<std::endl;
		s<<	myMat[2].y<<" == 10.0"<<std::endl;
		s<<	myMat[2].z<<" == 11.0"<<std::endl;
		s<<	myMat[2].w<<" == 12.0"<<std::endl;
		s<<	myMat[3].x<<" == 13.0"<<std::endl;
		s<<	myMat[3].y<<" == 14.0"<<std::endl;
		s<<	myMat[3].z<<" == 15.0"<<std::endl;
		s<<	myMat[3].w<<" == 16.0";
		AssertMsg_Test(myMat[0].x == 1.0 &&
				myMat[0].y == 2.0 &&
				myMat[0].z == 3.0 &&
				myMat[0].w == 4.0 &&
				myMat[1].x == 5.0 &&
				myMat[1].y == 6.0 &&
				myMat[1].z == 7.0 &&
				myMat[1].w == 8.0 &&
				myMat[2].x == 9.0 &&
				myMat[2].y == 10.0 &&
				myMat[2].z == 11.0 &&
				myMat[2].w == 12.0 &&
				myMat[3].x == 13.0 &&
				myMat[3].y == 14.0 &&
				myMat[3].z == 15.0 &&
				myMat[3].w == 16.0, s.str().c_str());

	}
	//rot x test
	{
		s.str("");
		myMat.SetRotationX(DegreeToRadian(90.0));
		WorldPoint3 myVec = WorldPoint3(0.0,1.0,0.0);
		WorldPoint3 out = myVec * myMat;
		s<<out << " == WorldPoint3(0.0,0.0,-1.0)";
		AssertMsg_Test(out == WorldPoint3(0.0,0.0,-1.0), s.str().c_str());
	}
	{
		s.str("");
		myMat.SetRotationX(DegreeToRadian(90.0));
		Matrix44 myMat2;
		myMat2.SetRotationX(DegreeToRadian(90.0));
		Matrix44 myMat3;
		myMat3 = myMat*myMat2;
		WorldPoint3 myVec = WorldPoint3(0.0,1.0,0.0);
		WorldPoint3 out = myVec * myMat3;
		s<<out << " == WorldPoint3(0.0,-1.0,0.0)";
		AssertMsg_Test(out == WorldPoint3(0.0,-1.0,0.0), s.str().c_str());
	}
	{
		s.str("");
		myMat.SetRotationX(DegreeToRadian(90.0));
		WorldPoint4 myVec = WorldPoint4(0.0,1.0,0.0);
		WorldPoint4 out = myVec * myMat;
		s<<out << " == WorldPoint4(0.0,0.0,-1.0, 1.0)";
		AssertMsg_Test(out == WorldPoint4(0.0,0.0,-1.0, 1.0), s.str().c_str());
	}
	{
		s.str("");
		myMat.SetRotationX(DegreeToRadian(90.0));
		s<<std::endl<<myMat<<std::endl;
		s<<std::endl<<Matrix44::IDENTITY<<std::endl;
		Matrix44 myMat2 =  Matrix44::IDENTITY*myMat;
		s<<std::endl<<myMat2<<std::endl;
		WorldPoint3 myVec = WorldPoint3(0.0,1.0,0.0);
		s<<std::endl<<myVec<<std::endl;
		WorldPoint3 out = myVec * myMat2;
		s<<out << " == WorldPoint3(0.0,0.0,-1.0)";
		AssertMsg_Test(out == WorldPoint3(0.0,0.0,-1.0), s.str().c_str());
	}

	//rot y test
	{
		myMat.SetRotationY(DegreeToRadian(90.0));
		myMat =  Matrix44::IDENTITY*myMat ;
		WorldPoint3 myVec = WorldPoint3(1.0,0.0,0.0);
		WorldPoint3 out = myVec * myMat;
		s.str("");
		s<<out << " == WorldPoint3(0.0,0.0,1.0)";
		AssertMsg_Test(out == WorldPoint3(0.0,0.0,1.0), s.str().c_str());
	}

	//rot z test
	{
		myMat.SetRotationZ(DegreeToRadian(90.0));
		myMat =  Matrix44::IDENTITY*myMat ;
		WorldPoint3 myVec = WorldPoint3(1.0,0.0,0.0);
		WorldPoint3 out = myVec * myMat;
		s.str("");
		s<<out << " == WorldPoint3(0.0,-1.0,0.0)";
		AssertMsg_Test(out == WorldPoint3(0.0,-1.0,0.0), s.str().c_str());
	}
	//inverse tests
	{
		Matrix44 tempMatrix;
		//asserting that inverse throws an exception when diving by zero
		memset(&tempMatrix, 0, sizeof(Matrix44));

		try
		{
			tempMatrix = Inverse(tempMatrix);
			Assert_Test(false);
		}
		catch (GCLException &e)
		{
		}
	}
	//transpose
	{

		const Real mat[] = {1.0, 2.0, 3.0, 4.0,
				5.0, 6.0, 7.0, 8.0,
				9.0, 10.0, 11.0, 12.0,
				13.0, 14.0, 15.0, 16.0};
		myMat.Set(Matrix44(mat));
		myMat.Transpose();
		const Real tmat[] = {1.0, 5.0, 9.0, 13.0,
				2.0, 6.0, 10.0, 14.0,
				3.0, 7.0, 11.0, 15.0,
				4.0, 8.0, 12.0, 16.0};

		Matrix44 myMat2(tmat);
		s<<std::endl<<myMat<<std::endl<<"=="<<std::endl<<myMat2;
		AssertMsg_Test(myMat==myMat2, s.str().c_str());

	}
	//transpose inverse
	{
		s.str("");
		myMat.SetRotationX(DegreeToRadian(90.0));
		s<<Determinant(myMat)<<"==1.0";
		AssertMsg_Test(abseq(Determinant(myMat),1.0, DBL_PRECISION_TOLERANCE), s.str().c_str());
		Assert_Test(myMat.IsOrthoNormal());

		s.str("");
		s<<std::endl<<myMat;
		myMat.Transpose();
		s<<std::endl<<myMat;
		Matrix44 myMat2;
		myMat2.SetRotationX(DegreeToRadian(90.0));
		Matrix44 res;
		res = myMat2*myMat;

		s<<std::endl<<res<<std::endl<<"=="<<std::endl<<Matrix44::IDENTITY;
		AssertMsg_Test(res==Matrix44::IDENTITY, s.str().c_str());


	}
	{

		s.str("");
		//proper inverse
		myMat = Matrix44::IDENTITY;
		Matrix44 myMatInv = Inverse(myMat);
		s << std::endl << myMatInv << std::endl << "==" << std::endl << Matrix44::IDENTITY;
		AssertMsg_Test(myMatInv==Matrix44::IDENTITY, s.str().c_str());
	}
	{

		s.str("");
		//proper inverse
		myMat.SetRotationX(DegreeToRadian(90.0));
		Matrix44 myMatInv = Inverse(myMat);
		s <<std::endl<< myMat<<std::endl;
		s << myMatInv<<std::endl;
		//		AssertMsg_Test(myMatInv== m
		Matrix44 myMat2;
		myMat2.SetRotationX(DegreeToRadian(90.0));
		Matrix44 myMat3;
		myMat3 = myMatInv*myMat2;


		s << std::endl << myMat3 << std::endl << "==" << std::endl << Matrix44::IDENTITY;
		AssertMsg_Test(myMat3==Matrix44::IDENTITY, s.str().c_str());
	}
	{
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

	}
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

	//[] operator test
	{
		Matrix44 indexOpTest;
		indexOpTest[0] = WorldPoint4(1.810660174077882, 2.0, 3.0, 4.0);

		WorldPoint4 indexOpTestPoint = indexOpTest[0];

		s.str("");
		s<<std::endl<<indexOpTestPoint<<std::endl<<"=="<<std::endl<<WorldPoint4(1.810660174077882, 2.0, 3.0, 4.0);
		AssertMsg_Test(indexOpTestPoint==WorldPoint4(1.810660174077882, 2.0, 3.0, 4.0), s.str().c_str());
	}

}

}
