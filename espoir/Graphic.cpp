#include "StdAfx.h"
#include "Graphic.h"
#include "debug.h"
#include "intrusive_func.h"
//#include "Singleton.h"
//#include "DXDeviceCreation.h"
#include "system.h"
#include "vertex.h"

namespace espoir{

Graphic::Graphic(SPGraphicInfo gInfo)
{
	if(gInfo_ == NULL)
		this->gInfo_ = gInfo;

	LPDIRECT3DSURFACE9 tmp_backBuf;

	const HRESULT hr = sys::Device::GetInst()->GetBackBuffer(
		0, 0, D3DBACKBUFFER_TYPE_MONO, &tmp_backBuf);

	//これから初期化するので中身はNULLのはず
	//NULLかどうかチェック

	//EXPECT_EQ(this->gInfo_->backBuf, NULL);

	
	//static_cast<LPDIRECT3DSURFACE9>(this->gInfo_->backBuf.get());

	this->gInfo_->backBuf = tmp_backBuf;

	if(FAILED(hr)){
		throw std::runtime_error("BackBufferの初期化に失敗しました");
		//(*debug::Dout::GetInst()) << _T("BackBufferの初期化に失敗しました");
	}
}


void Graphic::DrawCircle(const RECT& rect)
{
	//if(!this->gInfo_->d3Device) return;
	HDC hDC;

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
	else{
		//DOut dout;
		//dout << _T("backBufが初期化されていません ") << DSTM << std::endl;
		throw std::runtime_error("backBufが初期化されていません");
	}
}

//四角形の描画
void Graphic::DrawRect(const RECT& rect){

	const int z = 1;

	//四角形のvertex
	const VertexL pt[4] = {
		{rect.left, rect.top, z, 1, 0xFFFF0000},
		{rect.left, rect.bottom, z, 1, 0xFF0000FF},
		{rect.right, rect.bottom, z, 1, 0xFF0000FF},
		{rect.right, rect.top, z, 1, 0xFF0000FF}
	};


	//三角形
//    const VertexL pt[3] = {
//        {rect.left, rect.top, z, 1, 0xFFFF0000},
//        {rect.left, rect.bottom, z, 1, 0xFF0000FF},
//        {rect.right, rect.top, z, 1, 0xFF0000FF}
//    };


	//シェーダのデータ
	EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->SetVertexShader( NULL ));

	//プリミティブの描画
	const HRESULT primHR = sys::Device::GetInst()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST, 1, pt, sizeof(VertexL)
		);

	//sys::Device::GetInst()->SetFVF(D3DFVF_CUSTOMVERTEX);

	//sys::Device::GetInst()->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);

	EXPECT_HRESULT_SUCCEEDED(primHR);
}

Graphic::~Graphic(void)
{
}


}
