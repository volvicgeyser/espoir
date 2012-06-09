#pragma once

//#include "system.h"
//#include"form.h"
//#include"DXFormCreation.h"
//#include"DX3D9Creation.h"
//#include"Singleton.h"
#include"system.h"
#include"debug.h"
namespace espoir{

static void InitPresent(D3DPRESENT_PARAMETERS* d3dpp, const D3DDISPLAYMODE d3ddm){
	if(!d3dpp)
		throw std::runtime_error("d3dpp����ł�");

	d3dpp->BackBufferFormat = d3ddm.Format;
//    d3dpp->BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp->BackBufferCount = 1;
	d3dpp->SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp->Windowed = TRUE;
//    d3dpp->EnableAutoDepthStencil = TRUE;
//    d3dpp->AutoDepthStencilFormat = D3DFMT_D16;

	//�A�v���P�[�V�������o�b�N�o�b�t�@�𒼐ڃ��b�N
	d3dpp->Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
}

//�f�o�C�X�������̃G���[�`�F�b�N
static inline void CheckDeviceErr(const HRESULT hResult){
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
}


template <class ObjType>
class DXDeviceCreation{
//typedef boost::intrusive_ptr<ObjType> SPObjType;
typedef ComPtr<ObjType> SPObjType;
public:
	static SPObjType Create(){

		using namespace std;
		//Device����
		IDirect3DDevice9* tmp_d3Device = NULL;
		//ObjType* tmp_d3Device = NULL;

		//�f�B�X�v���C���[�h�\����
		::D3DDISPLAYMODE d3ddm;
		ZeroMemory(&d3ddm, sizeof(d3ddm));

		//�f�B�X�v���C���[�h�̎擾
		const HRESULT err_code = sys::Direct3D::GetInst()->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		//�f�B�X�v���C���[�h�擾���̃G���[�`�F�b�N
		if(FAILED(err_code)){
			DOut dout;
			dout << _T("GetAdapterDisplayMode�����s���܂���") << std::endl;
		}

		//�v���[���g�p�����[�^
		::D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		//�v���[���g�p�����[�^�̏�����
		InitPresent(&d3dpp, d3ddm);


		//�f�o�C�X�̍쐬
		const HRESULT hResult = sys::Direct3D::GetInst()->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, sys::Form::GetInst()->GetHandle(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &tmp_d3Device);

		//�f�o�C�X�������̃G���[�`�F�b�N
		CheckDeviceErr(hResult);

		//zbuffer�̐ݒ�
//        tmp_d3Device->SetRenderState(D3DRS_ZENABLE, TRUE);	

		//�A���r�G���g
		tmp_d3Device->SetRenderState(D3DRS_AMBIENT, 0xffffffff );

		const SPObjType obj = SPObjType(tmp_d3Device);

		return obj;
	}
private:
};

}
