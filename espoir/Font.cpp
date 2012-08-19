#include"stdafx.h"
#include"font.h"
#include"intrusive_func.h"
#include"system.h"

namespace espoir{

Font::Font(String font_name){
	if(font_name.empty()){
		throw std::runtime_error("フォント名の文字列が空っぽです");
	}

	//フォント名
	this->fontInfo_.pFacename = font_name;

	//イタリック off
	this->fontInfo_.italic = false;

	this->fontInfo_.height = 10;

	this->fontInfo_.width = 0;

	this->fontInfo_.mipLevels = 0;
	this->fontInfo_.charSet = 0;
	this->fontInfo_.outputPrecision = 0;
	this->fontInfo_.quality = DEFAULT_QUALITY;

	//アンチエイリアス
	//this->fontInfo_.quality = ANTIALIASED_QUALITY;
	this->fontInfo_.pitchAndFamily = DEFAULT_PITCH || FF_DONTCARE;

	LPD3DXFONT font = NULL;

	HRESULT hr = D3DXCreateFont(sys::Device::GetInst().GetRef(),
		this->fontInfo_.height,
		this->fontInfo_.width,
		FW_NORMAL,
		this->fontInfo_.mipLevels,
		this->fontInfo_.italic,
		SHIFTJIS_CHARSET,
		this->fontInfo_.outputPrecision,
		this->fontInfo_.quality,
		this->fontInfo_.pitchAndFamily,
		this->fontInfo_.pFacename.c_str(),
		&font);

	if(FAILED(hr)){
		throw std::runtime_error("フォントの初期化に失敗しました");
	}
	if(!font){
		throw std::runtime_error("フォントのポインタがnullです");
	}

	this->fontInfo_.ppFont = boost::intrusive_ptr<ID3DXFont>(font, false);

}

void Font::DrawString(String str){
	//throw std::runtime_error("未実装");
	RECT rect = {100,100,0,0};
	const int nullEnd = -1;
	this->fontInfo_.ppFont->DrawText(NULL, str.c_str(), nullEnd, &rect, DT_LEFT | DT_NOCLIP,
		D3DCOLOR_ARGB(255, 0, 0, 0));
}

}