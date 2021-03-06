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
#include "gcl/Macro.h"
#include "gcl/Point3.h"
#include "gcl/WorldUnit.h"


//============================================================================

namespace GCL
{
//============================================================================

	template<typename T> class Point4
	{

	public:
		T		x;
		T		y;
		T		z;
		T		w;

		GCLINLINE Point4() 												{ }
		template <typename A1,typename A2,typename A3,typename A4>
		GCLINLINE explicit Point4(const A1& aX, const A2& aY, const A3& aZ, const A4& aW)  
        {
            x = (T)(aX);
            y = (T)(aY);
            z = (T)(aZ);
            w = (T)(aW);	
        }
		template <typename A1,typename A2,typename A3>
		GCLINLINE explicit Point4(const A1& aX, const A2& aY, const A3& aZ)  
        { 
            x = (T)(aX);
            y = (T)(aY);
            z = (T)(aZ);
            w = (T)(1.0);	
        }

		template <typename T2>
		GCLINLINE explicit Point4(const T2 a[4])  : x(a[0]),y(a[1]),z(a[2]), w(a[3]) 			{ }
		GCLINLINE Point4(const Point4& a) : x(a.x),y(a.y),z(a.z), w(a.w)	{ }

		GCLINLINE void Set(const T& aX, const T& aY, const T& aZ, const T& aW) 	{ this->x = aX; this->y = aY; this->z = aZ; this->w = aW; }
		GCLINLINE void Set(const T a[4])												{ this->x = a[0]; this->y = a[1]; this->z = a[2]; this->w = a[3]; }

		GCLINLINE Point4 operator+() const 					{ return *this;					}
		GCLINLINE Point4 operator-() const 					{ return Point4(-this->x, -this->y, -this->z, -this->w);	}

		GCLINLINE Point4 operator+(const Point4& a) const 		{ return Point4(this->x+a.x, this->y+a.y, this->z+a.z, this->w+a.w);	}
		GCLINLINE Point4 operator-(const Point4& a) const 		{ return Point4(this->x-a.x, this->y-a.y, this->z-a.z, this->w-a.w);	}
		GCLINLINE Point4 operator*(const Point4& a) const 		{ return Point4(this->x*a.x, this->y*a.y, this->z*a.z, this->w*a.w);	}
		GCLINLINE Point4 operator*(const T& a)	  const 		{ return Point4(this->x*a,   this->y*a,   this->z*a,   this->w*a  );	}
		GCLINLINE Point4 operator/(const Point4& a) const 		{ return Point4(this->x/a.x, this->y/a.y, this->z/a.z, this->w/a.w);	}
		GCLINLINE Point4 operator/(const T& a)	  const 		{ return Point4(this->x/a,   this->y/a,   this->z/a,   this->w/a  );	}
		GCLINLINE Point4 operator<<(unsigned a)	  const 		{ return Point4(this->x<<a,  this->y<<a,  this->z<<a,  this->w<<a );	}
		GCLINLINE Point4 operator>>(unsigned a)	  const 		{ return Point4(this->x>>a,  this->y>>a,  this->z>>a,  this->w>>a );	}

		GCLINLINE friend Point4 operator*(const T& a, const Point4& b)  { return Point4(a*b.x, a*b.y, a*b.z, a*b.w); }

		GCLINLINE Point4& operator+=(const Point4& a) 			{ this->x += a.x; this->y += a.y; this->z += a.z; this->w += a.w; return *this;	}
		GCLINLINE Point4& operator-=(const Point4& a) 			{ this->x -= a.x; this->y -= a.y; this->z -= a.z; this->w -= a.w; return *this;	}
		GCLINLINE Point4& operator*=(const Point4& a) 			{ this->x *= a.x; this->y *= a.y; this->z *= a.z; this->w *= a.w; return *this;	}
		GCLINLINE Point4& operator*=(const T& a)					{ this->x *= a;   this->y *= a;	  this->z *= a;   this->w *= a;   return *this;	}
		GCLINLINE Point4& operator/=(const Point4& a) 			{ this->x /= a.x; this->y /= a.y; this->z /= a.z; this->w /= a.w; return *this;	}
		GCLINLINE Point4& operator/=(const T& a)	    			{ this->x /= a;   this->y /= a;	  this->z /= a;   this->w /= a;   return *this;	}
		GCLINLINE Point4& operator<<=(unsigned a)					{ this->x <<= a;  this->y <<= a;  this->z <<= a;  this->w <<= a;  return *this;	}
		GCLINLINE Point4& operator>>=(unsigned a)					{ this->x >>= a;  this->y >>= a;  this->z >>= a;  this->w >>= a;  return *this;	}

		// Dot Product
		GCLINLINE typename TypeData<T>::MathematicalUpcast operator%(const Point4& a) const { return this->x*a.x + this->y*a.y + this->z*a.z + this->w*a.w; }


		GCLINLINE	    T& operator[](int i)		 			{ return (&x)[i]; }
		GCLINLINE const T& operator[](int i) const 			{ return (&x)[i]; }

		GCLINLINE Point4 &operator=(const Point3<T>& a)
				{
			this->x = a.x;
			this->y = a.y;
			this->z = a.z;
			return *this; }

		GCLINLINE Point4 &operator=(const Point4<T>& a)
						{
					this->x = a.x;
					this->y = a.y;
					this->z = a.z;
					this->w = a.w;
					return *this; }

		GCLINLINE bool operator==(const Point4& a) const
		{
			return (this->x == a.x &&
						this->y == a.y &&
						this->z == a.z &&
						this->w == a.w );
        }
		GCLINLINE bool operator!=(const Point4& a) const
		{ 
            return (this->x!=a.x ||
                this->y != a.y ||
                this->z != a.z ||
                this->w != a.w);
        }
		GCLINLINE bool operator< (const Point4& a) const 		{ return this->x <  a.x && this->y <  a.y && this->z <  a.z && this->w <  a.w; }
		GCLINLINE bool operator<=(const Point4& a) const 		{ return this->x <= a.x && this->y <= a.y && this->z <= a.z && this->w <= a.w; }
		GCLINLINE bool operator> (const Point4& a) const 		{ return this->x >  a.x && this->y >  a.y && this->z >  a.z && this->w >  a.w; }
		GCLINLINE bool operator>=(const Point4& a) const 		{ return this->x >= a.x && this->y >= a.y && this->z >= a.z && this->w >= a.w; }


		GCLINLINE Real Length() const {  return sqrt(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w); }
		GCLINLINE Real LengthSqr() const {  return (this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);	}
		GCLINLINE void Normalize()
		{
			Real ln = Length();
			if (ln == 0) return;                    // do nothing for nothing
			this->x /= ln;
			this->y /= ln;
			this->z /= ln;
			this->w /= ln;
		}


		GCLINLINE friend Point4 Abs(const Point4& a) 			{ return Point4(Abs(a.x), Abs(a.y), Abs(a.z), Abs(a.w)); }
		
		static const Point4 ZERO;
		static const Point4 X_AXIS;
		static const Point4 Y_AXIS;
		static const Point4 Z_AXIS;
		static const Point4 W_AXIS;
	};

	template<>
    GCLINLINE bool Point4<Real>::operator==(const Point4<Real>& a) const
    {
        return (abseq(this->x, a.x, DBL_PRECISION_TOLERANCE) &&
            abseq(this->y, a.y, DBL_PRECISION_TOLERANCE) &&
            abseq(this->z, a.z, DBL_PRECISION_TOLERANCE) &&
            abseq(this->w, a.w, DBL_PRECISION_TOLERANCE));
    }


	template<typename T> const Point4<T> Point4<T>::ZERO( TypeData<T>::Zero(), TypeData<T>::Zero(), TypeData<T>::Zero(), TypeData<T>::Zero());
	template<typename T> const Point4<T> Point4<T>::X_AXIS( TypeData<T>::Identity(), TypeData<T>::Zero(), TypeData<T>::Zero(), TypeData<T>::Zero());
	template<typename T> const Point4<T> Point4<T>::Y_AXIS( TypeData<T>::Zero(), TypeData<T>::Identity(), TypeData<T>::Zero(), TypeData<T>::Zero());
	template<typename T> const Point4<T> Point4<T>::Z_AXIS( TypeData<T>::Zero(), TypeData<T>::Zero(), TypeData<T>::Identity(), TypeData<T>::Zero());
	template<typename T> const Point4<T> Point4<T>::W_AXIS( TypeData<T>::Zero(), TypeData<T>::Zero(), TypeData<T>::Zero(), TypeData<T>::Identity());
	
//============================================================================

	template<typename T> class TypeData< Point4<T> >
	{
	public:
		static const Point4<T>& Minimum()	{ return MINIMUM;	}
		static const Point4<T>& Maximum()	{ return MAXIMUM;	}
		static const Point4<T>& Zero()		{ return Point4<T>::ZERO;		}
		static const Point4<T>& Identity()	{ return IDENTITY;	}

		static const Point4<T>& XAxis()		{ return Point4<T>::X_AXIS;	}
		static const Point4<T>& YAxis()		{ return Point4<T>::Y_AXIS;	}
		static const Point4<T>& ZAxis()		{ return Point4<T>::Z_AXIS;	}
		static const Point4<T>& WAxis()		{ return Point4<T>::W_AXIS;	}
		
		enum { IS_INTEGRAL			= TypeData<T>::IS_INTEGRAL			};
		enum { IS_FLOAT				= TypeData<T>::IS_FLOAT				};
		enum { IS_POD				= TypeData<T>::IS_POD				};
		enum { IS_BITWISE_COPY_SAFE	= TypeData<T>::IS_BITWISE_COPY_SAFE };
		enum { IS_POINTER			= TypeData<T>::IS_POINTER			};
		
	private:
		static const Point4<T> MINIMUM;
		static const Point4<T> MAXIMUM;
		static const Point4<T> IDENTITY;
	};

	template<typename T> const Point4<T> TypeData< Point4<T> >::MINIMUM( TypeData<T>::Minimum(), TypeData<T>::Minimum(), TypeData<T>::Minimum(), TypeData<T>::Minimum() ); 
	template<typename T> const Point4<T> TypeData< Point4<T> >::MAXIMUM( TypeData<T>::Maximum(), TypeData<T>::Maximum(), TypeData<T>::Maximum(), TypeData<T>::Maximum() ); 
	template<typename T> const Point4<T> TypeData< Point4<T> >::IDENTITY( TypeData<T>::Identity(), TypeData<T>::Identity(), TypeData<T>::Identity(), TypeData<T>::Identity() );

	// Write output Vector4 in format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
	GCLINLINE std::ostream& operator<<( std::ostream& output, const Point4<Real> &P)
	{
		output << "(" << P.x << ", " << P.y << ", " << P.z << ", " << P.w <<")";
		return output;
	}
//============================================================================

	typedef Point4<Real> WorldPoint4;
	
//============================================================================
}
//============================================================================
