#include"stdafx.h"
#include"new.h"

namespace espoir{


#if _DEBUG
	namespace _allocator{
		unsigned long alloc_count = 0L;
		unsigned long dealloc_count = 0L;
	}
//new_関数を呼び出した回数を取得する
unsigned long GetAllocCount(){return _allocator::alloc_count;}

//delete_関数を呼び出した回数を取得する
unsigned long GetDeallocCount(){return _allocator::dealloc_count;}
#endif

}