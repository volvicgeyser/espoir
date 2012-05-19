#pragma once
#include"intrusive_func.h"

namespace espoir{

//Xファイルから読みだしたデータを格納しておく構造体
struct XFileData{
	std::vector<D3DMATERIAL9> meshMaterials_;
	std::vector<LPDIRECT3DTEXTURE9> textures_;
	LPD3DXMESH mesh_;
	DWORD numMaterials_;
};

//Xファイルの読み込みをおこうなうクラス
class XFile{
public:
SP_TDEF(XFileData)
	static SPXFileData Load(const String& model);
};


}
