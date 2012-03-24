#pragma once




namespace espoir{
struct GraphicInfo{
	//Direct3D
	//ComPtr<IDirect3D9>::type direct3D;
	boost::intrusive_ptr<IDirect3D9> direct3D;

	//�f�o�C�X
	//ComPtr<IDirect3DDevice9>::type d3Device;
	boost::intrusive_ptr<IDirect3DDevice9> d3Device;

	//�o�b�N�o�b�t�@�T�[�t�F�X
	//ComPtr<IDirect3DSurface9>::type backBuf;
	boost::intrusive_ptr<IDirect3DSurface9> backBuf;

	//DiretcX�̃E�B���h�E�n���h��
	//HWND hWnd;
};
}