#pragma once

//#include "system.h"
//#include"form.h"
//#include"DXFormCreation.h"
//#include"DX3D9Creation.h"
//#include"Singleton.h"
#include"system.h"
#include"debug.h"
namespace espoir{

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

		::D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		d3dpp.BackBufferFormat =  d3ddm.Format;//D3DFMT_R5G6B5;//D3DFMT_UNKNOWN;//d3ddm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = TRUE;

		//�A�v���P�[�V�������o�b�N�o�b�t�@�𒼐ڃ��b�N
		d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;


		const HRESULT hResult = sys::Direct3D::GetInst()->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, sys::Form::GetInst()->GetHandle(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &tmp_d3Device);

		//�f�o�C�X�������̃G���[�`�F�b�N
		CheckDeviceErr(hResult);

		const SPObjType obj = SPObjType(tmp_d3Device);

		return obj;
	}
private:
	struct DeviceDeleter{
		template<class T>
		void operator()(T* t){
			if(!t){
				throw std::runtime_error("Device������������Ă��Ȃ����A�s���ɍ폜����Ă��܂�");
			}
			t->Release();
		}
	};
};

}
