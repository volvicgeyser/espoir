#pragma once

namespace espoir{
struct GraphicInfo{
	//Direct3D
	ComPtr<IDirect3D9>::type direct3D;

	//�f�o�C�X
	ComPtr<IDirect3DDevice9>::type d3Device;

	//DiretcX�̃E�B���h�E�n���h��
	HWND hWnd;
};
}