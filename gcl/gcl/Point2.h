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
#include "gcl/TypeData.h"
#include "gcl/WorldUnit.h"

//============================================================================

namespace GCL
{
//============================================================================

	template<typename T> class Point2
	{
	public:
		T		x;
		T		y;

		GCLINLINE Point2() throw()												{ }
		GCLINLINE Point2(const T& aX, const T& aY) throw() : x(aX), y(aY)			{ }
		GCLINLINE Point2(const T a[2]) throw() : x(a[0]), y(a[1])					{ }
		template<typename A>
			GCLINLINE explicit Point2(const Point2<A>& a) : x(a.x), y(a.y)		{ }

		GCLINLINE void Set(const T& aX, const T& aY) throw()			{ x = aX; y = aY; }
		GCLINLINE void Set(const T a[2])				throw()			{ x = a[0]; y = a[1]; }

		GCLINLINE Point2 operator+() const throw()					{ return *this;				}
		GCLINLINE Point2 operator-() const throw()					{ return Point2(-x, -y);	}

		GCLINLINE Point2 operator+(const Point2& a) const throw()		{ return Point2(x+a.x, y+a.y);	}
		GCLINLINE Point2 operator-(const Point2& a) const throw()		{ return Point2(x-a.x, y-a.y);	}
		GCLINLINE Point2 operator*(const Point2& a) const throw()		{ return Point2(x*a.x, y*a.y);	}
		GCLINLINE Point2 operator*(const T& a)	  const throw()		{ return Point2(x*a,   y*a);	}
		GCLINLINE Point2 operator/(const Point2& a) const throw()		{ return Point2(x/a.x, y/a.y);	}
		GCLINLINE Point2 operator/(const T& a)	  const throw()		{ return Point2(x/a,   y/a);	}
		GCLINLINE Point2 operator<<(unsigned a)	  const throw()		{ return Point2(x<<a, y<<a); }
		GCLINLINE Point2 operator>>(unsigned a)	  const throw()		{ return Point2(x>>a, y>>a); }

		GCLINLINE friend Point2 operator*(const T& a, const Point2& b) throw() { return Point2(a*b.x, a*b.y); }

		GCLINLINE Point2& operator+=(const Point2& a) throw()			{ x += a.x; y += a.y; return *this;	}
		GCLINLINE Point2& operator-=(const Point2& a) throw()			{ x -= a.x; y -= a.y; return *this;	}
		GCLINLINE Point2& operator*=(const Point2& a) throw()			{ x *= a.x; y *= a.y; return *this;	}
		GCLINLINE Point2& operator*=(const T& a)		throw()			{ x *= a;   y *= a;	  return *this;	}
		GCLINLINE Point2& operator/=(const Point2& a) throw()			{ x /= a.x; y /= a.y; return *this;	}
		GCLINLINE Point2& operator/=(const T& a)	    throw()			{ x /= a;   y /= a;	  return *this;	}
		GCLINLINE Point2& operator<<=(unsigned a)		throw()			{ x <<= a;  y <<= a;  return *this;	}
		GCLINLINE Point2& operator>>=(unsigned a)		throw()			{ x >>= a;  y >>= a;  return *this;	}

		// Dot Product
		GCLINLINE typename TypeData<T>::MathematicalUpcast operator%(const Point2& a) const { return x*a.x + y*a.y; }
		
		GCLINLINE friend typename TypeData<T>::MathematicalUpcast Length(const Point2& a) throw()				{ return sqrt(a%a); }
		GCLINLINE friend typename TypeData<T>::MathematicalUpcast LengthSquared(const Point2& a) throw()		{ return a%a; }
		GCLINLINE Real Length() const{  return sqrt(this->x*this->x + this->y*this->y ); }
		GCLINLINE Real LengthSqr() const{  return (this->x*this->x + this->y*this->y );	}

		//GCLINLINE friend Point2 Normalize(const Point2& a) throw()	{ return a / Length(a); }

		GCLINLINE void Normalize()
		{
			Real ln = Length();
			*this/= ln; //can throw float div zero
		}

		
		GCLINLINE	      T& operator[](int i)		 throw()			{ return (&x)[i]; }
		GCLINLINE const T& operator[](int i) const throw()			{ return (&x)[i]; }

		GCLINLINE bool operator==(const Point2& a) const throw()
				{ return this->x == a.x &&  this->y==a.y; }
		GCLINLINE bool operator!=(const Point2& a) const throw()
		{ return this->x != a.x || this->y != a.y; }
		GCLINLINE bool operator< (const Point2& a) const throw()		{ return x <  a.x && y <  a.y; }
		GCLINLINE bool operator<=(const Point2& a) const throw()		{ return x <= a.x && y <= a.y; }
		GCLINLINE bool operator> (const Point2& a) const throw()		{ return x >  a.x && y >  a.y; }
		GCLINLINE bool operator>=(const Point2& a) const throw()		{ return x >= a.x && y >= a.y; }

		GCLINLINE friend Point2 Abs(const Point2& a) throw()			{ return Point2(Abs(a.x), Abs(a.y)); }

        template<typename A>
        GCLINLINE Point2 &operator=(const Point2<A> &a) throw()
        {
            this->x = (T)a.x;
            this->y = (T)a.y;
            return *this;
        }

		static const Point2<T> ZERO;
		static const Point2<T> X_AXIS;
		static const Point2<T> Y_AXIS;
	};
	template<>
    GCLINLINE bool Point2<Real>::operator==(const Point2<Real>& a) const throw()
    { return abseq(this->x, a.x, DBL_PRECISION_TOLERANCE) && abseq(this->y, a.y, DBL_PRECISION_TOLERANCE) ; }
	template<>
	GCLINLINE bool Point2<Real>::operator!=(const Point2<Real>& a) const throw()
    { return !abseq(this->x, a.x, DBL_PRECISION_TOLERANCE) || !abseq(this->y, a.y, DBL_PRECISION_TOLERANCE) ; }

	template<typename T> const Point2<T> Point2<T>::ZERO( TypeData<T>::Zero(), TypeData<T>::Zero());
	template<typename T> const Point2<T> Point2<T>::X_AXIS( TypeData<T>::Identity(), TypeData<T>::Zero());
	template<typename T> const Point2<T> Point2<T>::Y_AXIS( TypeData<T>::Zero(), TypeData<T>::Identity());
	
//============================================================================

	template<typename T> class TypeData< Point2<T> >
	{
	public:
		static const Point2<T>& Minimum()	{ return MINIMUM;			}
		static const Point2<T>& Maximum()	{ return MAXIMUM;			}
		static const Point2<T>& Zero()		{ return Point2<T>::ZERO;	}
		static const Point2<T>& Identity()	{ return IDENTITY;			}

		static const Point2<T>& XAxis()		{ return Point2<T>::X_AXIS;	}
		static const Point2<T>& YAxis()		{ return Point2<T>::Y_AXIS;	}
		
		enum { IS_INTEGRAL			= TypeData<T>::IS_INTEGRAL			};
		enum { IS_FLOAT				= TypeData<T>::IS_FLOAT				};
		enum { IS_POD				= TypeData<T>::IS_POD				};
		enum { IS_BITWISE_COPY_SAFE	= TypeData<T>::IS_BITWISE_COPY_SAFE };
		enum { IS_POINTER			= TypeData<T>::IS_POINTER			};
		
		typedef Point2<T> MathematicalUpcast;
		typedef const Point2<T>& ParameterType;
		
	private:
		static const Point2<T> MINIMUM;
		static const Point2<T> MAXIMUM;
		static const Point2<T> IDENTITY;
	};

	template<typename T> const Point2<T> TypeData< Point2<T> >::MINIMUM( TypeData<T>::Minimum(), TypeData<T>::Minimum()); 
	template<typename T> const Point2<T> TypeData< Point2<T> >::MAXIMUM( TypeData<T>::Maximum(), TypeData<T>::Maximum()); 
	template<typename T> const Point2<T> TypeData< Point2<T> >::IDENTITY( TypeData<T>::Identity(), TypeData<T>::Identity());
		
	// Write output Vector3 in format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
	template<typename T>
	GCLINLINE std::ostream& operator<<( std::ostream& output, const Point2<T> &P)
	{
		output << "(" << P.x << ", " << P.y  << ")";
		return output;
	}

//============================================================================
	
	typedef Point2<Real> WorldPoint2;
	
//============================================================================
}
//============================================================================
