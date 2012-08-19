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
	//ÉfÉoÉCÉXÉRÉìÉeÉLÉXÉg
	HDC hDC;

	//if(this->gInfo_->backBuf != NULL){
	const HRESULT hr = sys::Backbuf::GetInst()->GetDC(&hDC);
//        const HRESULT hr = this->gInfo_->backBuf->GetDC(&hDC);

	//ê≥ÇµÇ≠DCéÊìæÇ≈Ç´ÇΩÇ©test
	EXPECT_HRESULT_SUCCEEDED(hr);

	if(hr == S_OK){

		//ìÒéüå≥ÇÃâ~Çï`âÊ
		const BOOL rEllipse = Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
			
		//â~Ç™ê≥ÇµÇ≠ï`âÊÇ≈Ç´ÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©ÉeÉXÉg
		EXPECT_NE(rEllipse, FALSE);
 			
		sys::Backbuf::GetInst()->ReleaseDC(hDC);
//        this->gInfo_->backBuf->ReleaseDC(hDC);
	}
	else{
		//DOut dout;
		//dout << _T("Error: ") << hr << _T(" â~ÇÃï`âÊÇ…é∏îsÇµÇ‹ÇµÇΩ ") << DSTM << std::endl;

		//throw std::runtime_error("â~ÇÃï`âÊÇ…é∏îsÇµÇ‹ÇµÇΩ");

		const char* str = "â~ÇÃï`âÊÇ…é∏îsÇµÇ‹ÇµÇΩ";
		//å^É`ÉFÉbÉNÉeÉXÉg
		typedef ::testing::Types<long> testTypes;
			TYPED_TEST_CASE(getdc_result_test, testTypes);

		switch(hr){
			case E_FAIL:
				throw std::runtime_error( (boost::format("%1% E_FAIL") % str).str() );
				break;
			case D3DERR_INVALIDCALL :
				throw std::runtime_error( (boost::format("%1% ñ≥å¯Ç»åƒÇ—èoÇµ") % str).str() );
				break;
		}
	}
}

//éläpå`ÇÃï`âÊ
void Graphic::DrawRect(){

}

void Graphic::SetRect(const RECT& rect){
}

Graphic::~Graphic(void)
{
}


}
