#pragma once
#include"macro.h"

namespace espoir{

//シングルトンで保持するオブジェクトの生成を定義するクラス
//newしたものをスマートポインタで包み込んで返す
template <class ObjType> 
class DefaultSingletonCreation{
	SP_TDEF(ObjType);
public:
	static SPObjType create(){
		return SPObjType(new ObjType);
	}
};


class SingletonSingleThread{};

template <class ObjType, 
		 template <class> class CreationPolicy = DefaultSingletonCreation, 
		 class ThreadPolicy = SingletonSingleThread
		>
class Singleton{

SP_TDEF(ObjType)
	
public:
	SPObjType object_;
	SPObjType operator->() {return this->GetInst();}
	SPObjType GetInst(){
		if(this->object_.get() == NULL)
			object_ = CreationPolicy::create();	
		return this->object_;
	}
};

namespace system{

}

}
