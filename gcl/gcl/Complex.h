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

#include "gcl/Macro.h"
#include <cmath>

//============================================================================

namespace GCL
{
//============================================================================

	template<typename T> class Complex
	{
	public:
		T	r;
		T	i;

		Complex()															{ }
		GCLINLINE Complex(const T &ir, const T &ii)	: r(ir), i(ii)			{ }
		GCLINLINE Complex(const T a[2])				: r(a[0]), i(a[1])		{ }
																									
		GCLINLINE void Set(const T &ir, const T &ii)			{ r = ir; i = ii;						}
		GCLINLINE void Set(const T a[2])						{ r = a[0]; i = a[1];					}

		GCLINLINE Complex operator+()					const	{ return *this;							}
		GCLINLINE Complex operator-()					const	{ return Complex(-r, -i);				}

		GCLINLINE Complex operator+(const Complex &c)	const	{ return Complex(r+c.r, i+c.i);			}
		GCLINLINE Complex operator-(const Complex &c)	const	{ return Complex(r-c.r, i-c.i);			}
		GCLINLINE Complex operator*(const Complex &c)	const	{ return Complex(r*c.r - i*c.i, r*c.i + i*c.r);	}
		GCLINLINE Complex operator*(T a)				const	{ return Complex(r*a,   i*a  );			}
		GCLINLINE Complex operator/(const Complex &c)	const	{ return *this * Inverse(c);			}
		GCLINLINE Complex operator/(T a)				const	{ return Complex(r/a,   i/a  );			}
																								
		GCLINLINE Complex& operator+=(const Complex &c)			{ r += c.r; i += c.i;	return *this;	}
		GCLINLINE Complex& operator-=(const Complex &c)			{ r -= c.r; i -= c.i;	return *this;	}
		GCLINLINE Complex& operator*=(const Complex &c)			{ *this = *this * c;	return *this;	}
		GCLINLINE Complex& operator*=(T a)						{ r *= a;   i *= a;		return *this;	}
		GCLINLINE Complex& operator/=(const Complex &c)			{ *this *= Inverse(c);	return *this;	}
		GCLINLINE Complex& operator/=(T a)						{ r /= a;   i /= a;		return *this;	}
																									
		// Dot product																				
		GCLINLINE typename TypeData<T>::MathematicalUpcast operator%(const Complex &c) const	{ return r*c.r + i*c.i;		}
																									
		// Array access operators.																	
		GCLINLINE const T& operator[](int n)			const		{ return (&r)[n];						}
		GCLINLINE		  T& operator[](int n)						{ return (&r)[n];						}
																									
		GCLINLINE bool operator==(const Complex &c)	const		{ return r==c.r && i==c.i;				}
		GCLINLINE bool operator!=(const Complex &c)	const		{ return r!=c.r || i!=c.i;				}
		GCLINLINE bool operator< (const Complex &c)	const		{ return r< c.r && i< c.i;				}
		GCLINLINE bool operator> (const Complex &c)	const		{ return r> c.r && i> c.i;				}
		GCLINLINE bool operator<=(const Complex &c)	const		{ return r<=c.r && i<=c.i;				}
		GCLINLINE bool operator>=(const Complex &c)	const		{ return r>=c.r && i>=c.i;				}

		GCLINLINE friend typename TypeData<T>::MathematicalFloatUpcast Length(const Complex &c)			{ return sqrt(static_cast<typename TypeData<T>::MathematicalFloatUpcast>(c.r*c.r + c.i*c.i));	}
		GCLINLINE friend typename TypeData<T>::MathematicalFloatUpcast Argument(const Complex &c)			{ return atan2(static_cast<typename TypeData<T>::MathematicalFloatUpcast>(c.i), static_cast<typename TypeData<T>::MathematicalFloatUpcast>(c.r));	}
		GCLINLINE friend typename TypeData<T>::MathematicalUpcast		 LengthSquared(const Complex &c)	{ return c.r*c.r + c.i*c.i;			}
		GCLINLINE friend Complex Conjugate(const Complex &c)		{ return Complex(c.r, -c.i);							}
		GCLINLINE friend Complex Inverse(const Complex &c)		{ return Conjugate(c) * (1.0f / Length(c));				}
		GCLINLINE friend Complex Normalize(const Complex &c)		{ return c * (1.0f / Length(c));						}

		template<typename A>
			GCLINLINE friend Complex operator*(const A &a, const Complex &c)	{ return Complex(a*c.r, a*c.i);					}

		friend Complex Minimum(const Complex &a, const Complex &b)	{ return Complex(Minimum(a.r, b.r), Minimum(a.i, b.i));	}
		friend Complex Maximum(const Complex &a, const Complex &b)	{ return Complex(Maximum(a.r, b.r), Maximum(a.i, b.i));	}
		void SetMinimum(const Complex &c)							{ if(c.r < r) r = c.r; if(r.i < i) i = c.i;				}
		void SetMaximum(const Complex &c)							{ if(c.r > r) r = c.r; if(r.i > i) i = c.i;				}
	};

//============================================================================

	// Floating point Point2 optimization overrides.
	template<> GCLINLINE Complex<float>  Complex<float>::operator/(float a) const	{ float s = 1.0f / a; return Complex(s*r, s*i);		}
	template<> GCLINLINE Complex<float>& Complex<float>::operator/=(float a)		{ float s = 1.0f / a; r *= s; i *= s; return *this;	}

//============================================================================
} // namespace GCL

//============================================================================
