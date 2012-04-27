#pragma once
#include"form.h"
#include"GameMain.h"
#include"GraphicInfo.h"
#include"intrusive_func.h"

//DirectX�̏�����������N���X


namespace espoir{

class Form;
	
LRESULT CALLBACK DWndProc(HWND, UINT, WPARAM, LPARAM);

//Form�̃X�}�[�g�|�C���^��
SP_TDEF(Form);

SP_TDEF(GameMain);
SP_TDEF(GraphicInfo);
SP_TDEF(DXInfo);

//DirectX�̏�����������N���X

//<summary>DDevice�R�����g</summary>
class DDevice{
private:
	//Direct3D
	//ComPtr<IDirect3D9>::type direct3D_;
	//boost::intrusive_ptr<IDirect3D9> direct3D_;

	//�f�o�C�X
	//ComPtr<IDirect3DDevice9>::type d3Device_;
	boost::intrusive_ptr<IDirect3DDevice9> d3Device_;

	//Direct3D, �f�o�C�X
	//SPGrahpicInfo ginfo_;

	//DirectX�̃��C���ɂȂ�t�H�[���E�B���h�E
	//SPForm form_;

	SPGameMain gm_;
	

public:

	//�E�B���h�E�n���h���̐ݒ�
	//void SetHWND(HWND hWnd);

	//DirectX�̏�����
	bool Init();

	//DiretX�̃��C�����[�v
	void DMainLoop();
};



}