/*
 * Copyright (C) 2011 by Jeffrey Lim
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
//============================================================================

#pragma once
#include <cstring>

#include "gcl/Math.h"
#include "gcl/Point4.h"
#include "gcl/WorldUnit.h"

//============================================================================

namespace GCL
{
//============================================================================

class Matrix43;

//============================================================================

class Matrix44
{
public:
	explicit Matrix44() { }
	Matrix44(const Matrix44 &m)
	{
		m0 = m[0];
		m1 = m[1];
		m2 = m[2];
		m3 = m[3];
	}
	explicit Matrix44(const WorldPoint4& a0, const WorldPoint4& a1, const WorldPoint4& a2, const WorldPoint4& a3)
	//: m0(a0), m1(a1), m2(a2), m3(a3) { }
	{
		m0 = a0;
		m1 = a1;
		m2 = a2;
		m3 = a3;
	}

	template<typename T>
	explicit Matrix44(const T a[16])  : m0(a), m1(a+4), m2(a+8), m3(a+12) { }



	GCLINLINE explicit Matrix44(bool isIdentity)
	{
		if (isIdentity)
		{
			m0 = WorldPoint4(1.0, 0.0, 0.0, 0.0);
			m1 = WorldPoint4(0.0, 1.0, 0.0, 0.0);
			m2 = WorldPoint4(0.0, 0.0, 1.0, 0.0);
			m3 = WorldPoint4(0.0, 0.0, 0.0, 1.0);
		}
	}

	GCLINLINE void Set(const Matrix44& a)
	{
		m0 = a[0];
		m1 = a[1];
		m2 = a[2];
		m3 = a[3];
	}

	void SetIdentity()
	{
		m0 = WorldPoint4(1.0, 0.0, 0.0, 0.0);
		m1 = WorldPoint4(0.0, 1.0, 0.0, 0.0);
		m2 = WorldPoint4(0.0, 0.0, 1.0, 0.0);
		m3 = WorldPoint4(0.0, 0.0, 0.0, 1.0);
	}

	void SetRotationX(Real rotation);
	void SetRotationY(Real rotation);
	void SetRotationZ(Real rotation);

	const WorldPoint4 &GetPosition() const { return m3; }
    void SetPosition(Real x, Real y, Real z) { m3 = WorldPoint4(x,y,z,1.0); }
	void SetPosition(const WorldPoint3 &position) { m3 = position; }

	void SetPosition(const WorldPoint4 &position) { m3 = position; }
    
	GCLINLINE const Matrix44& operator+() const 		{ return *this;		}
	GCLEXPORT Matrix44  operator-() const ;

	GCLEXPORT Matrix44  operator+(const Matrix44& a) const ;
	GCLEXPORT Matrix44  operator-(const Matrix44& a) const ;

	GCLEXPORT Matrix44&  operator+=(const Matrix44& a) ;
	GCLEXPORT Matrix44&  operator-=(const Matrix44& a) ;

	GCLEXPORT Matrix44  operator*(const Matrix44& a) const ;

	GCLEXPORT friend Matrix44  operator*(const Real a, const Matrix44& b) ;
	GCLEXPORT friend WorldPoint3  operator*(const WorldPoint3& a, const Matrix44& b);
	GCLEXPORT friend WorldPoint4  operator*(const WorldPoint4& a, const Matrix44& b);
	GCLEXPORT friend Real  Determinant(const Matrix44& m) ;
	GCLEXPORT friend Matrix44  Inverse(const Matrix44& m) ;

	GCLINLINE		  WorldPoint4& operator[](size_t i)				{ return (&m0)[i]; }
	GCLINLINE const WorldPoint4& operator[](size_t i) const		{ return (&m0)[i]; }

	GCLINLINE bool operator==(const Matrix44& a) const 	{ return m0==a.m0 && m1==a.m1 && m2==a.m2 && m3==a.m3 ; }
	GCLINLINE bool operator!=(const Matrix44& a) const { return m0!=a.m0 || m1!=a.m1 || m2!=a.m2 || m3!=a.m3 ; }

	GCLINLINE bool IsOrthoNormal() const { Real det = Determinant(*this); return det>=1.0 || det<=-1.0; }
	GCLEXPORT static const Matrix44 ZERO;
	GCLEXPORT static const Matrix44 IDENTITY;

	GCLINLINE void SetPerspective(Real fov, Real aspect, Real znear, Real zfar)
	{
		/* Restrict fov to 179 degrees, for numerical stability */
		if(fov >= 180.0)
			fov = 179.0;

		Real y = 1.0 / std::tan(DegreeToRadian(fov) * 0.5);
		Real x = y/aspect;
		Real z1 = (zfar+znear)/(znear-zfar);
		Real z2 = (2.0f*zfar*znear)/(znear-zfar);
		m0=WorldPoint4(x, 0.0,  0.0,  0.0);
		m1=WorldPoint4(0.0, y,  0.0,  0.0);
		m2=WorldPoint4(0.0, 0, z1, -1);
		m3=WorldPoint4(0.0, 0.0,  z2,  0.0);
	}

    GCLINLINE void SetOrtho( Real left, Real right, Real bottom, Real top, Real zNear, Real zFar)
    {
        m0 = WorldPoint4(2.0/(right-left), 0.0,0.0,0.0);
        m1 = WorldPoint4(0.0, 2.0/(top-bottom), 0.0, 0.0);
        m2 = WorldPoint4(0.0,0.0, -2.0/(zFar-zNear), 0.0);
        m3 = WorldPoint4(-((right+left)/(right-left)), 
            -((top+bottom)/(top-bottom)),
            -((zFar+zNear)/(zFar-zNear)), 
            1.0);                
    }

	GCLINLINE WorldPoint4 Project(const WorldPoint4& v, Real width, Real height)
	{
		WorldPoint4 proj;
		Real centerX = width*0.5f;
		Real centerY = height*0.5f;

		proj.x = v.x*centerX  + centerX;
		proj.y = v.y*centerY + centerY;
		proj.z = v.z*0.5f + 0.5f;
		proj.w = 1.0f / v.w;

		return proj;
	}
	GCLINLINE void Transpose()
	{
		WorldPoint4 temp;
		temp.y = m0.y;
		temp.z = m0.z;
		temp.w = m0.w;
		m0.y = m1.x;
		m0.z = m2.x;
		m0.w = m3.x;

		m1.x = temp.y;
		m2.x = temp.z;
		m3.x = temp.w;

		temp.x = m1.z;
		temp.y = m1.w;
		temp.z = m2.w;
		m1.z = m2.y;
		m1.w = m3.y;
		m2.w = m3.z;
		m2.y = temp.x;
		m3.y = temp.y;
		m3.z = temp.z;

	}
protected:
	WorldPoint4		m0;
	WorldPoint4		m1;
	WorldPoint4		m2;
	WorldPoint4		m3;
};

// Write output Vector3 in format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
GCLINLINE std::ostream& operator<<( std::ostream& output, const Matrix44 &P)
{
	output << "(" << P[0].x << ", " << P[0].y << ", " << P[0].z << ", " << P[0].w << ")" << std::endl;
	output << "(" << P[1].x << ", " << P[1].y << ", " << P[1].z << ", " << P[1].w << ")" << std::endl;
	output << "(" << P[2].x << ", " << P[2].y << ", " << P[2].z << ", " << P[2].w << ")" << std::endl;
	output << "(" << P[3].x << ", " << P[3].y << ", " << P[3].z << ", " << P[3].w << ")" << std::endl;
	return output;
}

//============================================================================

template<> class TypeData< Matrix44 >
{
public:
	static const Matrix44& Zero()		{ return Matrix44::ZERO;			}
	static const Matrix44& Identity()	{ return Matrix44::IDENTITY;		}

	enum { IS_INTEGRAL			= TypeData<Real>::IS_INTEGRAL			};
	enum { IS_FLOAT				= TypeData<Real>::IS_FLOAT				};
	enum { IS_POD				= TypeData<Real>::IS_POD				};
	enum { IS_BITWISE_COPY_SAFE	= TypeData<Real>::IS_BITWISE_COPY_SAFE };
	enum { IS_POINTER			= TypeData<Real>::IS_POINTER			};
};

//============================================================================
class Matrix44f
{
public:
	Matrix44f(){}
	Matrix44f(const Matrix44 &m)
	{
		m0.x = float(m[0].x);
		m0.y = float(m[0].y);
		m0.z = float(m[0].z);
		m0.w = float(m[0].w);

		m1.x = float(m[1].x);
		m1.y = float(m[1].y);
		m1.z = float(m[1].z);
		m1.w = float(m[1].w);

		m2.x = float(m[2].x);
		m2.y = float(m[2].y);
		m2.z = float(m[2].z);
		m2.w = float(m[2].w);

		m3.x = float(m[3].x);
		m3.y = float(m[3].y);
		m3.z = float(m[3].z);
		m3.w = float(m[3].w);
	}
	Point4<float> m0;
	Point4<float> m1;
	Point4<float> m2;
	Point4<float> m3;
};
}
//============================================================================
