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
#include "Matrix33.h"

//============================================================================

namespace GCL
{
//============================================================================

	class Matrix43 : public Matrix33
	{
	private:
		typedef Matrix33 Inherited;

	public:
		Matrix43() throw()														{ }
		Matrix43(const WorldPoint3& a0, const WorldPoint3& a1, const WorldPoint3& a2, const WorldPoint3& a3) throw() : Inherited(a0, a1, a2), m3(a3) { }
		Matrix43(const Real a[12]) throw() : Inherited(a), m3(a+9) { }

		GCLINLINE explicit Matrix43(bool b) : Inherited(b),
											m3(TypeData<Real>::Zero(), TypeData<Real>::Zero(), TypeData<Real>::Zero()) { }
		
		GCLINLINE const Matrix43& operator+() const throw()			{ return *this;		}
		GCLEXPORT Matrix43  operator-() const throw();

		GCLEXPORT Matrix43  operator+(const Matrix43& a) const throw();
		GCLEXPORT Matrix43  operator-(const Matrix43& a) const throw();

		GCLEXPORT Matrix43&  operator+=(const Matrix43& a) throw();
		GCLEXPORT Matrix43&  operator-=(const Matrix43& a) throw();
	
		GCLEXPORT Matrix43  operator*(const Matrix43& a) const throw();
		
		GCLEXPORT friend Matrix43  operator*(const Real a, const Matrix43& b) throw();
		GCLEXPORT friend WorldPoint3  operator*(const WorldPoint3& a, const Matrix43& b) throw();
		GCLEXPORT friend Matrix43  Inverse(const Matrix43& m) throw();

		// Array access from Matrix33

		GCLINLINE bool operator==(const Matrix43& a) const throw()	{ return memcmp(this, &a, sizeof(*this)) == 0; }
		GCLINLINE bool operator!=(const Matrix43& a) const throw()	{ return memcmp(this, &a, sizeof(*this)) != 0; }

		GCLEXPORT static const Matrix43 ZERO;
		GCLEXPORT static const Matrix43 IDENTITY;

	protected:
		WorldPoint3		m3;
	};

//============================================================================

	template<> class TypeData< Matrix43 >
	{
	public:
		static const Matrix43& Zero()		{ return Matrix43::ZERO;			}
		static const Matrix43& Identity()	{ return Matrix43::IDENTITY;		}

		enum { IS_INTEGRAL			= TypeData<Real>::IS_INTEGRAL			};
		enum { IS_FLOAT				= TypeData<Real>::IS_FLOAT				};
		enum { IS_POD				= TypeData<Real>::IS_POD				};
		enum { IS_BITWISE_COPY_SAFE	= TypeData<Real>::IS_BITWISE_COPY_SAFE };
		enum { IS_POINTER			= TypeData<Real>::IS_POINTER			};
	};

//============================================================================
}
//============================================================================
