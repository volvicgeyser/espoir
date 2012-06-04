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

	//shared_ptrに任せるので破棄は何もしない
	static void Destroy(ObjType){}
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


//C++の規則に従った寿命管理
//obj1, obj2, obj3 と生成されると obj3, obj2, obj1 という順序に解放される
template<class ObjType>
class SPDefaultLifetime
{
	//注意! ObjTypeはスマートポインタ
public:
	static void ScheduleCall(ObjType, void(*func)(void)){
		std::atexit(func);
	}

	//一度削除して呼び出すと例外が投げられる
	static void OnDeadReference(){
		throw std::runtime_error("Singletonオブジェクトが一度破棄されています");
	}
};

//テンプレートなSingleton
template <
	class ObjType,
	template <class> class CreationPolicy = SPDefaultSingletonCreation,
	template <class> class SmartPtr = boost::shared_ptr,
	template <class> class LifeTimePolicy = SPDefaultLifetime
		>
class SPSingleton : boost::noncopyable{
//SP_TDEF(ObjType)
typedef SmartPtr<ObjType> SPObjType;
//typedef SPSingleton<CreationPolicy, SmartPtr, LifeTimePolicy> self_type;
public:
	static SPObjType GetInst(){
		//同じ型なら一度だけ生成
		static SPObjType object_;
		if(object_ == NULL){

			//一度破棄されていないかどうかチェック
			if(isDestroyed_){
				LifeTimePolicy<SPObjType>::OnDeadReference();
				isDestroyed_ = true;
			}

			//オブジェクトの生成
			object_ = CreationPolicy<ObjType>::Create();

			//寿命管理登録
			LifeTimePolicy<SPObjType>::ScheduleCall(object_, DestroySingleton);
		}
		return object_;
	}
	static void DestroySingleton(){
		BOOST_ASSERT(!isDestroyed_);
		//CreationPolicy<ObjType>::Destroy(object_);
	}
private:
	static bool isDestroyed_;
};

//破棄フラグの初期化
template<class O, 
	template<class> class C, 
	template<class> class S,
	template<class> class L
>bool SPSingleton<O, C, S, L>::isDestroyed_ = false;

//オブジェクトの初期化
//template<class O,
//    template<class> class C,
//    template<class> class S,
//    template<class> class L
//>S<O> SPSingleton<O, C, S, L>::object_ = 0;

//Comptr専用
//template <
//    class ObjType,
//    template <class> class CreationPolicy,
//    template <class> class SmartPtr
//>
//class SPSingleton : boost::noncopyable{
//public:
//};

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
public:
	static void ScheduleCall(ObjType*, boost::function<void (void)> func){
	}
};

template<
	class ObjType,
	template<class> class CreationPolicy = DefaultSingletonCreation,
	template<class> class LifeTimePolicy = DefaultLifeTimePolicy 
>
class Singleton{
public:
	static ObjType* object;
    static ObjType* GetInst(){
        //static ObjType* object;
        if(!object){
            object = CreationPolicy<ObjType>::Create();
			BOOST_ASSERT(object);
			LifeTimePolicy<ObjType>::ScheduleCall(object, &DestroySingleton);
        }
        return object; 
    }
	static void DestroySingleton(){
		
	}

};

//オブジェクトを0(NULL)で初期化
template<
	class O,
	template<class> class C,
	template<class> class L
>O* Singleton<O, C, L>::object = 0;







}
