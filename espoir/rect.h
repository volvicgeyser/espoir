#pragma once

namespace espoir{

//éläpå`ÇÃç\ë¢ëÃ
template <typename T>
struct Rect_
{
	Rect_(void){}
	
	T x;
	T y;
	T w;
	T h;
};

//intå^Rect
typedef Rect_<int> Rect;

//floatå^Rect
typedef Rect_<float> RectF;
	
}