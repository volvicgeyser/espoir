#pragma once

#include"safedelete.h"

namespace espoir{

template<class ObjType>
class DXBackBufferCreation{
typedef ComPtr<ObjType> SPObjType;
public:
	//�o�b�N�o�b�t�@�̏�����
	static SPObjType Create(){
		IDirect3DSurface9* backbuf;
		const HRESULT hr = sys::Device::GetInst()->GetBackBuffer(
				0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuf);

		if(FAILED(hr)){
			throw std::runtime_error("BackBuffer�̏������Ɏ��s���܂���");
		}
		BOOST_ASSERT(backbuf);

		SPObjType spobj = SPObjType(backbuf);

		return spobj;
	}
};

}
