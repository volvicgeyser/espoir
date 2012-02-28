
#include"stdafx.h"
#include"DDevice.h"
#include"debug.h"

#include"Resource.h"

namespace espoir{

bool espoir::DDevice::Init(){
		//�߂�l�@�������ɐ�������=true : ���s=false
		bool result = true;

		//DirectX�̊֐������s���ɔ��������G���[�R�[�h
		HRESULT err_code;

		//IDirect3D�I�u�W�F�N�g�C���X�^���X�̎擾
		direct3D_.Attach( Direct3DCreate9(D3D_SDK_VERSION) );

		::D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		
		//�f�B�X���v�C���[�h�\����
		::D3DDISPLAYMODE d3ddm;
		ZeroMemory(&d3ddm, sizeof(d3ddm));

		//�f�B�X�v���C���[�h�̎擾
		err_code = direct3D_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		//�f�B�X�v���C���[�h�擾���̃G���[�`�F�b�N
		if(FAILED(err_code)){
			espoir::DOut dout;
			dout << _T("GetAdapterDisplayMode�����s���܂���") << std::endl;
		}
		d3dpp.BackBufferFormat =  d3ddm.Format;//D3DFMT_R5G6B5;//D3DFMT_UNKNOWN;//d3ddm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = TRUE;

		//�A�v���P�[�V�������o�b�N�o�b�t�@�𒼐ڃ��b�N
		d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

		this->form_ = SPForm(new Form(DirectX));
		this->form_->Show();

		//HEL(�\�t�g�E�F�A�G�~�����[�V����)�Ńf�o�C�X����
		HRESULT hResult;
		hResult = direct3D_->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->form_->GetHandle(),

			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3Device_);
					//D3DPRESENTFLAG_LOCKABLE_BACKBUFFER, &d3dpp, &d3Device_);
		
		//�f�o�C�X�������̃G���[�`�F�b�N
		if(FAILED(hResult))
		{
			DOut dout;
			dout << _T("Error: HEL�ł̏������Ɏ��s���܂���") << std::endl;
			switch(hResult){
				case D3DERR_INVALIDCALL:
					dout << _T("���\�b�h�̌Ăяo���������B�p�����[�^�Ɉُ킩�������`�F�b�N���Ă�������") << std::endl;
					break;
				case D3DERR_NOTAVAILABLE:
					dout << _T("���̃f�o�C�X�́A�₢���킹���e�N�j�b�N���T�|�[�g���Ă��܂���") << std::endl;
					break;
				case D3DERR_OUTOFVIDEOMEMORY:
					dout << _T("Direct3D ���������s���̂ɏ\���ȃf�B�X�v���C ������������܂���") << std::endl;
					break;
			}
		}

		//DirectX�̏������Ɏ��s���Ă�����false��Ԃ�
		if(espoir::DDevice::direct3D_ == 0)
			result = false;


		//Grahpcs�̏�����
		SPGraphicInfo gInfo(new GraphicInfo());
		gInfo->d3Device = this->d3Device_;
		gInfo->direct3D = this->direct3D_;

		SPDXInfo dxInfo(new DXInfo);
		if(dxInfo->g.get() == NULL)
			dxInfo->g = SPGraphic(new Graphic(gInfo));

		//GameWindow�̏�����
		if(this->gm_.get() == NULL)
			this->gm_ = SPGameMain(new GameMain(dxInfo));

		return result;
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
				DOut dout;
				dout << _T("GameMain������������Ă��܂���") << DSTM << std::endl;
			}
		}
	}

}






}