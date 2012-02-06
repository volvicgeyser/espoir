#pragma once

namespace espoir{
typedef unsigned char Byte;

//カラー構造体
template <Byte tr, Byte tg, Byte tb>
struct static_color;

struct Color{
	Byte r;
	Byte g;
	Byte b;
	bool operator !=(Color c){
		return r != c.r || g != c.g || b != c.b;
	}
	bool operator ==(Color c){
		return r == c.r && g == c.g && b == c.b;
	}
	void operator=(Color& c){
		r = c.r;
		g = c.g;
		b = c.b;
	}
};

//静的なカラー構造体
template <Byte tr, Byte tg, Byte tb>
struct static_color{
	enum{
		r = tr,
		g = tg,
		b = tb
	};
	static Color Create(){
		Color c;
		c.r = r;
		c.g = g;
		c.b = b;
		return c;
	}
};

typedef static_color<255, 255, 255> White;
typedef static_color<0, 0, 0> Black;
typedef static_color<255, 0, 0> Red;
typedef static_color<0, 255, 0> Green;
typedef static_color<0, 0, 255> Blue;

}