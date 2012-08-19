#include"stdafx.h"
#include"intrusive_func.h"
#include"debug.h"

//Comポインタ用、参照が増えた時の処理
void intrusive_ptr_add_ref(IUnknown* ptr)
{
	ptr->AddRef();
}

//Comポインタ用、参照が減った時の処理
void intrusive_ptr_release(IUnknown* ptr)
{
	const ULONG count = ptr->Release();
}


//フォント用
void intrusive_ptr_add_ref(LPD3DXFONT ptr){
	ptr->AddRef();
}

void intrusive_ptr_release(LPD3DXFONT ptr){
	const ULONG count = ptr->Release();
}