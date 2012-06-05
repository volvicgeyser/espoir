#pragma once

#include"safedelete.h"

namespace espoir{

template<class ObjType>
class DXBackBufferCreation{
typedef ComPtr<ObjType> SPObjType;
public:
	//バックバッファの初期化
	static SPObjType Create(){
		IDirect3DSurface9* backbuf;
		const HRESULT hr = sys::Device::GetInst()->GetBackBuffer(
				0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuf);

		if(FAILED(hr)){
			throw std::runtime_error("BackBufferの初期化に失敗しました");
		}
		BOOST_ASSERT(backbuf);

		SPObjType spobj = SPObjType(backbuf);

		return spobj;
	}
};

}
