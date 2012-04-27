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
	//using namespace espoir;
	//DOut dout;
	const ULONG count = ptr->Release();
	//dout << _T("�J�E���^:") << count << std::endl;
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
	//	throw std::runtime_error("�J�E���^����v���܂���");
	//dout << _T("Direct3D�J�E���^ Add:") << count << std::endl;
//}

//void intrusive_ptr_release(IDirect3D9* ptr)
//{
	//using namespace espoir;
	//DOut dout;
	//direct3d_count--;
	//const ULONG count = ptr->Release();
	//if(direct3d_count != count)
	//	throw std::runtime_error("�J�E���^����v���܂���");
	//dout << _T("Direct3D�J�E���^ Release:") << count << std::endl;
	//dout << _T("Direct3D�Ǝ��̃J�E���^ Release:") << direct3d_count << std::endl;
//}
//#endif