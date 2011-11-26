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

#include "gcl/Matrix43.h"

//============================================================================

using namespace GCL;

//============================================================================

const Matrix43 Matrix43::ZERO(false);
const Matrix43 Matrix43::IDENTITY(true);

//============================================================================

Matrix43 Matrix43::operator-() const throw()					
{ 
	return Matrix43(-m0, -m1, -m2, -m3);	
}

Matrix43 Matrix43::operator+(const Matrix43& a) const throw()	
{ 
	return Matrix43(m0+a.m0, m1+a.m1, m2+a.m2, m3+a.m3);	
}

Matrix43 Matrix43::operator-(const Matrix43& a) const throw()	
{ 
	return Matrix43(m0-a.m0, m1-a.m1, m2-a.m2, m3-a.m3);	
}

Matrix43& Matrix43::operator+=(const Matrix43& a) throw()		
{ 
	m0 += a.m0; 
	m1 += a.m1; 
	m2 += a.m2; 
	m3 += a.m3;
	return *this;	
}

Matrix43& Matrix43::operator-=(const Matrix43& a) throw()		
{ 
	m0 -= a.m0; 
	m1 -= a.m1; 
	m2 -= a.m2; 
	m3 -= a.m3;
	return *this;	
}

namespace GCL
{	
	Matrix43  Inverse(const Matrix43& m) throw()
	{
		WorldUnit a0 = m[1][1]*m[2][2] - m[1][2]*m[2][1];
		WorldUnit a1 = m[1][2]*m[2][0] - m[1][0]*m[2][2];
		WorldUnit a2 = m[1][0]*m[2][1] - m[1][1]*m[2][0];
		
		WorldUnit s = 1.0f / (m[0][0]*a0 + m[0][1]*a1 + m[0][2]*a2);
		
		Matrix43 result;
		result[0].Set(s*a0, s*(m[0][2]*m[2][1]-m[0][1]*m[2][2]), s*(m[0][1]*m[1][2]-m[0][2]*m[1][1]));
		result[1].Set(s*a1, s*(m[0][0]*m[2][2]-m[0][2]*m[2][0]), s*(m[0][2]*m[1][0]-m[0][0]*m[1][2]));
		result[2].Set(s*a2, s*(m[0][1]*m[2][0]-m[0][0]*m[2][1]), s*(m[0][0]*m[1][1]-m[0][1]*m[1][0]));
		result[3] = result.TransformVector(-m[3]);

		return result;
	}
}

#if defined(JASM_GNUC_ARM_NEON)

Matrix43 GCL::operator*(const WorldUnit a, const Matrix43& b) throw() 
{
	asm("fmsr		s0, r1");
	asm("vldmia		r2!, { q1-q3 }");

	asm("vmul.f32	q1, q1, d0[0]");
	asm("vmul.f32	q2, q2, d0[0]");
	asm("vmul.f32	q3, q3, d0[0]");

	asm("vstmia		r0, { q1-q3 }");
}

Matrix43 Matrix43::operator*(const Matrix43& a) const throw()
{
	asm("fstmfds	sp!, { s16-s27 }");
	
	asm("fldmias	r2!, { s0-s2 }");
	asm("fldmias	r1, { s16-s27 }");
	
	asm("fldmias	r2!, { s4-s6 }");
	asm("fldmias	r2!, { s8-s10 }");
	asm("fldmias	r2!, { s12-s14 }");

	asm("vmul.f32	q8, q0, d8[0]");
	asm("vmul.f32	q9, q0, d9[1]");
	asm("vmul.f32	q10, q0, d11[0]");
	asm("vmul.f32	q11, q0, d12[1]");

	asm("vmla.f32	q8, q1, d8[1]");
	asm("vmla.f32	q9, q1, d10[0]");
	asm("vmla.f32	q10, q1, d11[1]");
	asm("vmla.f32	q11, q1, d13[0]");

	asm("vmla.f32	q8, q2, d9[0]");
	asm("vmla.f32	q9, q2, d10[1]");
	asm("vmla.f32	q10, q2, d12[0]");
	asm("vmla.f32	q11, q2, d13[1]");

	asm("vmov.f32	q0, q8");	
	asm("vmov.f32	q1, q9");
	asm("vmov.f32	q2, q10");
	asm("vadd.f32	q3, q11, q3");
	
	asm("fstmias	r0!, { s0-s2 }");
	asm("fstmias	r0!, { s4-s6 }");
	asm("fstmias	r0!, { s8-s10 }");
	asm("fstmias	r0!, { s12-s14 }");	

	asm("fldmfds	sp!, { s16-s27 }");
}

WorldPoint3 GCL::operator*(const WorldPoint3& a, const Matrix43& b) throw()
{
	asm("fldmias	r2!, { s0-s2 }");
	asm("flds		s7, [ r1, #0 ]");

	asm("fldmias	r2!, { s4-s6 }");
	asm("fldmias	r2!, { s8-s10 }");
	asm("fldmias	r2!, { s12-s14 }");
	asm("flds		s11, [ r1, #4 ]");

	asm("vmul.f32	q8, q0, d3[1]");	
	asm("flds		s3, [ r1, #8 ]");
	asm("vmla.f32	q3, q1, d5[1]");
	asm("vmla.f32	q8, q2, d1[1]");
	asm("vadd.f32	q0, q3, q8");

	asm("fstmias	r0, { s0-s2 }");	
}

#elif defined(JASM_GNUC_ARM)

Matrix43 GCL::operator*(const WorldUnit a, const Matrix43& b) throw() 
{
	asm("fmsr	 s0, r1");
	asm("fldmias r2!, { s4-s15 }");

	asm("fmuls	 s4, s4, s0");
	asm("fmuls	 s5, s5, s0");
	asm("fmuls	 s6, s6, s0");
	asm("fmuls	 s7, s7, s0");
	asm("fmuls	 s8, s8, s0");
	asm("fmuls	 s9, s9, s0");
	asm("fmuls	 s10, s10, s0");
	asm("fmuls	 s11, s11, s0");
	asm("fmuls	 s12, s12, s0");
	asm("fmuls	 s13, s13, s0");
	asm("fmuls	 s14, s14, s0");
	asm("fmuls	 s15, s15, s0");
	
	asm("fstmias r0!, { s4-s15 }");
}

Matrix43 Matrix43::operator*(const Matrix43& a) const throw()
{ 
	asm("fstmfds sp!, { s18-s29 }");
	
	asm("fmrx	 r12, fpscr");
	asm("mov	 r3, #0x00020000");
	asm("orr	 r3, #0x02000000");
	asm("fmxr	 fpscr, r3");

	asm("fldmias r1!, { s0-s5 }");
	asm("fldmias r2, { s18-s29 }");
	
	asm("add	 r3, r0, #36");
	
	asm("fmuls	 s8, s18, s0");
	asm("fmuls	 s11, s18, s3");
	asm("fmacs	 s8, s21, s1");
	asm("fmacs	 s11, s21, s4");
	asm("fmacs	 s8, s24, s2");
	asm("fmacs	 s11, s24, s5");

	asm("fldmias r1!, { s0-s5 }");
	asm("fstmias r0!, { s8-s13 }");

	asm("fmacs	 s27, s18, s3");
	asm("fmuls	 s8, s18, s0");
	asm("fmacs	 s27, s21, s4");
	asm("fmacs	 s8, s21, s1");
	asm("fmacs	 s27, s24, s5");
	asm("fmacs	 s8, s24, s2");

	asm("fldmfds sp!, { s18-s25 }");

	asm("fstmias r3!, { s27-s29 }");
	asm("fstmias r0!, { s8-s10 }");	

	asm("fldmfds sp!, { s26-s29 }");
	asm("fmxr	 fpscr, r12");
}

WorldPoint3 GCL::operator*(const WorldPoint3& a, const Matrix43& b) throw()
{
	asm("fldmias r1, { s0-s2 }");
	asm("fldmias r2, { s4-s15 }");

	asm("fmuls	 s4, s4, s0");
	asm("fmuls	 s5, s5, s0");
	asm("fmuls	 s6, s6, s0");

	asm("fmacs	 s13, s7, s1");
	asm("fmacs	 s14, s8, s1");
	asm("fmacs	 s15, s9, s1");

	asm("fmacs	 s4, s10, s2");
	asm("fmacs	 s5, s11, s2");
	asm("fmacs	 s6, s12, s2");

	asm("fadds	 s4, s4, s13");
	asm("fadds	 s5, s5, s14");
	asm("fadds	 s6, s6, s15");
	
	asm("fstmias r0, { s4-s6 }");
}
	
#else

Matrix43  GCL::operator*(const WorldUnit a, const Matrix43& b) throw() 
{ 
	return Matrix43(a*b.m0, a*b.m1, a*b.m2, a*b.m3);
}

Matrix43  Matrix43::operator*(const Matrix43& a) const throw()
{
	return Matrix43(a.TransformVector(m0), a.TransformVector(m1), a.TransformVector(m2), m3 * a);
}

WorldPoint3  GCL::operator*(const WorldPoint3& a, const Matrix43& b) throw()
{
	return WorldPoint3(a[0]*b[0][0] + a[1]*b[1][0] + a[2]*b[2][0] + b[3][0],
					   a[0]*b[0][1] + a[1]*b[1][1] + a[2]*b[2][1] + b[3][1],
					   a[0]*b[0][2] + a[1]*b[1][2] + a[2]*b[2][2] + b[3][2]);
}

#endif // defined(JASM_GNUC_ARM)

//============================================================================
