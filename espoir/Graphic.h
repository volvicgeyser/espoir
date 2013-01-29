#pragma once
#include"GraphicInfo.h"
//#include"vertex.h"
#include"ComPtr.h"

namespace espoir{
class Graphic
{

private:
	//std::vector<Vertex> vertexArray;

public:
	//typedef ComPtr<IDirect3DTexture9> SPTexture;
	typedef boost::intrusive_ptr<IDirect3DTexture9> SPTexture;
	typedef boost::intrusive_ptr<ID3DXSprite> SPSprite;

	Graphic();

	//テキストメッセージの表示
	void DrawString(String text);

	//円の描画
	void DrawCircle(const RECT& rect);

	//設定された四角形の頂点を元に描画
	void DrawRect();

	//四角形の頂点を設定
	void SetRect(const RECT& rect);

	//画像をロードする
	SPTexture LoadGraphic(const String& filename);

	SPTexture LoadGraphicFromCache(const String& filename);

	void DrawGraphic(const SPTexture& spTexture, const RECT& rect);

	~Graphic(void);
};

}
