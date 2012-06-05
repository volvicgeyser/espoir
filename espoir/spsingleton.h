#pragma once
#include"macro.h"
#include"new.h"

namespace espoir{

//シングルトンで保持するオブジェクトの生成を定義するクラス
//newしたものをスマートポインタで包み込んで返す
template <class ObjType> 
class SPDefaultSingletonCreation{
SP_TDEF(ObjType)
public:
	//オブジェクトの生成関数
	static SPObjType Create(){
		return SPObjType(new_<ObjType>());
	}
};

//静的に生成
//template <class ObjType>
//class SPSingletonStaticCreation{
//SP_TDEF(ObjType)
//public:
//    static SPObjType Create(){
//        static ObjType obj;
//        return SPObjType(obj);
//    }
//};

//テンプレートなSingleton
template <
	class ObjType,
	template <class> class CreationPolicy = SPDefaultSingletonCreation,
	template <class> class SmartPtr = boost::shared_ptr
		>
class SPSingleton : boost::noncopyable{
typedef SmartPtr<ObjType> SPObjType;
public:
	static SPObjType GetInst(){
		//同じ型なら一度だけ生成
		//static SPObjType object_;
		if(object_ == NULL){

			//オブジェクトの生成
			object_ = CreationPolicy<ObjType>::Create();
		}
		return object_;
	}
private:
	static SPObjType object_;
};

//オブジェクトの実態
template<class O,
    template<class> class C,
	template<class> class S
>S<O> SPSingleton<O, C, S>::object_;

}
