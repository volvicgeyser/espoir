#include"stdafx.h"
#include"macro.h"
#include"debug.h"
#include"xfile.h"

namespace espoir{
	XFile::XFile(const String model){
		if(model.empty()){
			DOut dout;
			dout << _T("modelの文字列が空っぽです") << DSTM << std::endl;
		}
		if(!PathFileExists(model.c_str())){
			DOut dout;
			dout << _T("無効なファイルパスです") << model.c_str() <<DSTM << std::endl;
		}
		//D3DXLoadMeshFromX(model, D3DXMESH_SYSTEMMEM, 
	}
}
