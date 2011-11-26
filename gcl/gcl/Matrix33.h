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
#include "Point3.h"
#include "WorldUnit.h"

//============================================================================

namespace GCL
{
//============================================================================

	class Matrix33
	{
	public:
		Matrix33() 														{ }
		Matrix33(const WorldPoint3& a0, const WorldPoint3& a1, const WorldPoint3& a2) throw() : m0(a0), m1(a1), m2(a2) { }
		Matrix33(const WorldUnit a[9]) throw() : m0(a), m1(a+3), m2(a+6) { }

		GCLINLINE explicit Matrix33(bool b) : m0(b ? TypeData<WorldUnit>::Identity() : TypeData<WorldUnit>::Zero(), TypeData<WorldUnit>::Zero(), TypeData<WorldUnit>::Zero()),
											m1(TypeData<WorldUnit>::Zero(), b ? TypeData<WorldUnit>::Identity() : TypeData<WorldUnit>::Zero(), TypeData<WorldUnit>::Zero()),
											m2(TypeData<WorldUnit>::Zero(), TypeData<WorldUnit>::Zero(), b ? TypeData<WorldUnit>::Identity() : TypeData<WorldUnit>::Zero()) { }
	
		GCLINLINE const Matrix33& operator+() const throw()			{ return *this;		}
		GCLEXPORT Matrix33  operator-() const throw();

		GCLEXPORT Matrix33  operator+(const Matrix33& a) const throw();
		GCLEXPORT Matrix33  operator-(const Matrix33& a) const throw();

		GCLEXPORT Matrix33&  operator+=(const Matrix33& a) throw();
		GCLEXPORT Matrix33&  operator-=(const Matrix33& a) throw();
	
		GCLEXPORT Matrix33  operator*(const Matrix33& a) const throw();
		
		GCLEXPORT friend Matrix33  operator*(const WorldUnit a, const Matrix33& b) throw();
		GCLEXPORT friend WorldPoint3  operator*(const WorldPoint3& a, const Matrix33& b) throw();
		GCLEXPORT friend WorldUnit  Determinant(const Matrix33& m) throw();
		GCLEXPORT friend Matrix33  Inverse(const Matrix33& m) throw();
		
		GCLINLINE WorldPoint3 TransformVector(const WorldPoint3& a) const { return a * (*this); }

		GCLINLINE		  WorldPoint3& operator[](size_t i)				{ return (&m0)[i]; }
		GCLINLINE const WorldPoint3& operator[](size_t i) const		{ return (&m0)[i]; }

		GCLINLINE bool operator==(const Matrix33& a) const throw()	{ return memcmp(this, &a, sizeof(*this)) == 0; }
		GCLINLINE bool operator!=(const Matrix33& a) const throw()	{ return memcmp(this, &a, sizeof(*this)) != 0; }

		GCLEXPORT static const Matrix33 ZERO;
		GCLEXPORT static const Matrix33 IDENTITY;

	protected:
		WorldPoint3		m0;
		WorldPoint3		m1;
		WorldPoint3		m2;		
	};

//============================================================================

	template<> class TypeData< Matrix33 >
	{
	public:
		static const Matrix33& Zero()		{ return Matrix33::ZERO;			}
		static const Matrix33& Identity()	{ return Matrix33::IDENTITY;		}

		enum { IS_INTEGRAL			= TypeData<WorldUnit>::IS_INTEGRAL			};
		enum { IS_FLOAT				= TypeData<WorldUnit>::IS_FLOAT				};
		enum { IS_POD				= TypeData<WorldUnit>::IS_POD				};
		enum { IS_BITWISE_COPY_SAFE	= TypeData<WorldUnit>::IS_BITWISE_COPY_SAFE };
		enum { IS_POINTER			= TypeData<WorldUnit>::IS_POINTER			};
	};

//============================================================================
}
//============================================================================
