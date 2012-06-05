#pragma once

#include"system.h"
#include"safedelete.h"

namespace espoir{

static void InitPresent(D3DPRESENT_PARAMETERS* d3dpp, const D3DDISPLAYMODE d3ddm){
	if(!d3dpp)
		throw std::runtime_error("d3dppが空です");

	d3dpp->BackBufferFormat = d3ddm.Format;
	d3dpp->BackBufferCount = 1;
	d3dpp->SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp->Windowed = TRUE;

	//アプリケーションがバックバッファを直接ロック
	d3dpp->Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
}

template<class ObjType>
class DXDeviceCreation{
public:
	static ObjType* Create(){
		using namespace std;
		IDirect3DDevice9* device = NULL;

		//ディスプレイモード構造体
		D3DDISPLAYMODE d3ddm;

		//0で初期化
		ZeroMemory(&d3ddm, sizeof(d3ddm));

		//ディスプレイモードの取得
		const HRESULT displaymode_err = sys::Direct3D::GetInst()->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);


		//ディスプレイモードのエラーチェック
		if(FAILED(displaymode_err))
			throw std::runtime_error("GetAdapterDisplayModeが失敗しました");

		//プレゼントパラメータ
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		//ディスプレイモードの設定
		InitPresent(&d3dpp, d3ddm);

		const HRESULT hResult = sys::Direct3D::GetInst()->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, sys::Form::GetInst()->GetHandle(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device);

		//ユーザーの実行でエラーになる可能性も十分に考えられるので
		//ダイアログを出して初期化に失敗したことを伝える
		if(FAILED(hResult))
			MessageBox(NULL, _T("HALでの初期化に失敗しました"), _T("err"), MB_OK);

		if(!device)
			throw std::runtime_error("deviceがNULLです");

		return device;
	}

	//Deviceの破棄
	static void Destroy(ObjType* device) {
		safe_release(device);
	}
};

}
