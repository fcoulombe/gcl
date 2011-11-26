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
#include <iostream>
#include "gcl/Macro.h"
#include "gcl/Point2.h"

//============================================================================

namespace GCL
{
//============================================================================

	template<typename T> class Point3
	{

	public:
		T		x;
		T		y;
		T		z;

		GCLINLINE Point3() throw()												{ }
		GCLINLINE Point3(const T& aX, const T& aY, const T& aZ) throw() : x(aX), y(aY), z(aZ)	{ }
		GCLINLINE Point3(const T a[3]) throw() : x(a[0]),y(a[1]), z(a[2]) 			{ }
		template<typename A>
			GCLINLINE explicit Point3(const Point3<A>& a) : x(a.x), y(a.x), z(a.z)	{ }

		GCLINLINE void Set(const T& aX, const T& aY, const T& aZ) throw()			{ this->x = aX; this->y = aY; this->z = aZ; }
		GCLINLINE void Set(const T a[3])				throw()						{ this->x = a[0]; this->y = a[1]; this->z = a[2]; }

		GCLINLINE Point3 operator+() const throw()					{ return *this;					}
		GCLINLINE Point3 operator-() const throw()					{ return Point3(-this->x, -this->y, -this->z);	}

		GCLINLINE Point3 operator+(const Point3& a) const throw()		{ return Point3(this->x+a.x, this->y+a.y, this->z+a.z);	}
		GCLINLINE Point3 operator-(const Point3& a) const throw()		{ return Point3(this->x-a.x, this->y-a.y, this->z-a.z);	}
		GCLINLINE Point3 operator*(const Point3& a) const throw()		{ return Point3(this->x*a.x, this->y*a.y, this->z*a.z);	}
		GCLINLINE Point3 operator*(const T& a)	  const throw()		{ return Point3(this->x*a,   this->y*a,   this->z*a  );	}
		GCLINLINE Point3 operator/(const Point3& a) const throw()		{ return Point3(this->x/a.x, this->y/a.y, this->z/a.z);	}
		GCLINLINE Point3 operator/(const T& a)	  const throw()		{ return Point3(this->x/a,   this->y/a,   this->z/a  );	}
		GCLINLINE Point3 operator<<(unsigned a)	  const throw()		{ return Point3(this->x<<a,  this->y<<a,  this->z<<a );	}
		GCLINLINE Point3 operator>>(unsigned a)	  const throw()		{ return Point3(this->x>>a,  this->y>>a,  this->z>>a );	}

		GCLINLINE friend Point3 operator*(const T& a, const Point3& b) throw() { return Point3(a*b.x, a*b.y, a*b.z); }

		GCLINLINE Point3& operator+=(const Point3& a) throw()			{ this->x += a.x; this->y += a.y; this->z += a.z; return *this;	}
		GCLINLINE Point3& operator-=(const Point3& a) throw()			{ this->x -= a.x; this->y -= a.y; this->z -= a.z; return *this;	}
		GCLINLINE Point3& operator*=(const Point3& a) throw()			{ this->x *= a.x; this->y *= a.y; this->z *= a.z; return *this;	}
		GCLINLINE Point3& operator*=(const T& a)		throw()			{ this->x *= a;   this->y *= a;	  this->z *= a;   return *this;	}
		GCLINLINE Point3& operator/=(const Point3& a) throw()			{ this->x /= a.x; this->y /= a.y; this->z /= a.z; return *this;	}
		GCLINLINE Point3& operator/=(const T& a)	    throw()			{ this->x /= a;   this->y /= a;	  this->z /= a;   return *this;	}
		GCLINLINE Point3& operator<<=(unsigned a)		throw()			{ this->x <<= a;  this->y <<= a;  this->z <<= a;  return *this;	}
		GCLINLINE Point3& operator>>=(unsigned a)		throw()			{ this->x >>= a;  this->y >>= a;  this->z >>= a;  return *this;	}

		// Dot Product
		GCLINLINE typename TypeData<T>::MathematicalUpcast operator%(const Point3& a) const { return this->x*a.x + this->y*a.y + this->z*a.z; }

		
		// Cross Product
		GCLINLINE Point3 operator^(const Point3& a) throw()			{ return Point3(this->y*a.z - this->z*a.y, this->z*a.x-this->x*a.z, this->x*a.y-this->y*a.x); }
		GCLINLINE Point3& operator^=(const Point3& a) throw()			{ *this = *this ^ a; return *this; }


		GCLINLINE	    T& operator[](int i)		 throw()			{ return (&x)[i]; }
		GCLINLINE const T& operator[](int i) const throw()			{ return (&x)[i]; }

		GCLINLINE bool operator==(const Point3& a) const throw();
		GCLINLINE bool operator!=(const Point3& a) const throw();
		GCLINLINE bool operator< (const Point3& a) const throw()		{ return this->x <  a.x && this->y <  a.y && this->z <  a.z; }
		GCLINLINE bool operator<=(const Point3& a) const throw()		{ return this->x <= a.x && this->y <= a.y && this->z <= a.z; }
		GCLINLINE bool operator> (const Point3& a) const throw()		{ return this->x >  a.x && this->y >  a.y && this->z >  a.z; }
		GCLINLINE bool operator>=(const Point3& a) const throw()		{ return this->x >= a.x && this->y >= a.y && this->z >= a.z; }

		GCLINLINE friend Point3 Abs(const Point3& a) throw()			{ return Point3(Abs(a.x), Abs(a.y), Abs(a.z)); }
		
		/*friend GCLINLINE std::istream& operator>>( std::istream&, Point3&);
		friend GCLINLINE std::ostream& operator<<( std::ostream&, const Point3 &);*/


		GCLINLINE double Length() const{  return sqrt(this->x*this->x + this->y*this->y + this->z*this->z); }
		GCLINLINE double LengthSqr() const{  return (this->x*this->x + this->y*this->y + this->z*this->z);	}

		GCLINLINE void Normalize()
		{
			double ln = Length();
			if (ln == 0) return;                    // do nothing for nothing
			this->x /= ln;
			this->y /= ln;
			this->z /= ln;
		}

		static const Point3 ZERO;
		static const Point3 X_AXIS;
		static const Point3 Y_AXIS;
		static const Point3 Z_AXIS;
	};

	template<typename T>
	GCLINLINE static typename TypeData<T>::MathematicalUpcast Length(const Point3<T>& a) throw()				{ return sqrt(a%a); }
	template<typename T>
	GCLINLINE static typename TypeData<T>::MathematicalUpcast LengthSquared(const Point3<T>& a) throw()		{ return a%a; }

	template<typename T>
	GCLINLINE static Point3<T> Normalize(const Point3<T>& a) throw()	{ return a / Length(a); }

	// Read input Vector3 format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
	GCLINLINE std::istream& operator>>( std::istream& input, Point3<double>& P) {
		char c;
		input >> c;                // skip '('
		input >> P.x;
		input >> c;
		input >> P.y;
		input >> c;
		input >> P.z;
		input >> c;                // skip ')'
		return input;
	}

	// Write output Vector3 in format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
	GCLINLINE std::ostream& operator<<( std::ostream& output, const Point3<double> &P) {
		output << "(" << P.x << ", " << P.y << ", " << P.z << ")";
		return output;
	}

	template<typename T> const Point3<T> Point3<T>::ZERO( TypeData<T>::Zero(), TypeData<T>::Zero(), TypeData<T>::Zero());
	template<typename T> const Point3<T> Point3<T>::X_AXIS( TypeData<T>::Identity(), TypeData<T>::Zero(), TypeData<T>::Zero());
	template<typename T> const Point3<T> Point3<T>::Y_AXIS( TypeData<T>::Zero(), TypeData<T>::Identity(), TypeData<T>::Zero());
	template<typename T> const Point3<T> Point3<T>::Z_AXIS( TypeData<T>::Zero(), TypeData<T>::Zero(), TypeData<T>::Identity());
	
//============================================================================

	template<typename T> class TypeData< Point3<T> >
	{
	public:
		static const Point3<T>& Minimum()	{ return MINIMUM;	}
		static const Point3<T>& Maximum()	{ return MAXIMUM;	}
		static const Point3<T>& Zero()		{ return Point3<T>::ZERO;		}
		static const Point3<T>& Identity()	{ return IDENTITY;	}

		static const Point3<T>& XAxis()		{ return Point3<T>::X_AXIS;	}
		static const Point3<T>& YAxis()		{ return Point3<T>::Y_AXIS;	}
		static const Point3<T>& ZAxis()		{ return Point3<T>::Z_AXIS;	}
		
		enum { IS_INTEGRAL			= TypeData<T>::IS_INTEGRAL			};
		enum { IS_FLOAT				= TypeData<T>::IS_FLOAT				};
		enum { IS_POD				= TypeData<T>::IS_POD				};
		enum { IS_BITWISE_COPY_SAFE	= TypeData<T>::IS_BITWISE_COPY_SAFE };
		enum { IS_POINTER			= TypeData<T>::IS_POINTER			};
		
		typedef Point3<T> MathematicalUpcast;
		typedef const Point3<T>& ParameterType;

	private:
		static const Point3<T> MINIMUM;
		static const Point3<T> MAXIMUM;
		static const Point3<T> IDENTITY;
	};

	template<typename T> const Point3<T> TypeData< Point3<T> >::MINIMUM( TypeData<T>::Minimum(), TypeData<T>::Minimum(), TypeData<T>::Minimum()); 
	template<typename T> const Point3<T> TypeData< Point3<T> >::MAXIMUM( TypeData<T>::Maximum(), TypeData<T>::Maximum(), TypeData<T>::Maximum()); 
	template<typename T> const Point3<T> TypeData< Point3<T> >::IDENTITY( TypeData<T>::Identity(), TypeData<T>::Identity(), TypeData<T>::Identity());

//============================================================================
	
	template<> GCLINLINE Point3<float> Point3<float>::operator/(const float& a) const throw()
	{
		return *this * (1.0f / a);
	}

	template<> GCLINLINE Point3<float>& Point3<float>::operator/=(const float& a) throw()
	{
		return *this *= (1.0f / a);
	}
	
	template<> GCLINLINE bool Point3<double>::operator==(const Point3& a) const throw()		{ return abseq(this->x, a.x, DBL_PRECISION_TOLERANCE) && abseq(this->y, a.y, DBL_PRECISION_TOLERANCE) && abseq(this->z, a.z, DBL_PRECISION_TOLERANCE); }
	template<> GCLINLINE bool Point3<double>::operator!=(const Point3& a) const throw()		{ return !abseq(this->x, a.x, DBL_PRECISION_TOLERANCE) || !abseq(this->y, a.y, DBL_PRECISION_TOLERANCE) || !abseq(this->z, a.z, DBL_PRECISION_TOLERANCE); }


//============================================================================

	typedef Point3<WorldUnit> WorldPoint3;
	
//============================================================================
}
//============================================================================
