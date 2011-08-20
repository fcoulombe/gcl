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
//
// Notes about FixedPoint
//
// int Fractional	- the number of bits used to represent the fractional
//					  component of the number
// typename T		- the 'container' type for the fixed point number
// typename S		- the intermediate type used for scaling
//
//============================================================================

#pragma once
#include "TypeData.h"

//============================================================================

namespace GCL
{
//============================================================================

	struct Raw;
	const Raw *const RAW = NULL;

//============================================================================

	template<int Fractional, typename T = int, typename S=typename TypeData<T>::MathematicalUpcast> struct FixedPoint
	{
	public:
	
		T rawValue;

		FixedPoint()						throw()	{ }
		FixedPoint(int i)					throw()	{ rawValue = i << Fractional;				}
		FixedPoint(float f)					throw()	{ rawValue = (T) (f * (1 << Fractional));	}
		FixedPoint(T aValue, const Raw*)	throw()	{ rawValue = aValue;						}

		template<bool EqualFractional, bool GreaterFractional, int f, typename T2, typename S2> 
			class _AssignHelper
		{
		public:
			static GCLINLINE void Assign(FixedPoint& a, const FixedPoint<f, T2, S2>& b) throw();
		};
			
		template<bool b, int f, typename T2, typename S2> 
			class _AssignHelper<true, b, f, T2, S2>
		{
		public:
			static GCLINLINE void Assign(FixedPoint& a, const FixedPoint<f, T2, S2>& b) throw()	{ a.rawValue = b.rawValue;	}
		};

		template<int f, typename T2, typename S2> 
			class _AssignHelper<false, true, f, T2, S2>
		{
		public:
			static GCLINLINE void Assign(FixedPoint& a, const FixedPoint<f, T2, S2>& b) throw()	{ a.rawValue = (T) (b.rawValue >> (f-Fractional));	}
		};

		template<int f, typename T2, typename S2> 
			class _AssignHelper<false, false, f, T2, S2>
		{
		public:
			static GCLINLINE void Assign(FixedPoint& a, const FixedPoint<f, T2, S2>& b) throw()	{ a.rawValue = (T) (b.rawValue << (Fractional-f));	}
		};

		template<int f, typename T2, typename S2> 
			FixedPoint(const FixedPoint<f, T2, S2>& a) throw() { _AssignHelper<f == Fractional, (f > Fractional), f, T2, S2>::Assign(*this, a);	}

		template<int f, typename T2, typename S2> 
			GCLINLINE void Set(const FixedPoint<f, T2, S2>& a) throw()	{ _AssignHelper<f == Fractional, (f > Fractional), f, T2, S2>::Assign(*this, a);	}

		GCLINLINE friend const FixedPoint operator+(const FixedPoint &a, const FixedPoint &b) throw()	{ return FixedPoint(a.rawValue + b.rawValue, RAW);			}
		GCLINLINE friend const FixedPoint operator-(const FixedPoint &a, const FixedPoint &b) throw()	{ return FixedPoint(a.rawValue - b.rawValue, RAW);			}

		template<int f, typename T2, typename S2> 
		GCLINLINE friend FixedPoint<f+Fractional, S> operator*(const FixedPoint &a, const FixedPoint<f, T2, S2> &b)	{ return FixedPoint<f+Fractional, S>( (S) a.rawValue * (S2) b.rawValue, RAW); 	}

		GCLINLINE friend FixedPoint operator/(const FixedPoint &a, const FixedPoint &b)	{ return FixedPoint((T) (((S) a.rawValue << Fractional)/b.rawValue), RAW);	}
		// Special case optimizations
		GCLINLINE friend const FixedPoint operator*(int a, const FixedPoint &b)	throw()	{ return FixedPoint(a*b.rawValue, RAW);	}
		GCLINLINE const FixedPoint operator*(int a) 			const				throw()	{ return FixedPoint(a*rawValue, RAW);	}
		GCLINLINE const FixedPoint operator/(int a) 			const				throw()	{ return FixedPoint(rawValue / a, RAW);	}

		// And functions to make sure that the special case optimizations don't get used when they shouldn't be.
		GCLINLINE friend const FixedPoint operator*(float a, const FixedPoint &b) throw()	{ return FixedPoint(a)*b;			}
		GCLINLINE const FixedPoint operator*(float a) 		const				 throw()	{ return *this * FixedPoint(a);	}
		GCLINLINE const FixedPoint operator/(float a) 		const				 throw()	{ return *this / FixedPoint(a);	}

		FixedPoint	operator-()			const throw()				{ return FixedPoint(-rawValue, RAW);		}
		FixedPoint	operator+()			const throw()				{ return *this;								}
		FixedPoint	operator>>(int a)	const throw()				{ return FixedPoint(rawValue >> a, RAW);	} 
		FixedPoint	operator<<(int a)	const throw()				{ return FixedPoint(rawValue << a, RAW);	} 

		FixedPoint& operator+=(const FixedPoint &a)		throw()		{ rawValue += a.rawValue;										return *this;	}
		FixedPoint& operator-=(const FixedPoint &a)		throw()		{ rawValue -= a.rawValue;										return *this;	}
		FixedPoint& operator*=(int a)					throw()		{ rawValue *= a;												return *this;	}
		FixedPoint& operator*=(float f)					throw()		{ rawValue *= f;												return *this;	}
		FixedPoint& operator*=(const FixedPoint &a)		throw()		{ rawValue = (T) (((S) rawValue * a.rawValue) >> Fractional);	return *this;	}
		FixedPoint& operator/=(int a)					throw()		{ rawValue /= a;												return *this;	}
		FixedPoint& operator/=(float f)					throw()		{ rawValue /= f;												return *this;	}
		FixedPoint& operator/=(const FixedPoint &a)		throw()		{ rawValue = (T) (((S) rawValue << Fractional)/a.rawValue);		return *this;	}
		FixedPoint& operator>>=(int a)					throw()		{ rawValue >>= a;												return *this;	}
		FixedPoint& operator<<=(int a)					throw()		{ rawValue <<= a;												return *this;	}

		template<int f, typename T2, typename S2> 
		FixedPoint& operator=(const FixedPoint<f, T2, S2>& a) throw() { _AssignHelper<f == Fractional, (f > Fractional), f, T2, S2>::Assign(*this, a);	}

		FixedPoint& operator=(const FixedPoint &a)		throw()		{ rawValue = a.rawValue;					return *this;		}
		FixedPoint& operator=(float f)					throw()		{ rawValue = (T) (f * (1 << Fractional));	return *this;		}
		FixedPoint& operator=(int a)					throw()		{ rawValue = a << Fractional;				return *this;		}

		int			GetIntegral()	const				throw()		{ return rawValue >> Fractional;								}
		FixedPoint	GetFractional()	const				throw()		{ return FixedPoint(rawValue & ~(-1 << Fractional), RAW);		}

		int			AsInteger()		const				throw()		{ return rawValue >> Fractional;								}
		float		AsFloat()		const				throw()		{ return rawValue * ( 1.0f / (1 << Fractional));				}

		// Comparison operators
		friend bool operator==(const FixedPoint &a, const FixedPoint &b) throw()	{ return a.rawValue == b.rawValue;		}
		friend bool operator!=(const FixedPoint &a, const FixedPoint &b) throw()	{ return a.rawValue != b.rawValue;		}
		friend bool operator<=(const FixedPoint &a, const FixedPoint &b) throw()	{ return a.rawValue <= b.rawValue;		}
		friend bool operator>=(const FixedPoint &a, const FixedPoint &b) throw()	{ return a.rawValue >= b.rawValue;		}
		friend bool operator<(const FixedPoint &a, const FixedPoint &b)	 throw()	{ return a.rawValue <  b.rawValue;		}
		friend bool operator>(const FixedPoint &a, const FixedPoint &b)	 throw()	{ return a.rawValue >  b.rawValue;		}
	};

//============================================================================
} // namespace GCL
//============================================================================
