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
	//staticに生成するので何もしない
	static void Destroy(ObjType*){
	}
private:
};

}
