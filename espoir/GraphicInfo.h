#pragma once




namespace espoir{
struct GraphicInfo{
	//Direct3D
	//ComPtr<IDirect3D9>::type direct3D;
	boost::intrusive_ptr<IDirect3D9> direct3D;

	//デバイス
	//ComPtr<IDirect3DDevice9>::type d3Device;
	boost::intrusive_ptr<IDirect3DDevice9> d3Device;

	//バックバッファサーフェス
	//ComPtr<IDirect3DSurface9>::type backBuf;
	boost::intrusive_ptr<IDirect3DSurface9> backBuf;

	//DiretcXのウィンドウハンドル
	//HWND hWnd;
};
}