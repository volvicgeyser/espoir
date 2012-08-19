#pragma once
#include"FontInfo.h"

namespace espoir{

//DirectXのフォントを管理するクラスです
struct Font{
	FontInfo fontInfo_;	
	Font(String font_name);
	void DrawString(String str);
};

}