#pragma once

//#include"DDevice.h"
#include"form.h"
namespace espoir{

template <class ObjType>
class DXFormCreation{
SP_TDEF(ObjType);
public:
	static SPObjType Create(){
		//DirectXウィンドウ生成
		SPObjType obj(new ObjType(DirectX));
		
		return obj;
	}
	//スマートポインタに任せるので何もしない
	static void Destroy(){}
private:
};

}