#pragma once

//newとdeleteの呼び出しを管理
//でもdeleteは使わない方針

namespace espoir{

#if _DEBUG
	namespace _allocator{
		extern unsigned long alloc_count;
		extern unsigned long dealloc_count;
	}
#endif

template<class T>
inline T* new_(){
#if _DEBUG
	_allocator::alloc_count++;
#endif
	return new T();
}

template<class T>
inline void delete_(T* t){
#if _DEBUG
	_allocator::dealloc_count++;
#endif
	delete t;
}

#if _DEBUG
	//new_関数を呼び出した回数を取得する
	unsigned long GetAllocCount();

	//delete_関数を呼び出した回数を取得する
	unsigned long GetDeallocCount();
#else
	#define GetAllocCount()
	#define GetDeallocCount()
#endif

template<class T, class Args1>
inline T* new_(const Args1& args1){
#if _DEBUG
	_allocator::alloc_count++;
#endif
    return new T(args1);
}

//template<class T, class Args1, class Args2>
//inline T* new_(Args1 args1, Args2 args2){
//    return new T(args1, args2);
//}

//template<class T, class Args1, class Args2, class Args3>
//inline T* new_(Args1 args1, Args2 args2, Args3 args3){
//    return new T(args1, args2, args3);
//}

}
