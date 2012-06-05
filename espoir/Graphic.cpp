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
	//ƒfƒoƒCƒXƒRƒ“ƒeƒLƒXƒg
	HDC hDC;

	//if(this->gInfo_->backBuf != NULL){
	const HRESULT hr = sys::Backbuf::GetInst()->GetDC(&hDC);
//        const HRESULT hr = this->gInfo_->backBuf->GetDC(&hDC);

	//³‚µ‚­DCŽæ“¾‚Å‚«‚½‚©test
	EXPECT_HRESULT_SUCCEEDED(hr);

	if(hr == S_OK){

		//“ñŽŸŒ³‚Ì‰~‚ð•`‰æ
		const BOOL rEllipse = Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
			
		//‰~‚ª³‚µ‚­•`‰æ‚Å‚«‚Ä‚¢‚é‚©‚Ç‚¤‚©ƒeƒXƒg
		EXPECT_NE(rEllipse, FALSE);
 			
		sys::Backbuf::GetInst()->ReleaseDC(hDC);
//        this->gInfo_->backBuf->ReleaseDC(hDC);
	}
	else{
		//DOut dout;
		//dout << _T("Error: ") << hr << _T(" ‰~‚Ì•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½ ") << DSTM << std::endl;

		//throw std::runtime_error("‰~‚Ì•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

		const char* str = "‰~‚Ì•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½";
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

//ŽlŠpŒ`‚Ì•`‰æ
void Graphic::DrawRect(const RECT& rect){

	const int z = 1;

	//ŽlŠpŒ`‚Ìvertex
	const VertexL pt[4] = {
		{rect.left, rect.top, z, 1, 0xFFFF0000},
		{rect.left, rect.bottom, z, 1, 0xFF0000FF},
		{rect.right, rect.bottom, z, 1, 0xFF0000FF},
		{rect.right, rect.top, z, 1, 0xFF0000FF}
	};


	//ŽOŠpŒ`
//    const VertexL pt[3] = {
//        {rect.left, rect.top, z, 1, 0xFFFF0000},
//        {rect.left, rect.bottom, z, 1, 0xFF0000FF},
//        {rect.right, rect.top, z, 1, 0xFF0000FF}
//    };


	//ƒVƒF[ƒ_‚Ìƒf[ƒ^
	EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->SetVertexShader( NULL ));

	//ƒvƒŠƒ~ƒeƒBƒu‚Ì•`‰æ
//    const HRESULT primHR = sys::Device::GetInst()->DrawPrimitiveUP(
//        D3DPT_TRIANGLELIST, 1, pt, sizeof(VertexL)
//        );

	//sys::Device::GetInst()->SetFVF(D3DFVF_CUSTOMVERTEX);

//    sys::Device::GetInst()->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);

//    EXPECT_HRESULT_SUCCEEDED(primHR);
}

Graphic::~Graphic(void)
{
}


}
