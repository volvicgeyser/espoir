#pragma once

//#include "system.h"
//#include"form.h"
//#include"DXFormCreation.h"
//#include"DX3D9Creation.h"
//#include"Singleton.h"
#include"system.h"
#include"debug.h"
namespace espoir{

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

		::D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		d3dpp.BackBufferFormat =  d3ddm.Format;//D3DFMT_R5G6B5;//D3DFMT_UNKNOWN;//d3ddm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = TRUE;

		//アプリケーションがバックバッファを直接ロック
		d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;


		const HRESULT hResult = sys::Direct3D::GetInst()->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, sys::Form::GetInst()->GetHandle(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &tmp_d3Device);

		//デバイス生成時のエラーチェック
		CheckDeviceErr(hResult);

		const SPObjType obj = SPObjType(tmp_d3Device);

		return obj;
	}
private:
	struct DeviceDeleter{
		template<class T>
		void operator()(T* t){
			if(!t){
				throw std::runtime_error("Deviceが初期化されていないか、不正に削除されています");
			}
			t->Release();
		}
	};
};

}
