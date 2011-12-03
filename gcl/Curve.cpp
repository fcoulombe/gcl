#include "gcl/Curve.h"


using namespace GCL;


WorldPoint3 Curve::BezierCurve(const WorldPoint3& p1, const WorldPoint3& p2, const WorldPoint3& p3, const WorldPoint3& p4, WorldUnit t)
{
   WorldUnit mum1,mum13,mu3;
   mum1 = 1.0 - t;
   mum13 = mum1 * mum1 * mum1;
   mu3 = t * t * t;

   WorldPoint3 p;
   p.x = mum13*p1.x + 3*t*mum1*mum1*p2.x + 3*t*t*mum1*p3.x + mu3*p4.x;
   p.y = mum13*p1.y + 3*t*mum1*mum1*p2.y + 3*t*t*mum1*p3.y + mu3*p4.y;
   p.z = mum13*p1.z + 3*t*mum1*mum1*p2.z + 3*t*t*mum1*p3.z + mu3*p4.z;

   return p;
}

WorldPoint3 Curve::BezierCurvev(const std::vector<WorldPoint3 >& p, WorldUnit t)
{

	WorldUnit blend,muk,munk;
	size_t count = p.size();
	WorldPoint3 b(0.0, 0.0, 0.0);

	muk = 1.0;
	munk = std::pow(1.0-t,(WorldUnit)count);

	for(size_t k=0;k<count;k++)
	{
		int kn,nn,nkn;
		nn = count;
		kn = k;
		nkn = count - k;
		blend = muk * munk;
		muk *= t;
		munk /= (1.0-t);
		while (nn >= 1)
		{
			blend *= (WorldUnit)nn;
			--nn;
			if(kn > 1)
			{
				blend /= (WorldUnit)kn;
				--kn;
			}
			if (nkn > 1)
			{
				blend /= (WorldUnit)nkn;
				--nkn;
			}
		}
		b.x += p[k].x * blend;
		b.y += p[k].y * blend;
		b.z += p[k].z * blend;
	}
	return b;
}
