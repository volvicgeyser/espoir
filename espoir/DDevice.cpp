
#include"stdafx.h"
#include"DDevice.h"
#include"debug.h"
#include"Resource.h"
ComPtr<IDirect3D9>::type espoir::DDevice::mDirect3D;
//::_com_ptr_t<::_com_IIID<IDirect3D9, &__uuidof(IDirect3D9)>>  espoir::DDevice::mDirect3D;
ComPtr<IDirect3DDevice9>::type espoir::DDevice::mD3Device;
//::_com_ptr_t<::_com_IIID<IDirect3DDevice9, &__uuidof(IDirect3DDevice9)>> espoir::DDevice::mD3Device;

HWND espoir::DDevice::hWnd = NULL;



void espoir::DDevice::SetHWND(HWND hWnd){

	//設定しようとしたウィンドウハンドルがNULLかどうか
	if(hWnd == NULL){
		DOut dout;
		dout << _T("Hwnd is null") << std::endl;
	}

	//ウィンドウハンドルの設定
	DDevice::hWnd = hWnd;
}
bool espoir::DDevice::Init(){
		//戻り値　初期化に成功した=true : 失敗=false
		bool result = true;

		//DirectXの関数を実行時に発生したエラーコード
		HRESULT err_code;

		//IDirect3Dオブジェクトインスタンスの取得
		mDirect3D.Attach( Direct3DCreate9(D3D_SDK_VERSION) );


		::D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		
		//ディスレプイモード構造体
		::D3DDISPLAYMODE d3ddm;
		ZeroMemory(&d3ddm, sizeof(d3ddm));

		//ディスレプイモードの取得
		err_code = mDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		//ディスプレイモード取得時のエラーチェック
		if(FAILED(err_code)){
			espoir::DOut dout;
			dout << _T("GetAdapterDisplayModeが失敗しました") << std::endl;
		}
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//d3ddm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = TRUE;


		//インスタンスハンドルの取得
		HINSTANCE hInst = GetModuleHandle(NULL);

		//インスタンスハンドル取得時のエラーチェック
		if(!hInst){
			DOut dout;
			dout << _T("インスタンスハンドルの取得に失敗しました error: code") << std::endl;
			dout << GetLastError() << std::endl;
		}


		//ウィンドウクラス名とウィンドウのタイトル名
		String dClass = _T("espoir");
		String title = _T("Directx espoir");
		
		
		//ウィンドウクラスの登録
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= espoir::DWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInst;
		wcex.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDI_ESPOIR));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ESPOIR);
		wcex.lpszClassName	= dClass.c_str();
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		ATOM atom = RegisterClassEx(&wcex);


		//プログラム起動時のオプションで指定されたウィンドウの状態を取得
		STARTUPINFO Info;
		GetStartupInfo(&Info);
		int nCmdShow = Info.wShowWindow;


		//メインウィンドウの生成
		hWnd = CreateWindow(dClass.c_str() , title.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst, NULL);
		
		//コマンドラインの取得
		LPTSTR cmd = GetCommandLine();

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		//メインウィンドウ生成時のエラーチェック
		if(!hWnd){
			DOut dout;
			dout << _T("DirectX、Windowの生成に失敗しました") << std::endl;
			dout << GetLastError() << std::endl;
		}

		//HEL(ソフトウェアエミュレーション)でデバイス生成
		HRESULT hResult;
		hResult = mDirect3D->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mD3Device);
		
		//デバイス生成時のエラーチェック
		if(FAILED(hResult))
		{
			espoir::DOut dout;
			dout << _T("Error: HELでの初期化に失敗しました") << std::endl;
			switch(hResult){
				case D3DERR_INVALIDCALL:
					dout << _T("メソッドの呼び出しが無効。パラメータに異常か無いかチェックしてください") << std::endl;
					break;
				case D3DERR_NOTAVAILABLE:
					dout << _T("このデバイスは、問い合わせたテクニックをサポートしていません") << std::endl;
					break;
				case D3DERR_OUTOFVIDEOMEMORY:
					dout << _T("Direct3D が処理を行うのに十分なディスプレイ メモリがありません") << std::endl;
					break;
			}
		}

		//DirectXの初期化に失敗していたらfalseを返す
		if(espoir::DDevice::mDirect3D == 0)
			result = false;

		return result;
}

LRESULT CALLBACK espoir::DWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){

		//ウィンドウが破棄された
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		//ウィンドウが再描画された
		case WM_PAINT:
		
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}
	return 0;
}

void espoir::DDevice::DMainLoop(){
	
	//メッセージ
	MSG msg;
	
	//インスタンスハンドルの取得
	HINSTANCE hInst = GetModuleHandle(NULL);
	
	//アクセラレータ（ショートカットキー）テーブルを取得
	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_ESPOIR));

	// メイン メッセージ ループ:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}