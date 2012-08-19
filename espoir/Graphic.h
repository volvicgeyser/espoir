#pragma once
#include"GraphicInfo.h"
//#include"vertex.h"

namespace espoir{
class Graphic
{

private:
	
	//std::vector<Vertex> vertexArray;
public:
	Graphic();

	//テキストメッセージの表示
	void DrawString(String text);

	//円の描画
	void DrawCircle(const RECT& rect);

	//設定された四角形の頂点を元に描画
	void DrawRect();

	//四角形の頂点を設定
	void SetRect(const RECT& rect);

	~Graphic(void);
};

}
