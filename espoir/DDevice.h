#pragma once
namespace espoir{
	//typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> String;


	
	LRESULT CALLBACK DWndProc(HWND, UINT, WPARAM, LPARAM);
	

//DirectX�̏�����������N���X
class DDevice{
private:
	//�R���X�g���N�^�̎��s�֎~
	DDevice(){}

	//�R�s�[�R���X�g���N�^�֎~
	DDevice(const DDevice& p){}
	
	//Direct3D
	static ComPtr<IDirect3D9>::type mDirect3D;


	//static ::_com_ptr_t<::_com_IIID<IDirect3D9, &__uuidof(IDirect3D9)>>   mDirect3D;
	//static ::_com_ptr_t<::_com_IIID<IDirect3DDevice9, &__uuidof(IDirect3DDevice9)>> mD3Device;




	//�f�o�C�X
	static ComPtr<IDirect3DDevice9>::type mD3Device;
	
	//���C���E�B���h�E�̃E�B���h�E�n���h��
	static HWND hWnd;
public:

	//�E�B���h�E�n���h���̐ݒ�
	static void SetHWND(HWND hWnd);

	//DirectX�̏�����
	static bool Init();

	//DiretX�̃��C�����[�v
	static void DMainLoop();
};



}