#include"stdafx.h"
#include"intrusive_func.h"
#include"debug.h"

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


//�t�H���g�p
void intrusive_ptr_add_ref(LPD3DXFONT ptr){
	ptr->AddRef();
}

void intrusive_ptr_release(LPD3DXFONT ptr){
	const ULONG count = ptr->Release();
}