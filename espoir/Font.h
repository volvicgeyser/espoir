#pragma once
#include"FontInfo.h"

namespace espoir{

//DirectX�̃t�H���g���Ǘ�����N���X�ł�
struct Font{
	FontInfo fontInfo_;	
	Font(String font_name);
	void DrawString(String str);
};

}