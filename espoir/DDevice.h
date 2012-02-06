#pragma once
namespace espoir{
	//typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> String;


	
	LRESULT CALLBACK DWndProc(HWND, UINT, WPARAM, LPARAM);
	

//DirectXの初期化をするクラス
class DDevice{
private:
	//コンストラクタの実行禁止
	DDevice(){}

	//コピーコンストラクタ禁止
	DDevice(const DDevice& p){}
	
	//Direct3D
	static ComPtr<IDirect3D9>::type mDirect3D;


	//static ::_com_ptr_t<::_com_IIID<IDirect3D9, &__uuidof(IDirect3D9)>>   mDirect3D;
	//static ::_com_ptr_t<::_com_IIID<IDirect3DDevice9, &__uuidof(IDirect3DDevice9)>> mD3Device;




	//デバイス
	static ComPtr<IDirect3DDevice9>::type mD3Device;
	
	//メインウィンドウのウィンドウハンドル
	static HWND hWnd;
public:

	//ウィンドウハンドルの設定
	static void SetHWND(HWND hWnd);

	//DirectXの初期化
	static bool Init();

	//DiretXのメインループ
	static void DMainLoop();
};



}