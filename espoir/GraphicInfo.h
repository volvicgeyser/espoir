#pragma once

namespace espoir{
struct GraphicInfo{
	//Direct3D
	ComPtr<IDirect3D9>::type direct3D;

	//デバイス
	ComPtr<IDirect3DDevice9>::type d3Device;

	//DiretcXのウィンドウハンドル
	HWND hWnd;
};
}