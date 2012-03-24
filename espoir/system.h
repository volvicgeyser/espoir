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


//シングルスレッド
class SingletonSingleThread{};

//テンプレートなSingleton
template <class ObjType, 
		 template <class> class CreationPolicy = DefaultSingletonCreation, 
		 class ThreadPolicy = SingletonSingleThread
		>
class Singleton{
SP_TDEF(ObjType)
public:
	
	//static SPObjType operator->() {return getInst();}
	static SPObjType getInst(){
		//同じ型なら一度だけ生成
		static SPObjType object_;
		if(object_.get() == NULL)
			object_ = CreationPolicy<ObjType>::create();	
		return object_;
	}
};

namespace system{

}

}
