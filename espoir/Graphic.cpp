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
	//�f�o�C�X�R���e�L�X�g
	HDC hDC;

	//if(this->gInfo_->backBuf != NULL){
	const HRESULT hr = sys::Backbuf::GetInst()->GetDC(&hDC);
//        const HRESULT hr = this->gInfo_->backBuf->GetDC(&hDC);

	//������DC�擾�ł�����test
	EXPECT_HRESULT_SUCCEEDED(hr);

	if(hr == S_OK){

		//�񎟌��̉~��`��
		const BOOL rEllipse = Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
			
		//�~���������`��ł��Ă��邩�ǂ����e�X�g
		EXPECT_NE(rEllipse, FALSE);
 			
		sys::Backbuf::GetInst()->ReleaseDC(hDC);
//        this->gInfo_->backBuf->ReleaseDC(hDC);
	}
	else{
		//DOut dout;
		//dout << _T("Error: ") << hr << _T(" �~�̕`��Ɏ��s���܂��� ") << DSTM << std::endl;

		//throw std::runtime_error("�~�̕`��Ɏ��s���܂���");

		const char* str = "�~�̕`��Ɏ��s���܂���";
		//�^�`�F�b�N�e�X�g
		typedef ::testing::Types<long> testTypes;
			TYPED_TEST_CASE(getdc_result_test, testTypes);

		switch(hr){
			case E_FAIL:
				throw std::runtime_error( (boost::format("%1% E_FAIL") % str).str() );
				break;
			case D3DERR_INVALIDCALL :
				throw std::runtime_error( (boost::format("%1% �����ȌĂяo��") % str).str() );
				break;
		}
	}
}

//�l�p�`�̕`��
void Graphic::DrawRect(){

}

void Graphic::SetRect(const RECT& rect){
}

Graphic::~Graphic(void)
{
}


}
