#include"stdafx.h"
#include"intrusive_func.h"

//Com�|�C���^�p�A�Q�Ƃ����������̏���
void intrusive_ptr_add_ref(IUnknown* ptr)
{
	ptr->AddRef();
}

//Com�|�C���^�p�A�Q�Ƃ����������̏���
void intrusive_ptr_release(IUnknown* ptr)
{
	ptr->Release();
}
