#include "StdAfx.h"
#include "Graphic.h"
#include "debug.h"
#include "intrusive_func.h"
#include "Singleton.h"
#include "DXDeviceCreation.h"

namespace espoir{

	namespace sys{
		typedef SPSingleton<IDirect3DDevice9, DXDeviceCreation, boost::intrusive_ptr> Device;
	}
Graphic::Graphic(SPGraphicInfo gInfo)
{
	if(gInfo_ == NULL)
		this->gInfo_ = gInfo;

	LPDIRECT3DSURFACE9 tmp_backBuf;
	//IDirect3DSurface9* tmp_bb = this->gInfo_->backBuf.get();
	//const HRESULT hr = this->gInfo_->d3Device->GetBackBuffer(
	//		0, 0, D3DBACKBUFFER_TYPE_MONO, &tmp_backBuf);
	const HRESULT hr = sys::Device::GetInst()->GetBackBuffer(
		0, 0, D3DBACKBUFFER_TYPE_MONO, &tmp_backBuf);

	//これから初期化するので中身はNULLのはず
	//NULLかどうかチェック

	//EXPECT_EQ(this->gInfo_->backBuf, NULL);

	
	//static_cast<LPDIRECT3DSURFACE9>(this->gInfo_->backBuf.get());

	this->gInfo_->backBuf = tmp_backBuf;

	if(FAILED(hr)){
		DOut dout;
		dout << _T("BackBufferの初期化に失敗しました ") << DSTM << std::endl;
	}
	
}


void Graphic::DrawCircle(RECT rect)
{
	//if(!this->gInfo_->d3Device) return;
	HDC hDC;
	//const HRESULT hrClear = this->gInfo_->d3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 50), 1.0f, 0);
	const HRESULT hrClear = sys::Device::GetInst()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 50), 1.0f, 0);
	//正しく画面クリアされたかどうかtest
	EXPECT_HRESULT_SUCCEEDED(hrClear);

	if(this->gInfo_->backBuf != NULL){
		const HRESULT hr = this->gInfo_->backBuf->GetDC(&hDC);

		//正しくDC取得できたかtest
		EXPECT_HRESULT_SUCCEEDED(hr);

		if(hr == S_OK){

			//二次元の円を描画
			const BOOL rEllipse = Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
			
			//円が正しく描画できているかどうかテスト
			EXPECT_NE(rEllipse, FALSE);
 			
			this->gInfo_->backBuf->ReleaseDC(hDC);
			DOut dout;

			//次のバッファのコンテンツをプレゼンテーション
			//this->gInfo_->d3Device->Present(NULL, NULL, NULL, NULL);
			sys::Device::GetInst()->Present(NULL, NULL, NULL, NULL);
		}
		else{
			DOut dout;
			dout << _T("Error: ") << hr << _T(" 円の描画に失敗しました ") << DSTM << std::endl;

			//型チェックテスト
			typedef ::testing::Types<long> testTypes;
			TYPED_TEST_CASE(getdc_result_test, testTypes);

			switch(hr){
				case E_FAIL:
					dout << _T("E_FAIL");
					break;
				case D3DERR_INVALIDCALL :
					dout << _T("無効な呼び出し");
					break;
			}
		}

	}
	else{
		DOut dout;
		dout << _T("backBufが初期化されていません ") << DSTM << std::endl;
	}
}

Graphic::~Graphic(void)
{
}


}
