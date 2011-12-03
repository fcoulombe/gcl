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

#include <cmath>

#include "gcl/Assert.h"
#include "gcl/Math.h"
#include "gcl/Matrix44.h"

//============================================================================

using namespace GCL;

//============================================================================

const Matrix44 Matrix44::ZERO(false);
const Matrix44 Matrix44::IDENTITY(true);

//============================================================================

Matrix44 Matrix44::operator-() const throw()					
		{
	return Matrix44(-m0, -m1, -m2, -m3);	
		}

Matrix44 Matrix44::operator+(const Matrix44& a) const throw()	
		{
	return Matrix44(m0+a.m0, m1+a.m1, m2+a.m2, m3+a.m3);	
		}

Matrix44 Matrix44::operator-(const Matrix44& a) const throw()	
		{
	return Matrix44(m0-a.m0, m1-a.m1, m2-a.m2, m3-a.m3);	
		}

Matrix44& Matrix44::operator+=(const Matrix44& a) throw()		
		{
	m0 += a.m0; 
	m1 += a.m1; 
	m2 += a.m2; 
	m3 += a.m3; 
	return *this;	
		}

Matrix44& Matrix44::operator-=(const Matrix44& a) throw()		
		{
	m0 -= a.m0; 
	m1 -= a.m1; 
	m2 -= a.m2; 
	m3 -= a.m3; 
	return *this;	
		}

Matrix44  GCL::operator*(const WorldUnit a, const Matrix44& b) throw() 
		{
	return Matrix44(a*b.m0, a*b.m1, a*b.m2, a*b.m3); 
		}



void Matrix44::SetRotationX(double rotation)
{
	*this = IDENTITY;
	m1[1] = cos(rotation);
	m1[2] = -sin(rotation);
	m2[1] = sin(rotation);
	m2[2] = cos(rotation);
}
void Matrix44::SetRotationY(double rotation)
{
	*this = IDENTITY;
	m0[0] = cos(rotation);
	m0[2] = sin(rotation);
	m2[0] = -sin(rotation);
	m2[2] = cos(rotation);
}
void Matrix44::SetRotationZ(double rotation)
{
	*this = IDENTITY;
	m0[0] = cos(rotation);
	m0[1] = -sin(rotation);
	m1[0] = sin(rotation);
	m1[1] = cos(rotation);
}

namespace GCL
{	
Matrix44  Inverse(const Matrix44& m)
{
	//std::cout << "inversing: " << m;
	WorldUnit a0 = m[0][0]*m[1][1] - m[0][1]*m[1][0];
	WorldUnit a1 = m[0][0]*m[1][2] - m[0][2]*m[1][0];
	WorldUnit a2 = m[0][0]*m[1][3] - m[0][3]*m[1][0];
	WorldUnit a3 = m[0][1]*m[1][2] - m[0][2]*m[1][1];
	WorldUnit a4 = m[0][1]*m[1][3] - m[0][3]*m[1][1];
	WorldUnit a5 = m[0][2]*m[1][3] - m[0][3]*m[1][2];
	WorldUnit b0 = m[2][0]*m[3][1] - m[2][1]*m[3][0];
	WorldUnit b1 = m[2][0]*m[3][2] - m[2][2]*m[3][0];
	WorldUnit b2 = m[2][0]*m[3][3] - m[2][3]*m[3][0];
	WorldUnit b3 = m[2][1]*m[3][2] - m[2][2]*m[3][1];
	WorldUnit b4 = m[2][1]*m[3][3] - m[2][3]*m[3][1];
	WorldUnit b5 = m[2][2]*m[3][3] - m[2][3]*m[3][2];

	const WorldUnit div = (a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0);
	GCLAssert(div!=0.0f);

	WorldUnit s = 1.0f / div;
	return Matrix44(WorldPoint4(s*( m[1][1]*b5 - m[1][2]*b4 + m[1][3]*b3 ),
			s*(-m[0][1]*b5 + m[0][2]*b4 - m[0][3]*b3 ),
			s*( m[3][1]*a5 - m[3][2]*a4 + m[3][3]*a3 ),
			s*(-m[2][1]*a5 + m[2][2]*a4 - m[2][3]*a3 )),
			WorldPoint4(s*(-m[1][0]*b5 + m[1][2]*b2 - m[1][3]*b1 ),
					s*( m[0][0]*b5 - m[0][2]*b2 + m[0][3]*b1 ),
					s*(-m[3][0]*a5 + m[3][2]*a2 - m[3][3]*a1 ),
					s*( m[2][0]*a5 - m[2][2]*a2 + m[2][3]*a1 )),
					WorldPoint4(s*( m[1][0]*b4 - m[1][1]*b2 + m[1][3]*b0 ),
							s*(-m[0][0]*b4 + m[0][1]*b2 - m[0][3]*b0 ),
							s*( m[3][0]*a4 - m[3][1]*a2 + m[3][3]*a0 ),
							s*(-m[2][0]*a4 + m[2][1]*a2 - m[2][3]*a0 )),
							WorldPoint4(s*(-m[1][0]*b3 + m[1][1]*b1 - m[1][2]*b0 ),
									s*( m[0][0]*b3 - m[0][1]*b1 + m[0][2]*b0 ),
									s*(-m[3][0]*a3 + m[3][1]*a1 - m[3][2]*a0 ),
									s*( m[2][0]*a3 - m[2][1]*a1 + m[2][2]*a0 ))						
	);
}

WorldUnit  Determinant(const Matrix44& m) throw()
			{
	WorldUnit a0 = m[0][0]*m[1][1] - m[0][1]*m[1][0];
	WorldUnit a1 = m[0][0]*m[1][2] - m[0][2]*m[1][0];
	WorldUnit a2 = m[0][0]*m[1][3] - m[0][3]*m[1][0];
	WorldUnit a3 = m[0][1]*m[1][2] - m[0][2]*m[1][1];
	WorldUnit a4 = m[0][1]*m[1][3] - m[0][3]*m[1][1];
	WorldUnit a5 = m[0][2]*m[1][3] - m[0][3]*m[1][2];
	WorldUnit b0 = m[2][0]*m[3][1] - m[2][1]*m[3][0];
	WorldUnit b1 = m[2][0]*m[3][2] - m[2][2]*m[3][0];
	WorldUnit b2 = m[2][0]*m[3][3] - m[2][3]*m[3][0];
	WorldUnit b3 = m[2][1]*m[3][2] - m[2][2]*m[3][1];
	WorldUnit b4 = m[2][1]*m[3][3] - m[2][3]*m[3][1];
	WorldUnit b5 = m[2][2]*m[3][3] - m[2][3]*m[3][2];

	return a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
			}
}

#if defined(JASM_GNUC_ARM_NEON)

Matrix44 Matrix44::operator*(const Matrix44& a) const throw()
		{
	asm("vldmia		r1, { q0-q3 }");		// q4-q7 = *this
	asm("vldmia		r2, { q8-q11 }");		// q8-q11 = a

	asm("vmul.f32	q12, q8, d0[0]");
	asm("vmul.f32	q13, q8, d2[0]");
	asm("vmul.f32	q14, q8, d4[0]");
	asm("vmul.f32	q15, q8, d6[0]");

	asm("vmla.f32	q12, q9, d0[1]");
	asm("vmla.f32	q13, q9, d2[1]");
	asm("vmla.f32	q14, q9, d4[1]");
	asm("vmla.f32	q15, q9, d6[1]");

	asm("vmla.f32	q12, q10, d1[0]");
	asm("vmla.f32	q13, q10, d3[0]");
	asm("vmla.f32	q14, q10, d5[0]");
	asm("vmla.f32	q15, q10, d7[0]");

	asm("vmla.f32	q12, q11, d1[1]");
	asm("vmla.f32	q13, q11, d3[1]");
	asm("vmla.f32	q14, q11, d5[1]");
	asm("vmla.f32	q15, q11, d7[1]");

	asm("vstmia		r0, { q12-q15 }");	
		}

WorldPoint3 GCL::operator*(const WorldPoint3& a, const Matrix44& b) throw()
		{
	asm("fldmias	r1, { s0-s2 }");
	asm("vldmia		r2!, { q8-q11 }");

	asm("vmul.f32	q8, q8, d0[0]");
	asm("vmla.f32	q11, q9, d0[1]");
	asm("vmla.f32	q8, q10, d1[0]");
	asm("vadd.f32	q0, q11, q8");

	asm("fstmias	r0, { s0-s2 }");
		}

WorldPoint4 GCL::operator*(const WorldPoint4& a, const Matrix44& b) throw()
		{
	asm("vldmia		r1, { q0 }");
	asm("vldmia		r2!, { q8-q11 }");

	asm("vmul.f32	q8, q8, d0[0]");
	asm("vmul.f32	q9, q9, d0[1]");
	asm("vmla.f32	q8, q10, d1[0]");
	asm("vmla.f32	q9, q11, d1[1]");
	asm("vadd.f32	q8, q8, q9");

	asm("vstmia		r0, { q8 }");
		}

#elif defined(JASM_GNUC_ARM)

Matrix44 Matrix44::operator*(const Matrix44& a) const throw()
		{
	asm("fstmfds sp!, { s16-s31 }");

	asm("fmrx	 r12, fpscr");
	asm("mov	 r3, #0x00030000");
	asm("orr	 r3, #0x02000000");
	asm("fmxr	 fpscr, r3");

	asm("fldmias r1!, { s0-s7 }");
	asm("fldmias r2, { s16-s31 }");

	asm("fmuls	 s8, s16, s0");
	asm("fmuls	 s12, s16, s4");
	asm("fmacs	 s8, s20, s1");
	asm("fmacs	 s12, s20, s5");
	asm("fmacs	 s8, s24, s2");
	asm("fmacs	 s12, s24, s6");
	asm("fmacs	 s8, s28, s3");
	asm("fmacs	 s12, s28, s7");

	asm("fldmias r1!, { s0-s7 }");
	asm("fstmias r0!, { s8-s15 }");

	asm("fmuls	 s8, s16, s0");
	asm("fmuls	 s12, s16, s4");
	asm("fmacs	 s8, s20, s1");
	asm("fmacs	 s12, s20, s5");
	asm("fmacs	 s8, s24, s2");
	asm("fmacs	 s12, s24, s6");
	asm("fmacs	 s8, s28, s3");
	asm("fmacs	 s12, s28, s7");

	asm("fldmfds sp!, { s16-s31 }");
	asm("fstmias r0!, { s8-s15 }");

	asm("fmxr	 fpscr, r12");
		}

WorldPoint3 GCL::operator*(const WorldPoint3& a, const Matrix44& b) throw()
		{
	asm("fstmfds sp!, { s16-s18 }");
	asm("fldmias r1, { s0-s2 }");
	asm("fldmias r2, { s4-s18 }");

	asm("fmuls	 s4, s4, s0");
	asm("fmuls	 s5, s5, s0");
	asm("fmuls	 s6, s6, s0");

	asm("fmacs	 s16, s8, s1");
	asm("fmacs	 s17, s9, s1");
	asm("fmacs	 s18, s10, s1");

	asm("fmacs	 s4, s12, s2");
	asm("fmacs	 s5, s13, s2");
	asm("fmacs	 s6, s14, s2");

	asm("fadds   s4, s4, s16");
	asm("fadds   s5, s5, s17");
	asm("fadds   s6, s6, s18");

	asm("fldmfds sp!, { s16-s18 }");
	asm("fstmias r0, { s4-s6 }");
		}

WorldPoint4 GCL::operator*(const WorldPoint4& a, const Matrix44& b) throw()
		{
	asm("fstmfds sp!, { s16-s19 }");
	asm("fldmias r1, { s0-s3 }");
	asm("fldmias r2, { s4-s19 }");

	asm("fmuls	 s4, s4, s0");
	asm("fmuls	 s5, s5, s0");
	asm("fmuls	 s6, s6, s0");
	asm("fmuls	 s7, s7, s0");

	asm("fmuls	 s8, s8, s1");
	asm("fmuls	 s9, s9, s1");
	asm("fmuls	 s10, s10, s1");
	asm("fmuls	 s11, s11, s1");

	asm("fmacs	 s4, s12, s2");
	asm("fmacs	 s5, s13, s2");
	asm("fmacs	 s6, s14, s2");
	asm("fmacs	 s7, s15, s2");

	asm("fmacs	 s8, s16, s3");
	asm("fmacs	 s9, s17, s3");
	asm("fmacs	 s10, s18, s3");
	asm("fmacs	 s11, s19, s3");

	asm("fadds   s4, s4, s8");
	asm("fadds   s5, s5, s9");
	asm("fadds   s6, s6, s10");
	asm("fadds   s7, s7, s11");

	asm("fldmfds sp!, { s16-s19 }");
	asm("fstmias r0, { s4-s7 }");
		}

#else

Matrix44  Matrix44::operator*(const Matrix44& a) const throw()
		{
	return Matrix44(m0*a, m1*a, m2*a, m3*a);
		}

WorldPoint3  GCL::operator*(const WorldPoint3& a, const Matrix44& b) throw()
		{
	return WorldPoint3(a[0]*b[0][0] + a[1]*b[1][0] + a[2]*b[2][0] + b[3][0],
			a[0]*b[0][1] + a[1]*b[1][1] + a[2]*b[2][1] + b[3][1],
			a[0]*b[0][2] + a[1]*b[1][2] + a[2]*b[2][2] + b[3][2]);
		}

#if 0 // defined(JASM_GNUC_X86_SSE3)

WorldPoint4 GCL::operator*(const WorldPoint4& a, const Matrix44& b) throw()
		{
	asm("mov	8(%ebp), %eax");
	asm("mov	12(%ebp), %ecx");
	asm("mov	16(%ebp), %edx");

	asm("movups	(%ecx), %xmm0");
	asm("movups (%edx), %xmm4");
	asm("movaps %xmm0, %xmm1");
	asm("movaps %xmm0, %xmm2");
	asm("movaps %xmm0, %xmm3");
	asm("shufps $0, %xmm0, %xmm0");
	asm("movups 16(%edx), %xmm5");
	asm("shufps $0x55, %xmm1, %xmm1");
	asm("movups 32(%edx), %xmm6");
	asm("shufps $0xaa, %xmm2, %xmm2");
	asm("movups 48(%edx), %xmm7");
	asm("shufps $0xff, %xmm3, %xmm3");
	asm("mulps  %xmm4, %xmm0");
	asm("mulps  %xmm5, %xmm1");
	asm("mulps  %xmm6, %xmm2");
	asm("mulps  %xmm7, %xmm3");
	asm("addps	%xmm1, %xmm0");
	asm("addps	%xmm3, %xmm2");
	asm("addps	%xmm2, %xmm0");
	asm("movups %xmm0, (%eax)");
		}

#else

WorldPoint4  GCL::operator*(const WorldPoint4& a, const Matrix44& b) throw()
		{
	return WorldPoint4(a[0]*b[0][0] + a[1]*b[1][0] + a[2]*b[2][0] + a[3]*b[3][0],
			a[0]*b[0][1] + a[1]*b[1][1] + a[2]*b[2][1] + a[3]*b[3][1],
			a[0]*b[0][2] + a[1]*b[1][2] + a[2]*b[2][2] + a[3]*b[3][2],
			a[0]*b[0][3] + a[1]*b[1][3] + a[2]*b[2][3] + a[3]*b[3][3] );
		}

#endif

#endif


/***************************************
 * Sets up our perspective clip matrix *
 ***************************************/




/*
void Matrix44::Perspective(Matrix44 &m, const WorldUnit fov, const WorldUnit aspect, const WorldUnit znear, const WorldUnit zfar)
{
	WorldUnit ymax = znear * tan(fov * PI/360.0);
	WorldUnit ymin = -ymax;
	WorldUnit xmax = ymax * aspect;
	WorldUnit xmin = ymin * aspect;

	WorldUnit width = xmax - xmin;
	WorldUnit height = ymax - ymin;

	WorldUnit depth = zfar - znear;
	WorldUnit q = -(zfar + znear) / depth;
	WorldUnit qn = -2 * (zfar * znear) / depth;

	WorldUnit w = 2 * znear / width;
	w = w / aspect;
	WorldUnit h = 2 * znear / height;


	m[0].x  = w;
	m[0].y  = 0;
	m[0].z  = 0;
	m[0].w  = 0;

	m[1].x  = 0;
	m[1].y  = h;
	m[1].z  = 0;
	m[1].w  = 0;

	m[2].x  = 0;
	m[2].y  = 0;
	m[2].z = q;
	m[2].w = -1;

	m[3].x = 0;
	m[3].y = 0;
	m[3].z = qn;
	m[3].w = 0;
}
*/

//============================================================================
