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
#include "Point3.h"
#include "WorldUnit.h"

//============================================================================

namespace GCL
{
//============================================================================

	class Quaternion : public Point3<WorldUnit>
	{
	protected:
		typedef WorldUnit T;
		typedef Point3<WorldUnit> Inherited;

	public:
		T		w;

		GCLINLINE Quaternion() throw()												{ }
		GCLINLINE Quaternion(const T& aW, const T& aX, const T& aY, const T& aZ) throw() : Inherited(aX, aY, aZ), w(aW)	{ }
		GCLINLINE Quaternion(const T a[4]) throw() : Inherited(a+1), w(a[0]) 			{ }

		GCLINLINE void Set(const T& aW, const T& aX, const T& aY, const T& aZ) throw()	{ this->x = aX; this->y = aY; this->z = aZ; this->w = aW; }
		GCLINLINE void Set(const T a[4])				throw()								{ this->x = a[1]; this->y = a[2]; this->z = a[3]; this->w = a[0]; }

		GCLINLINE Quaternion operator+() const throw()						{ return *this;					}
		GCLINLINE Quaternion operator-() const throw()						{ return Quaternion(-this->w, -this->x, -this->y, -this->z);	}

		GCLINLINE Quaternion operator+(const Quaternion& a) const throw()		{ return Quaternion(this->w+a.w, this->x+a.x, this->y+a.y, this->z+a.z);	}
		GCLINLINE Quaternion operator-(const Quaternion& a) const throw()		{ return Quaternion(this->w-a.w, this->x-a.x, this->y-a.y, this->z-a.z);	}
		GCLINLINE Quaternion operator*(const Quaternion& a) const throw();

		GCLINLINE friend Quaternion operator*(const T& a, const Quaternion& b) throw() { return Quaternion(a*b.w, a*b.x, a*b.y, a*b.z); }

		GCLINLINE Quaternion& operator+=(const Quaternion& a) throw()			{ this->w += a.w; this->y += a.x; this->z += a.y; this->w += a.z; return *this;	}
		GCLINLINE Quaternion& operator-=(const Quaternion& a) throw()			{ this->w -= a.w; this->y -= a.x; this->z -= a.y; this->w -= a.z; return *this;	}
		GCLINLINE Quaternion& operator*=(const T& a)		    throw()			{ this->x *= a;   this->y *= a;	  this->z *= a;   this->w *= a;   return *this;	}

		// Dot Product
		GCLINLINE TypeData<T>::MathematicalUpcast operator%(const Quaternion& a) const { return this->x*a.x + this->y*a.y + this->z*a.z + this->w*a.w; }

		GCLINLINE friend Quaternion Conjugate(const Quaternion& a) throw()		{ return Quaternion(a.w, -a.x, -a.y, -a.z); }
		
		// Array access (operator[]) inherited from Point2/Point3

		GCLINLINE bool operator==(const Quaternion& a) const throw()			{ return this->x == a.x && this->y == a.y && this->z == a.z && this->w == a.w; }
		GCLINLINE bool operator!=(const Quaternion& a) const throw()			{ return this->x != a.x || this->y != a.y || this->z != a.z || this->w != a.w; }

		static const Quaternion IDENTITY;
	};
	
//============================================================================

	template<> class TypeData< Quaternion >
	{
	private:
		typedef WorldUnit T;
			
	public:
		static const Quaternion& Identity()	{ return Quaternion::IDENTITY;	}
		
		enum { IS_INTEGRAL			= TypeData<T>::IS_INTEGRAL			};
		enum { IS_FLOAT				= TypeData<T>::IS_FLOAT				};
		enum { IS_POD				= TypeData<T>::IS_POD				};
		enum { IS_BITWISE_COPY_SAFE	= TypeData<T>::IS_BITWISE_COPY_SAFE };
		enum { IS_POINTER			= TypeData<T>::IS_POINTER			};
	};

//============================================================================
}
//============================================================================
