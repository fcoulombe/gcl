#pragma once

#include <GCL/Point2.h>

namespace GCL
{
template <typename T>
class Rect
{
public:
	Rect() {}

	T x,y;
	T width, height;
};
}
