#pragma once

#include"form.h"

namespace espoir{

template<class ObjType>
class DXFormCreation{
public:
	static ObjType* Create(){
		static ObjType object(DirectX);
		return &object;
	}
	//static�ɐ�������̂ŉ������Ȃ�
	static void Destroy(ObjType*){
	}
private:
};

}
