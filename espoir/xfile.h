#pragma once
#include"intrusive_func.h"

namespace espoir{

//Xファイルから読みだしたデータを格納しておく構造体
struct XFileData{
	std::vector<D3DMATERIAL9> meshMaterials_;
	std::vector<LPDIRECT3DTEXTURE9> textures_;
	DWORD numMaterials_;
};

//Xファイルの読み込みをおこうなうクラス
class XFile{
public:
SP_TDEF(XFileData)
//    XFile(const String& model);
	static SPXFileData Load(const String& model);
};


}
