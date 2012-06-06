
#include"stdafx.h"
#include"DDevice.h"
#include"debug.h"
//#include"singleton.h"
#include"Resource.h"
//#include"DXFormCreation.h"
//#include"DX3D9Creation.h"
//#include"DXDeviceCreation.h"
#include"system.h"
#include"new.h"
namespace espoir{

}

bool espoir::DDevice::Init(){
		//戻り値　初期化に成功した=true : 失敗=false
		//bool result = true;

		//DirectXのメインウィンドウを生成
		typedef Singleton<Form, DXFormCreation> SingleDXForm;
		SingleDXForm::GetInst()->Show();

		//GameWindowの初期化
		if(this->gm_ == NULL)
			this->gm_ = boost::make_shared<GameMain>();

		return true;
}

void espoir::DDevice::DMainLoop(){
	
	//メッセージ
	MSG msg;
	
	//インスタンスハンドルの取得
	const HINSTANCE hInst = GetModuleHandle(NULL);
	
	//アクセラレータ（ショートカットキー）テーブルを取得
	const HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_ESPOIR));

	while(TRUE){
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)){
			if(!GetMessage(&msg, NULL, 0, 0))
				break;
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else{
			if(this->gm_ != NULL){
				this->gm_->Render();
				this->gm_->Update();
			}
			else{
				throw std::runtime_error("GameMainが初期化されていません");
			}
		}
	}

}





