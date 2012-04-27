
#include"stdafx.h"
#include"DDevice.h"
#include"debug.h"
//#include"singleton.h"
#include"Resource.h"
//#include"DXFormCreation.h"
//#include"DX3D9Creation.h"
//#include"DXDeviceCreation.h"
#include"system.h"
namespace espoir{

}

bool espoir::DDevice::Init(){
		//戻り値　初期化に成功した=true : 失敗=false
		bool result = true;

		//DirectXの関数を実行時に発生したエラーコード
		


//        if(this->direct3D_.get() != NULL){
//            DOut dout;
//            dout << _T("Direct3Dは既に初期化されています") << DSTM << std::endl;
//        }

		//IDirect3Dオブジェクトインスタンスの取得
		//direct3D_.Attach( Direct3DCreate9(D3D_SDK_VERSION) );

		//this->direct3D_ = boost::intrusive_ptr<IDirect3D9>( Direct3DCreate9(D3D_SDK_VERSION), false);
		//typedef Singleton<IDirect3D9, DX3D9Creation> SingleDX3D9;

		//::D3DPRESENT_PARAMETERS d3dpp;
		//ZeroMemory(&d3dpp, sizeof(d3dpp));
		
		//ディスプレイモード構造体
		//::D3DDISPLAYMODE d3ddm;
		//ZeroMemory(&d3ddm, sizeof(d3ddm));

		//ディスプレイモードの取得
		//const HRESULT err_code = sys::Direct3D::getInst()->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
		//const HRESULT err_code = direct3D_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		//ディスプレイモード取得時のエラーチェック
		//if(FAILED(err_code)){
		//	espoir::DOut dout;
		//	dout << _T("GetAdapterDisplayModeが失敗しました") << std::endl;
		//}
		//d3dpp.BackBufferFormat =  d3ddm.Format;//D3DFMT_R5G6B5;//D3DFMT_UNKNOWN;//d3ddm.Format;
		//d3dpp.BackBufferCount = 1;
		//d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		//d3dpp.Windowed = TRUE;

		//アプリケーションがバックバッファを直接ロック
		//d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

		//DirectXのメインウィンドウを生成
		typedef SPSingleton<Form, DXFormCreation> SingleDXForm;
		SingleDXForm::GetInst()->Show();
		//Singleton<Form, DXFormCreation>::getInst()->Show();
		//this->form_ = SPForm(new Form(DirectX));
		//this->form_->Show();

		//IDirect3DDevice9* tmp_d3Device = NULL;

		//HEL(ソフトウェアエミュレーション)でデバイス生成
		//const HRESULT hResult = sys::Direct3D::getInst()->CreateDevice(
		//	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, SingleDXForm::getInst()->GetHandle(),
		//	D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &tmp_d3Device);

//        const HRESULT hResult = direct3D_->CreateDevice(
//            D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, SingleDXForm::getInst()->GetHandle(),

//            D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &tmp_d3Device);
					//D3DPRESENTFLAG_LOCKABLE_BACKBUFFER, &d3dpp, &d3Device_);
		//this->d3Device_ = boost::intrusive_ptr<IDirect3DDevice9>(tmp_d3Device, false);

		//デバイス生成時のエラーチェック
		//if(FAILED(hResult))
		//{	
//            DOut dout;
//            dout << _T("Error: HELでの初期化に失敗しました") << std::endl;
//            switch(hResult){
//                case D3DERR_INVALIDCALL:
//                    dout << _T("メソッドの呼び出しが無効。パラメータに異常か無いかチェックしてください") << std::endl;
//                    break;
//                case D3DERR_NOTAVAILABLE:
//                    dout << _T("このデバイスは、問い合わせたテクニックをサポートしていません") << std::endl;
//                    break;
//                case D3DERR_OUTOFVIDEOMEMORY:
//                    dout << _T("Direct3D が処理を行うのに十分なディスプレイ メモリがありません") << std::endl;
//                    break;
//            }
//        }

		//DirectXの初期化に失敗していたらfalseを返す
		//if(espoir::DDevice::direct3D_ == 0)
		//	result = false;


		//test
		//Singleton<IDirect3DDevice9, DXDeviceCreation>::getInst();

		//Grahpcsの初期化
		SPGraphicInfo gInfo(new GraphicInfo());
		//gInfo->d3Device = this->d3Device_;
		//gInfo->direct3D = this->direct3D_;

		SPDXInfo dxInfo(new DXInfo);
		if(dxInfo->g.get() == NULL)
			dxInfo->g = SPGraphic(new Graphic(gInfo));

		//GameWindowの初期化
		if(this->gm_.get() == NULL)
			this->gm_ = SPGameMain(new GameMain(dxInfo));

		return result;
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
				DOut dout;
				dout << _T("GameMainが初期化されていません") << DSTM << std::endl;
			}
		}
	}

}





