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

	//���ꂩ�珉��������̂Œ��g��NULL�̂͂�
	//NULL���ǂ����`�F�b�N

	//EXPECT_EQ(this->gInfo_->backBuf, NULL);

	
	//static_cast<LPDIRECT3DSURFACE9>(this->gInfo_->backBuf.get());

	this->gInfo_->backBuf = tmp_backBuf;

	if(FAILED(hr)){
		DOut dout;
		dout << _T("BackBuffer�̏������Ɏ��s���܂��� ") << DSTM << std::endl;
	}
	
}


void Graphic::DrawCircle(RECT rect)
{
	//if(!this->gInfo_->d3Device) return;
	HDC hDC;
	//const HRESULT hrClear = this->gInfo_->d3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 50), 1.0f, 0);
	const HRESULT hrClear = sys::Device::GetInst()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 50), 1.0f, 0);
	//��������ʃN���A���ꂽ���ǂ���test
	EXPECT_HRESULT_SUCCEEDED(hrClear);

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
			DOut dout;

			//���̃o�b�t�@�̃R���e���c���v���[���e�[�V����
			//this->gInfo_->d3Device->Present(NULL, NULL, NULL, NULL);
			sys::Device::GetInst()->Present(NULL, NULL, NULL, NULL);
		}
		else{
			DOut dout;
			dout << _T("Error: ") << hr << _T(" �~�̕`��Ɏ��s���܂��� ") << DSTM << std::endl;

			//�^�`�F�b�N�e�X�g
			typedef ::testing::Types<long> testTypes;
			TYPED_TEST_CASE(getdc_result_test, testTypes);

			switch(hr){
				case E_FAIL:
					dout << _T("E_FAIL");
					break;
				case D3DERR_INVALIDCALL :
					dout << _T("�����ȌĂяo��");
					break;
			}
		}

	}
	else{
		DOut dout;
		dout << _T("backBuf������������Ă��܂��� ") << DSTM << std::endl;
	}
}

Graphic::~Graphic(void)
{
}


}
