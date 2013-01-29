#include "StdAfx.h"
#include "Graphic.h"
#include "debug.h"
#include "intrusive_func.h"
//#include "Singleton.h"
//#include "DXDeviceCreation.h"
#include "system.h"
#include "vertex.h"

namespace espoir{

Graphic::Graphic()
{
}


void Graphic::DrawCircle(const RECT& rect)
{
	//デバイスコンテキスト
	HDC hDC;

	//if(this->gInfo_->backBuf != NULL){
	const HRESULT hr = sys::Backbuf::GetInst()->GetDC(&hDC);
//        const HRESULT hr = this->gInfo_->backBuf->GetDC(&hDC);

	//正しくDC取得できたかtest
	EXPECT_HRESULT_SUCCEEDED(hr);

	if(hr == S_OK){

		//二次元の円を描画
		const BOOL rEllipse = Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
			
		//円が正しく描画できているかどうかテスト
		EXPECT_NE(rEllipse, FALSE);
 			
		sys::Backbuf::GetInst()->ReleaseDC(hDC);
//        this->gInfo_->backBuf->ReleaseDC(hDC);
	}
	else{
		//DOut dout;
		//dout << _T("Error: ") << hr << _T(" 円の描画に失敗しました ") << DSTM << std::endl;

		//throw std::runtime_error("円の描画に失敗しました");

		const char* str = "円の描画に失敗しました";
		//型チェックテスト
		typedef ::testing::Types<long> testTypes;
			TYPED_TEST_CASE(getdc_result_test, testTypes);

		switch(hr){
			case E_FAIL:
				throw std::runtime_error( (boost::format("%1% E_FAIL") % str).str() );
				break;
			case D3DERR_INVALIDCALL :
				throw std::runtime_error( (boost::format("%1% 無効な呼び出し") % str).str() );
				break;
		}
	}
}

//画像のロード
Graphic::SPTexture Graphic::LoadGraphic(const String& filename)
{
	//ロードされた画像ファイル名を覚えておく
	static std::vector<String> loadedName;

	if(std::find( loadedName.begin(), loadedName.end(), filename) != loadedName.end())
	{
		//既にロード済みの画像データは無視する
		SPTexture spTexture(NULL);
		return spTexture;
	}
	
	//ロードされたファイル名を保存する
	loadedName.push_back(filename);

	LPDIRECT3DTEXTURE9 texture = NULL;
	if(FAILED(D3DXCreateTextureFromFile( sys::Device::GetInst().GetRef(), filename.c_str(), &texture )))
	{
		DOut dout;
		dout << _T("画像の読み込みに失敗しました") << DSTM << std::endl;
		dout << _T("ファイル名:") << filename << std::endl;
		throw std::runtime_error("画像の読み込みに失敗しました");
	}

	//const ComPtr<IDirect3DTexture9> spTexture(texture);
	SPTexture spTexture(texture, false);

	return spTexture;
}

//四角形の描画
void Graphic::DrawRect(){
}

void Graphic::SetRect(const RECT& rect){
}

//画像を指定の位置に描画
void Graphic::DrawGraphic(const SPTexture& spTexture, const RECT& rect)
{
	if(!spTexture)
	{
		return;
	}
	const D3DXVECTOR3 vec3Center(0, 0, 0);
	const D3DXVECTOR3 vec3Position(220, 170, 0);

	typedef std::map<SPTexture, SPSprite> SpriteMap;

	SPSprite spSprite;
	static SpriteMap spriteMap;
	if( spriteMap.find(spTexture) == spriteMap.end() )
	{
		//該当のテクスチャーデータが存在しない場合
		
		LPD3DXSPRITE sprite = NULL;

		if(FAILED(D3DXCreateSprite(sys::Device::GetInst().GetRef(), &sprite)))
		{
			DOut dout;
			dout << _T("スプライトの初期化に失敗しました") << DSTM;
		}
		spSprite = SPSprite(sprite, false);

		//テクスデータをキーにスプライトを格納
		spriteMap[spTexture] = spSprite;
	}
	else
	{
		//該当のテクスチャーデータが存在する場合
		spSprite = spriteMap[spTexture];
	}

	
	RECT lrect = rect;

	//サイズの高さか幅が0なら画像サイズを自動取得
	if(rect.bottom == 0 || rect.right == 0)
	{
		D3DSURFACE_DESC desc;
		if(spTexture->GetLevelDesc(0, &desc) )
		{
			//画像サイズの取得に失敗
		}
		else
		{
			lrect.bottom = desc.Height;
			lrect.right = desc.Width;
		}
	}

	spSprite->Begin(D3DXSPRITE_ALPHABLEND);
    spSprite->Draw( spTexture.get(),
                   &lrect,
                   &vec3Center,
                   &vec3Position,
                   0xFFFFFFFF);
	spSprite->End();
}

Graphic::~Graphic(void)
{
}


}
