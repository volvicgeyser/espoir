#pragma once
#include"intrusive_func.h"

namespace espoir{
	//X�t�@�C���̊Ǘ����s���N���X
class XFile{
public:
	XFile(const String& model);
private:
	std::vector<D3DMATERIAL9> meshMaterials_;
	std::vector<LPDIRECT3DTEXTURE9> textures_;
	DWORD numMaterials_;
};

}
