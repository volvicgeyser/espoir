#include"stdafx.h"
#include"intrusive_func.h"
#include"debug.h"

//���g�p
//Com�|�C���^�p�A�Q�Ƃ����������̏���
void intrusive_ptr_add_ref(IUnknown* ptr)
{
	ptr->AddRef();
}

//Com�|�C���^�p�A�Q�Ƃ����������̏���
void intrusive_ptr_release(IUnknown* ptr)
{
	const ULONG count = ptr->Release();
}
