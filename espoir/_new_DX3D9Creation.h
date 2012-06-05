#pragma once

#include"system.h"
#include"debug.h"
#include"safedelete.h"

namespace espoir{

template<class ObjType>
class DX3D9Creation{
public:
	static ObjType* Create(){
		IDirect3D9* direct3d = Direct3DCreate9(D3D_SDK_VERSION);

		if(!direct3d)
			throw std::runtime_error("Direct3Dの初期化に失敗しました");

		return direct3d;
	}
	static void Destroy(ObjType* direct3d){
		safe_release(direct3d);
	}
};


}
