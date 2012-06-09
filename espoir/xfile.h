#pragma once
#include"ComPtr.h"
//#include"intrusive_func.h"
#include"safedelete.h"
namespace espoir{



//Xファイルから読みだしたデータを格納しておく構造体
struct XFileData{
	typedef ComPtr<IDirect3DTexture9> SPTexture;
    typedef std::vector<SPTexture> TextureArray;

	std::vector<D3DMATERIAL9> meshMaterials_;
	TextureArray textures_;
//    LPD3DXMESH mesh_;
	boost::intrusive_ptr<ID3DXMesh> mesh_;
	DWORD numMaterials_;
};

//Xファイルの読み込みをおこうなうクラス
class XFile{
public:
SP_TDEF(XFileData)
	static SPXFileData Load(const String& model);
};


}
