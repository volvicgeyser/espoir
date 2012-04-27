#pragma once
#include"macro.h"

namespace espoir{

//シングルトンで保持するオブジェクトの生成を定義するクラス
//newしたものをスマートポインタで包み込んで返す
template <class ObjType> 
class SPDefaultSingletonCreation{
SP_TDEF(ObjType)
public:
	static SPObjType Create(){
		return SPObjType(new ObjType);
	}
};

//静的に生成
template <class ObjType>
class SPSingletonStaticCreation{
SP_TDEF(ObjType)
public:
	static SPObjType Create(){
		static ObjType obj;
		return SPObjType(obj);
	}
};


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

	//typedef SPObjType CreationPolicy<ObjType>::SPObjType;
	//static SPObjType operator->() {return getInst();}

	static SPObjType GetInst(){
		//同じ型なら一度だけ生成
		static SPObjType object_;
		if(object_ == NULL){
			//const SPObjType tmp(CreationPolicy<ObjType>::Create());	
			//if(tmp == NULL)
			//	throw std::runtime_error("正しくオブジェクトが生成できていません");
			object_ = CreationPolicy<ObjType>::Create();
		}
		return object_;
	}
};









}
