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
	//staticÇ…ê∂ê¨Ç∑ÇÈÇÃÇ≈âΩÇ‡ÇµÇ»Ç¢
	static void Destroy(ObjType*){
	}
private:
};

}
