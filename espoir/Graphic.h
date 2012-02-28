#pragma once
#include"GraphicInfo.h"

namespace espoir{
class Graphic
{
SP_TDEF(GraphicInfo);

private:
	SPGraphicInfo gInfo_;
public:
	Graphic(SPGraphicInfo gInfo);

	//テキストメッセージの表示
	void DrawString(String text);
	void DrawCircle(Rect rect);
	~Graphic(void);
};

}