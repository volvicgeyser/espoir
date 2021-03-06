#pragma once

//#include "system.h"
//#include"form.h"
//#include"DXFormCreation.h"
//#include"DX3D9Creation.h"
//#include"Singleton.h"
#include"system.h"
#include"debug.h"
namespace espoir{

static void InitPresent(D3DPRESENT_PARAMETERS* d3dpp, const D3DDISPLAYMODE d3ddm){
	if(!d3dpp)
		throw std::runtime_error("d3dppが空です");

	d3dpp->BackBufferFormat = d3ddm.Format;
    //d3dpp->BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp->BackBufferCount = 1;
	d3dpp->SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp->Windowed = TRUE;
	if(!d3dpp->Windowed){
		d3dpp->BackBufferWidth = 0;
		d3dpp->BackBufferHeight = 0;
	}
	d3dpp->MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp->EnableAutoDepthStencil = TRUE;
	d3dpp->AutoDepthStencilFormat = D3DFMT_D16;

	
//    d3dpp->EnableAutoDepthStencil = TRUE;
//    d3dpp->AutoDepthStencilFormat = D3DFMT_D16;

	//d3dpp->d3dfor
	//アプリケーションがバックバッファを直接ロック
	d3dpp->Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
}

//デバイス生成時のエラーチェック
static inline void CheckDeviceErr(const HRESULT hResult){
		if(FAILED(hResult))
		{	
			DOut dout;
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
}


template <class ObjType>
class DXDeviceCreation{
//typedef boost::intrusive_ptr<ObjType> SPObjType;
typedef ComPtr<ObjType> SPObjType;
public:
	static SPObjType Create(){

		using namespace std;
		//Device生成
		IDirect3DDevice9* tmp_d3Device = NULL;
		//ObjType* tmp_d3Device = NULL;

		//ディスプレイモード構造体
		::D3DDISPLAYMODE d3ddm;
		ZeroMemory(&d3ddm, sizeof(d3ddm));

		//ディスプレイモードの取得
		const HRESULT err_code = sys::Direct3D::GetInst()->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		//ディスプレイモード取得時のエラーチェック
		if(FAILED(err_code)){
			DOut dout;
			dout << _T("GetAdapterDisplayModeが失敗しました") << std::endl;
		}

		//プレゼントパラメータ
		::D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		//プレゼントパラメータの初期化
		InitPresent(&d3dpp, d3ddm);

		//デバイスの作成 HAL
		const HRESULT hResult = sys::Direct3D::GetInst()->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, sys::Form::GetInst()->GetHandle(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &tmp_d3Device);

		//デバイス生成時のエラーチェック
		CheckDeviceErr(hResult);

		//zbufferの設定
        tmp_d3Device->SetRenderState(D3DRS_ZENABLE, TRUE);	

		//ライティングの設定
        D3DLIGHT9 light;

        ZeroMemory(&light, sizeof(D3DLIGHT9) );
        light.Type = D3DLIGHT_DIRECTIONAL;
        light.Direction = D3DXVECTOR3(0, 0, 10);

        light.Diffuse.r = 1.0f;
        light.Diffuse.g = 1.0f;
        light.Diffuse.b = 1.0f;
		//light.Diffuse.a = 1.0f;

        tmp_d3Device->SetLight( 0, &light );
        tmp_d3Device->LightEnable( 0, true );

        tmp_d3Device->SetRenderState( D3DRS_LIGHTING, TRUE ); 
		//sys::Device::GetInst()->SetRenderState( D3DRS_AMBIENT, 0xff030303); 

		//アンビエント
		//D3DMATERIAL9 mtrl;
		//ZeroMemory( &mtrl, sizeof(mtrl) );
		//mtrl.Ambient.r = 0.75f;
		//mtrl.Ambient.g = 0.0f;
		//mtrl.Ambient.b = 0.0f;
		//mtrl.Ambient.a = 0.0f;
		//tmp_d3Device->SetMaterial( &mtrl );

		tmp_d3Device->SetRenderState(D3DRS_AMBIENT, 0xffffffff );

		const SPObjType obj = SPObjType(tmp_d3Device);

		return obj;
	}
private:
};

}
