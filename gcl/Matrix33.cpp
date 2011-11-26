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

#include "gcl/Matrix33.h"

//============================================================================

using namespace GCL;

//============================================================================

const Matrix33 Matrix33::ZERO(false);
const Matrix33 Matrix33::IDENTITY(true);

//============================================================================

Matrix33 Matrix33::operator-() const throw()					
{ 
	return Matrix33(-m0, -m1, -m2);	
}

Matrix33 Matrix33::operator+(const Matrix33& a) const throw()	
{ 
	return Matrix33(m0+a.m0, m1+a.m1, m2+a.m2);	
}

Matrix33 Matrix33::operator-(const Matrix33& a) const throw()	
{ 
	return Matrix33(m0-a.m0, m1-a.m1, m2-a.m2);	
}

Matrix33& Matrix33::operator+=(const Matrix33& a) throw()		
{ 
	m0 += a.m0; 
	m1 += a.m1; 
	m2 += a.m2; 
	return *this;	
}

Matrix33& Matrix33::operator-=(const Matrix33& a) throw()		
{ 
	m0 -= a.m0; 
	m1 -= a.m1; 
	m2 -= a.m2; 
	return *this;	
}

namespace GCL
{	
	Matrix33  Inverse(const Matrix33& m) throw()
	{
		WorldUnit a0 = m[1][1]*m[2][2] - m[1][2]*m[2][1];
		WorldUnit a1 = m[1][2]*m[2][0] - m[1][0]*m[2][2];
		WorldUnit a2 = m[1][0]*m[2][1] - m[1][1]*m[2][0];

		WorldUnit s = 1.0f / (m[0][0]*a0 + m[0][1]*a1 + m[0][2]*a2);

		return Matrix33(WorldPoint3(s*a0, s*(m[0][2]*m[2][1]-m[0][1]*m[2][2]), s*(m[0][1]*m[1][2]-m[0][2]*m[1][1])),
						WorldPoint3(s*a1, s*(m[0][0]*m[2][2]-m[0][2]*m[2][0]), s*(m[0][2]*m[1][0]-m[0][0]*m[1][2])),
						WorldPoint3(s*a2, s*(m[0][1]*m[2][0]-m[0][0]*m[2][1]), s*(m[0][0]*m[1][1]-m[0][1]*m[1][0])));
	}

	WorldUnit  Determinant(const Matrix33& m) throw()
	{
		return m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1])
			   + m[0][1]*(m[1][2]*m[2][0] - m[1][0]*m[2][2])
			   + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
	}
}

#if defined(JASM_GNUC_ARM_NEON)

Matrix33 GCL::operator*(const WorldUnit a, const Matrix33& b) throw()
{ 
	asm("fmsr	 s0, r1");
	asm("fldmias r2!, { s4-s12 }");
	
	asm("fmuls	 s4, s4, s0");
	asm("fmuls	 s5, s5, s0");
	asm("fmuls	 s6, s6, s0");
	asm("fmuls	 s7, s7, s0");
	asm("fmuls	 s8, s8, s0");
	asm("fmuls	 s9, s9, s0");
	asm("fmuls	 s10, s10, s0");
	asm("fmuls	 s11, s11, s0");
	asm("fmuls	 s12, s12, s0");
	
	asm("fstmias r0, { s4-s12 }");
}

Matrix33 Matrix33::operator*(const Matrix33& a) const throw()
{
	return Matrix33(m0*a, m1*a, m2*a);
}

WorldPoint3 GCL::operator*(const WorldPoint3& a, const Matrix33& b) throw()
{
	asm("fldmias	r1, { s0-s2 }");
	asm("fldmias	r2!, { s4-s6 }");
	asm("fldmias	r2!, { s8-s10 }");
	asm("fldmias	r2!, { s12-s14 }");
	
	asm("vmul.f32	q1, q1, d0[0]");
	asm("vmla.f32	q1, q2, d0[1]");
	asm("vmla.f32	q1, q3, d1[0]");
	
	asm("fstmias r0, { s4-s6 }");
}

#elif defined(JASM_GNUC_ARM)

Matrix33 GCL::operator*(const WorldUnit a, const Matrix33& b) throw()
{ 
	asm("fmsr	 s0, r1");
	asm("fldmias r2!, { s4-s12 }");
	
	asm("fmuls	 s4, s4, s0");
	asm("fmuls	 s5, s5, s0");
	asm("fmuls	 s6, s6, s0");
	asm("fmuls	 s7, s7, s0");
	asm("fmuls	 s8, s8, s0");
	asm("fmuls	 s9, s9, s0");
	asm("fmuls	 s10, s10, s0");
	asm("fmuls	 s11, s11, s0");
	asm("fmuls	 s12, s12, s0");
	
	asm("fstmias r0, { s4-s12 }");
}

Matrix33 Matrix33::operator*(const Matrix33& a) const throw()
{
	return Matrix33(m0*a, m1*a, m2*a);
}

WorldPoint3 GCL::operator*(const WorldPoint3& a, const Matrix33& b) throw()
{
	asm("fldmias r1, { s0-s2 }");
	asm("fldmias r2, { s4-s12 }");
	
	asm("fmuls	 s4, s4, s0");
	asm("fmuls	 s5, s5, s0");
	asm("fmuls	 s6, s6, s0");
	
	asm("fmacs	 s4, s7, s1");
	asm("fmacs	 s5, s8, s1");
	asm("fmacs	 s6, s9, s1");
	
	asm("fmacs	 s4, s10, s2");
	asm("fmacs	 s5, s11, s2");
	asm("fmacs	 s6, s12, s2");
	
	asm("fstmias r0, { s4-s6 }");
}

#else

Matrix33  Matrix33::operator*(const Matrix33& a) const throw()
{
	return Matrix33(m0*a, m1*a, m2*a);
}

Matrix33  GCL::operator*(const WorldUnit a, const Matrix33& b) throw() 
{ 
	return Matrix33(a*b.m0, a*b.m1, a*b.m2); 
}

WorldPoint3  GCL::operator*(const WorldPoint3& a, const Matrix33& b) throw()
{
	return WorldPoint3(a[0]*b[0][0] + a[1]*b[1][0] + a[2]*b[2][0],
					   a[0]*b[0][1] + a[1]*b[1][1] + a[2]*b[2][1],
					   a[0]*b[0][2] + a[1]*b[1][2] + a[2]*b[2][2]);
}

#endif // defined(JASM_GNUC_ARM)

//============================================================================
