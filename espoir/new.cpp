#include"stdafx.h"
#include"new.h"

namespace espoir{


#if _DEBUG
	namespace _allocator{
		unsigned long alloc_count = 0L;
		unsigned long dealloc_count = 0L;
	}
//new_�֐����Ăяo�����񐔂��擾����
unsigned long GetAllocCount(){return _allocator::alloc_count;}

//delete_�֐����Ăяo�����񐔂��擾����
unsigned long GetDeallocCount(){return _allocator::dealloc_count;}
#endif

}