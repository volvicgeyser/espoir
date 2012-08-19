#pragma once
#include"ComPtr.h"

namespace espoir{

//GDIの描画なので遅い。

//フォントの情報構造体
struct FontInfo{

	//文字の高さ
	INT height;

	//文字の幅
	UINT width;

	//ミップマップレベルの数
	UINT mipLevels;

	//イタリックかどうか
	BOOL italic;

	//フォントの文字セット
	DWORD charSet;

	//出力精度
	DWORD outputPrecision;

	//出力品質
	DWORD quality;

	//ピッチとファミリインデックス
	DWORD pitchAndFamily;

	//フォント名
	String pFacename;
	
	//フォントのポインタ
	boost::intrusive_ptr<ID3DXFont> ppFont;
};




}
