#include"stdafx.h"
#include"intrusive_func.h"

//Comポインタ用、参照が増えた時の処理
void intrusive_ptr_add_ref(IUnknown* ptr)
{
	ptr->AddRef();
}

//Comポインタ用、参照が減った時の処理
void intrusive_ptr_release(IUnknown* ptr)
{
	ptr->Release();
}
