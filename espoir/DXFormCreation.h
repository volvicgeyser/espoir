#pragma once

//#include"DDevice.h"
#include"form.h"
namespace espoir{

template <class ObjType>
class DXFormCreation{
SP_TDEF(ObjType);
public:
	static SPObjType Create(){
		//DirectX�E�B���h�E����
		SPObjType obj(new ObjType(DirectX));
		
		return obj;
	}
private:
};

}