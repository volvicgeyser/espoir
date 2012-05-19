#pragma once
#include"intrusive_func.h"

namespace espoir{

//X�t�@�C������ǂ݂������f�[�^���i�[���Ă����\����
struct XFileData{
	std::vector<D3DMATERIAL9> meshMaterials_;
	std::vector<LPDIRECT3DTEXTURE9> textures_;
	LPD3DXMESH mesh_;
	DWORD numMaterials_;
};

//X�t�@�C���̓ǂݍ��݂��������Ȃ��N���X
class XFile{
public:
SP_TDEF(XFileData)
	static SPXFileData Load(const String& model);
};


}
