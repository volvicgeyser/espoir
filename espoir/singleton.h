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
//SP_TDEF(ObjType)
typedef SmartPtr<ObjType> SPObjType;
public:
	static SPObjType GetInst(){
		//同じ型なら一度だけ生成
		static SPObjType object_;
		if(object_ == NULL){
			object_ = CreationPolicy<ObjType>::Create();
		}
		return object_;
	}
};



//静的に生成
template<class ObjType>
class DefaultSingletonCreation{
public:
	static ObjType* Create(){
		static ObjType obj;
		return &obj;
	}
};

template<class ObjType>
class DefaultLifeTimePolicy{
};

template<
	class ObjType,
	template<class> class CreationPolicy = DefaultSingletonCreation,
	template<class> class LifeTimePolicy = DefaultLifeTimePolicy 
>
class Singleton{
public:
    static ObjType* GetInst(){
        static ObjType* object;
        if(!object){
            object = CreationPolicy<ObjType>::Create();
			BOOST_ASSERT(object);
        }
        return object; 
    }

};







}
