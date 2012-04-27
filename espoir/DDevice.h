#pragma once
#include"form.h"
#include"GameMain.h"
#include"GraphicInfo.h"
#include"intrusive_func.h"

//DirectXの初期化をするクラス


namespace espoir{

class Form;
	
LRESULT CALLBACK DWndProc(HWND, UINT, WPARAM, LPARAM);

//Formのスマートポインタ版
SP_TDEF(Form);

SP_TDEF(GameMain);
SP_TDEF(GraphicInfo);
SP_TDEF(DXInfo);

//DirectXの初期化をするクラス

//<summary>DDeviceコメント</summary>
class DDevice{
private:
	//Direct3D
	//ComPtr<IDirect3D9>::type direct3D_;
	//boost::intrusive_ptr<IDirect3D9> direct3D_;

	//デバイス
	//ComPtr<IDirect3DDevice9>::type d3Device_;
	boost::intrusive_ptr<IDirect3DDevice9> d3Device_;

	//Direct3D, デバイス
	//SPGrahpicInfo ginfo_;

	//DirectXのメインになるフォームウィンドウ
	//SPForm form_;

	SPGameMain gm_;
	

public:

	//ウィンドウハンドルの設定
	//void SetHWND(HWND hWnd);

	//DirectXの初期化
	bool Init();

	//DiretXのメインループ
	void DMainLoop();
};



}