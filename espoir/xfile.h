#pragma once
#include"intrusive_func.h"

namespace espoir{
	//Xファイルの管理を行うクラス
class XFile{
public:
	XFile(const String& model);
private:
	std::vector<D3DMATERIAL9> meshMaterials_;
	std::vector<LPDIRECT3DTEXTURE9> textures_;
	DWORD numMaterials_;
};

}
