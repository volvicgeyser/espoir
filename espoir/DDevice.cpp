
#include"stdafx.h"
#include"DDevice.h"
#include"debug.h"
//#include"singleton.h"
#include"Resource.h"
//#include"DXFormCreation.h"
//#include"DX3D9Creation.h"
//#include"DXDeviceCreation.h"
#include"system.h"
#include"new.h"
namespace espoir{

}

bool espoir::DDevice::Init(){
		//�߂�l�@�������ɐ�������=true : ���s=false
		//bool result = true;

		//DirectX�̃��C���E�B���h�E�𐶐�
		typedef Singleton<Form, DXFormCreation> SingleDXForm;
		SingleDXForm::GetInst()->Show();

		//GameWindow�̏�����
		if(this->gm_ == NULL)
			this->gm_ = boost::make_shared<GameMain>();

		return true;
}

void espoir::DDevice::DMainLoop(){
	
	//���b�Z�[�W
	MSG msg;
	
	//�C���X�^���X�n���h���̎擾
	const HINSTANCE hInst = GetModuleHandle(NULL);
	
	//�A�N�Z�����[�^�i�V���[�g�J�b�g�L�[�j�e�[�u�����擾
	const HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_ESPOIR));

	while(TRUE){
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)){
			if(!GetMessage(&msg, NULL, 0, 0))
				break;
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else{
			if(this->gm_ != NULL){
				this->gm_->Render();
				this->gm_->Update();
			}
			else{
				throw std::runtime_error("GameMain������������Ă��܂���");
			}
		}
	}

}





