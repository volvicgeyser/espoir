#include "StdAfx.h"
#include "Graphic.h"
#include "debug.h"
#include "intrusive_func.h"
//#include "Singleton.h"
//#include "DXDeviceCreation.h"
#include "system.h"
namespace espoir{

Graphic::Graphic(SPGraphicInfo gInfo)
{
	if(gInfo_ == NULL)
		this->gInfo_ = gInfo;

	LPDIRECT3DSURFACE9 tmp_backBuf;

	const HRESULT hr = sys::Device::GetInst()->GetBackBuffer(
		0, 0, D3DBACKBUFFER_TYPE_MONO, &tmp_backBuf);

	//‚±‚ê‚©‚ç‰Šú‰»‚·‚é‚Ì‚Å’†g‚ÍNULL‚Ì‚Í‚¸
	//NULL‚©‚Ç‚¤‚©ƒ`ƒFƒbƒN

	//EXPECT_EQ(this->gInfo_->backBuf, NULL);

	
	//static_cast<LPDIRECT3DSURFACE9>(this->gInfo_->backBuf.get());

	this->gInfo_->backBuf = tmp_backBuf;

	if(FAILED(hr)){
		throw std::runtime_error("BackBuffer‚Ì‰Šú‰»‚É¸”s‚µ‚Ü‚µ‚½");
		//(*debug::Dout::GetInst()) << _T("BackBuffer‚Ì‰Šú‰»‚É¸”s‚µ‚Ü‚µ‚½");
	}
}


void Graphic::DrawCircle(RECT rect)
{
	//if(!this->gInfo_->d3Device) return;
	HDC hDC;

	if(this->gInfo_->backBuf != NULL){
		const HRESULT hr = this->gInfo_->backBuf->GetDC(&hDC);

		//³‚µ‚­DCæ“¾‚Å‚«‚½‚©test
		EXPECT_HRESULT_SUCCEEDED(hr);

		if(hr == S_OK){

			//“ñŸŒ³‚Ì‰~‚ğ•`‰æ
			const BOOL rEllipse = Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
			
			//‰~‚ª³‚µ‚­•`‰æ‚Å‚«‚Ä‚¢‚é‚©‚Ç‚¤‚©ƒeƒXƒg
			EXPECT_NE(rEllipse, FALSE);
 			
			this->gInfo_->backBuf->ReleaseDC(hDC);
		}
		else{
			//DOut dout;
			//dout << _T("Error: ") << hr << _T(" ‰~‚Ì•`‰æ‚É¸”s‚µ‚Ü‚µ‚½ ") << DSTM << std::endl;

			//throw std::runtime_error("‰~‚Ì•`‰æ‚É¸”s‚µ‚Ü‚µ‚½");

			const char* str = "‰~‚Ì•`‰æ‚É¸”s‚µ‚Ü‚µ‚½";
			//Œ^ƒ`ƒFƒbƒNƒeƒXƒg
			typedef ::testing::Types<long> testTypes;
			TYPED_TEST_CASE(getdc_result_test, testTypes);

			switch(hr){
				case E_FAIL:
					throw std::runtime_error( (boost::format("%1% E_FAIL") % str).str() );
					break;
				case D3DERR_INVALIDCALL :
					throw std::runtime_error( (boost::format("%1% –³Œø‚ÈŒÄ‚Ño‚µ") % str).str() );
					break;
			}
		}

	}
	else{
		//DOut dout;
		//dout << _T("backBuf‚ª‰Šú‰»‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ ") << DSTM << std::endl;
		throw std::runtime_error("backBuf‚ª‰Šú‰»‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ");
	}
}

Graphic::~Graphic(void)
{
}


}
