#include"stdafx.h"
#include"GameMain.h"
#include"debug.h"
#include"xfile.h"
#include"system.h"
namespace espoir{


GameMain::GameMain(SPDXInfo info){
	this->dinfo_ = info;

	XFile(_T("../../x/kabotha_sensi.x"));
}

//�Q�[���̕`��
void GameMain::Render(){
	
	//�`��J�n
	const HRESULT hrClear = sys::Device::GetInst()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 50), 1.0f, 0);
	

	//3D�̕`��
	if(SUCCEEDED(sys::Device::GetInst()->BeginScene())){
		//�`����̐ݒ�
		D3DXMATRIXA16 world;
		D3DXMatrixRotationY(&world, sys::Time::GetInst()->GetStartTime() / 1000.0f);
		sys::Device::GetInst()->SetTransform(D3DTS_WORLD, &world);
		D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 view;
		D3DXMatrixLookAtLH(&view, &vEyePt, &vLookatPt, &vUpVec);
		sys::Device::GetInst()->SetTransform(D3DTS_VIEW, &view);
		D3DXMATRIXA16 proj;
		D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI/ 4,1.0f,1.0f,100.0f);
		sys::Device::GetInst()->SetTransform(D3DTS_PROJECTION, &proj);

		//for(DWORD i = 0; i < numMaterials; i++){
			//sys::Device::GetInst()->SetMaterial( // �}�e���A��);
			//sys::Device::GetInst()->SetTexture( //�e�N�X�`��);
			//���b�V���̃h���[�T�u�Z�b�g
			
		//}
		sys::Device::GetInst()->EndScene();

	}
	
	//��������ʃN���A���ꂽ���ǂ���test
	EXPECT_HRESULT_SUCCEEDED(hrClear);

	//left top right bottom
	const RECT rect = {50, 50, 100, 100};

	if(this->dinfo_->g != NULL)
		this->dinfo_->g->DrawCircle(rect);
	else{
		DOut dout;
		dout << _T("graphic��NULL�ł� ") << DSTM << std::endl;
	}

	//���̃o�b�t�@�̃R���e���c���v���[���e�[�V����
	sys::Device::GetInst()->Present(NULL, NULL, NULL, NULL);
}

//�Q�[���̃A�b�v�f�[�g����
void GameMain::Update(){
	
}


}
