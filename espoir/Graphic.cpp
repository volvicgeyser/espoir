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

	//���ꂩ�珉��������̂Œ��g��NULL�̂͂�
	//NULL���ǂ����`�F�b�N

	//EXPECT_EQ(this->gInfo_->backBuf, NULL);

	
	//static_cast<LPDIRECT3DSURFACE9>(this->gInfo_->backBuf.get());

	this->gInfo_->backBuf = tmp_backBuf;

	if(FAILED(hr)){
		throw std::runtime_error("BackBuffer�̏������Ɏ��s���܂���");
		//(*debug::Dout::GetInst()) << _T("BackBuffer�̏������Ɏ��s���܂���");
	}
}


void Graphic::DrawCircle(const RECT& rect)
{
	//if(!this->gInfo_->d3Device) return;
	HDC hDC;

	if(this->gInfo_->backBuf != NULL){
		const HRESULT hr = this->gInfo_->backBuf->GetDC(&hDC);

		//������DC�擾�ł�����test
		EXPECT_HRESULT_SUCCEEDED(hr);

		if(hr == S_OK){

			//�񎟌��̉~��`��
			const BOOL rEllipse = Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
			
			//�~���������`��ł��Ă��邩�ǂ����e�X�g
			EXPECT_NE(rEllipse, FALSE);
 			
			this->gInfo_->backBuf->ReleaseDC(hDC);
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
	else{
		//DOut dout;
		//dout << _T("backBuf������������Ă��܂��� ") << DSTM << std::endl;
		throw std::runtime_error("backBuf������������Ă��܂���");
	}
}

//�l�p�`�̕`��
void Graphic::DrawRect(const RECT& rect){

	const int z = 1;

	//�l�p�`��vertex
	const VertexL pt[4] = {
		{rect.left, rect.top, z, 1, 0xFFFF0000},
		{rect.left, rect.bottom, z, 1, 0xFF0000FF},
		{rect.right, rect.bottom, z, 1, 0xFF0000FF},
		{rect.right, rect.top, z, 1, 0xFF0000FF}
	};


	//�O�p�`
//    const VertexL pt[3] = {
//        {rect.left, rect.top, z, 1, 0xFFFF0000},
//        {rect.left, rect.bottom, z, 1, 0xFF0000FF},
//        {rect.right, rect.top, z, 1, 0xFF0000FF}
//    };


	//�V�F�[�_�̃f�[�^
	EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->SetVertexShader( NULL ));

	//�v���~�e�B�u�̕`��
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
