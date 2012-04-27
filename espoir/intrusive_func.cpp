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
	//using namespace espoir;
	//DOut dout;
	const ULONG count = ptr->Release();
	//dout << _T("カウンタ:") << count << std::endl;
}

//#if _DEBUG
//static ULONG direct3d_count = 1;
//void intrusive_ptr_add_ref(IDirect3D9* ptr)
//{
	//using namespace espoir;
	//DOut dout;
	//direct3d_count++;
	//const ULONG count = ptr->AddRef();
	//if(direct3d_count != count)
	//	throw std::runtime_error("カウンタが一致しません");
	//dout << _T("Direct3Dカウンタ Add:") << count << std::endl;
//}

//void intrusive_ptr_release(IDirect3D9* ptr)
//{
	//using namespace espoir;
	//DOut dout;
	//direct3d_count--;
	//const ULONG count = ptr->Release();
	//if(direct3d_count != count)
	//	throw std::runtime_error("カウンタが一致しません");
	//dout << _T("Direct3Dカウンタ Release:") << count << std::endl;
	//dout << _T("Direct3D独自のカウンタ Release:") << direct3d_count << std::endl;
//}
//#endif