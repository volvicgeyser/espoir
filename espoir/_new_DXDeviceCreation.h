#pragma once

#include"system.h"
#include"safedelete.h"

namespace espoir{

static void InitPresent(D3DPRESENT_PARAMETERS* d3dpp, const D3DDISPLAYMODE d3ddm){
	if(!d3dpp)
		throw std::runtime_error("d3dpp����ł�");

	d3dpp->BackBufferFormat = d3ddm.Format;
	d3dpp->BackBufferCount = 1;
	d3dpp->SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp->Windowed = TRUE;

	//�A�v���P�[�V�������o�b�N�o�b�t�@�𒼐ڃ��b�N
	d3dpp->Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
}

template<class ObjType>
class DXDeviceCreation{
public:
	static ObjType* Create(){
		using namespace std;
		IDirect3DDevice9* device = NULL;

		//�f�B�X�v���C���[�h�\����
		D3DDISPLAYMODE d3ddm;

		//0�ŏ�����
		ZeroMemory(&d3ddm, sizeof(d3ddm));

		//�f�B�X�v���C���[�h�̎擾
		const HRESULT displaymode_err = sys::Direct3D::GetInst()->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);


		//�f�B�X�v���C���[�h�̃G���[�`�F�b�N
		if(FAILED(displaymode_err))
			throw std::runtime_error("GetAdapterDisplayMode�����s���܂���");

		//�v���[���g�p�����[�^
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		//�f�B�X�v���C���[�h�̐ݒ�
		InitPresent(&d3dpp, d3ddm);

		const HRESULT hResult = sys::Direct3D::GetInst()->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, sys::Form::GetInst()->GetHandle(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device);

		//���[�U�[�̎��s�ŃG���[�ɂȂ�\�����\���ɍl������̂�
		//�_�C�A���O���o���ď������Ɏ��s�������Ƃ�`����
		if(FAILED(hResult))
			MessageBox(NULL, _T("HAL�ł̏������Ɏ��s���܂���"), _T("err"), MB_OK);

		if(!device)
			throw std::runtime_error("device��NULL�ł�");

		return device;
	}

	//Device�̔j��
	static void Destroy(ObjType* device) {
		safe_release(device);
	}
};

}
