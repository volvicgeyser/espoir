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

	//円の描画
	void DrawCircle(const RECT& rect);

	//四角形の描画
	void DrawRect(const RECT& rect);


	~Graphic(void);
};

}