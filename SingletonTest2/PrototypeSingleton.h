#pragma once


template <class ObjType>
class DefaultDeleter{
	static void ExitCallBack(){
		if(ObjType){
			//–¢ŽÀ‘•
		}
	}
};

template <
	class ObjType,
	template <class> class CreationPolicy = SingletonCreation
	template <class> class Deleter = DefaultDeleter
>
class Singleton : boost::noncopyable{
public:
	static GetInst(){
	}
}