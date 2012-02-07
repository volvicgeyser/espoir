#pragma once

namespace espoir{



//フォントの情報構造体
struct FontInfo{


	//DirectXデバイス
	LPDIRECT3DDEVICE9 pDevice;

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
	ComPtr<LPD3DXFONT> ppFont;
}

}
