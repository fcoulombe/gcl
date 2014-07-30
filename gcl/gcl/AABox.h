/*
 * Copyright (C) 2014 by Francois Coulombe
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

#pragma once

#include "gcl/WorldUnit.h"
#include "gcl/Point3.h"

namespace GCL
{
	class AABox
	{
	public:
		AABox()
		{}
		AABox(Real x, Real y, Real z)
		{
			Real halfX = x*0.5;
			Real halfY = y*0.5;
			Real halfZ = z*0.5;
			mMin.x = -halfX;
			mMin.y = -halfY;
			mMin.z = -halfZ;
			mMax.x = halfX;
			mMax.y = halfY;
			mMax.z = halfZ;
		}
		const WorldPoint3 &GetMin() const { return mMin; }
		const WorldPoint3 &GetMax() const { return mMax; }
		Real GetWidth() const { return mMax.x - mMin.x; }
		Real GetHeight() const { return mMax.y - mMin.y; }
		Real GetLength() const { return mMax.z - mMin.z; }
		void SetOrigin(Real x, Real y, Real z)
		{ SetOrigin(WorldPoint3(x,y,z)); }
		void SetOrigin(const WorldPoint3 &position)
		{
			Real halfWidth = GetWidth() / 2.0;
			Real halfHeight = GetHeight() / 2.0;
			Real halfLength = GetLength() / 2.0;
			mMin.x = position.x - halfWidth;
			mMin.y = position.y - halfHeight;
			mMin.z = position.z - halfLength;
			mMax.x = position.x + halfWidth;
			mMax.y = position.y + halfHeight;
			mMax.z = position.z + halfLength;

		}
		inline bool IsIntersecting(const AABox& b2) const
		{
			if (mMax.x < b2.mMin.x)
				return false;
			if (mMax.y < b2.mMin.y)
				return false;
			if (mMax.z < b2.mMin.z)
				return false;
			if (mMin.x > b2.mMax.x)
				return false;
			if (mMin.y > b2.mMax.y)
				return false;
			if (mMin.z > b2.mMax.z)
				return false;
			return true;
		}
		bool operator==(const AABox& a) const
		{
			return a.GetMin() == mMin && a.GetMax() == mMax; 
		}
		bool operator!=(const AABox& a) const
		{
			return a.GetMin() != mMin || a.GetMax() != mMax; 
		}
	private:
		WorldPoint3 mMin;
		WorldPoint3 mMax;
	};
}
