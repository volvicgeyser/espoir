#pragma once

namespace espoir{

//�l�p�`�̍\����
template <typename T>
struct Rect_
{
	Rect_(void){}
	
	T x;
	T y;
	T w;
	T h;
};

//int�^Rect
typedef Rect_<int> Rect;

//float�^Rect
typedef Rect_<float> RectF;
	
}