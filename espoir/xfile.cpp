#include"stdafx.h"
#include"macro.h"
#include"debug.h"
#include"xfile.h"

namespace espoir{
	XFile::XFile(const String model){
		if(model.empty()){
			DOut dout;
			dout << _T("model�̕����񂪋���ۂł�") << DSTM << std::endl;
		}
		if(!PathFileExists(model.c_str())){
			DOut dout;
			dout << _T("�����ȃt�@�C���p�X�ł�") << model.c_str() <<DSTM << std::endl;
		}
		//D3DXLoadMeshFromX(model, D3DXMESH_SYSTEMMEM, 
	}
}
