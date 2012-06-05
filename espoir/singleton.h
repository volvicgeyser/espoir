#pragma once

//静的に生成
template<class ObjType>
class DefaultSingletonCreation{
public:
	//Createメンバ関数が呼び出された時点で生成される
	static ObjType* Create(){
		static ObjType obj;
		return &obj;
	}
	
	//staticに確保するので何もしない
	static void Destroy(ObjType*){
		std::cout << "Destroy" << std::endl;
	}
};

template<class ObjType>
class DefaultLifeTimePolicy{
public:
	//atexitに登録
	static void ScheduleCall(ObjType*, void(*f)(void)){
		atexit(f);
	}

	//ダングリングポインタ参照時に例外を投げる
	static void OnDeadReference()
	{
		throw std::runtime_error("Singletonオブジェクトは一度破棄されています");
	}
};

template<
	class ObjType,
	template<class> class CreationPolicy = DefaultSingletonCreation,
	template<class> class LifeTimePolicy = DefaultLifeTimePolicy 
>
class Singleton{
public:
	static ObjType* object_;
    static ObjType* GetInst(){
        //static ObjType* object;
        if(!object_){

			//Singletonオブジェクトが一度破棄されているかどうかチェック
			if(isDestroyed_){
				LifeTimePolicy<ObjType>::OnDeadReference();
				isDestroyed_ = false;
			}

			//CreationPolicyによるオブジェクトの生成
            object_ = CreationPolicy<ObjType>::Create();

			BOOST_ASSERT(object_);

			//寿命を設定する
			LifeTimePolicy<ObjType>::ScheduleCall(object_, &DestroySingleton);

        }
        return object_; 
    }
	//Singletonオブジェクトの破棄
	//CreationPolicyの破棄メンバ関数を呼び出す
	static void DestroySingleton(){
		BOOST_ASSERT(object_);
		CreationPolicy<ObjType>::Destroy(object_);
		isDestroyed_ = true;
	}
private:
	static bool isDestroyed_;
};


//オブジェクトを0(NULL)で初期化
template<
	class O,
	template<class> class C,
	template<class> class L
>O* Singleton<O, C, L>::object_ = 0;


//破棄フラグの初期化
template<
	class O,
	template<class> class C,
	template<class> class L
>bool Singleton<O, C, L>::isDestroyed_= 0;


