#pragma once
#include"ComPtr.h"
//#include"intrusive_func.h"
#include"safedelete.h"
namespace espoir{



//Xファイルから読みだしたデータを格納しておく構造体
struct XFileData{
	typedef ComPtr<IDirect3DTexture9> SPTexture;
	//typedef boost::intrusive_ptr<IDirect3DTexture9> SPTexture;
    typedef std::vector<SPTexture> TextureArray;
	//const static int ARRAY_SIZE = 256;
	//typedef SPTexture TextureArray[ARRAY_SIZE];

	//typedef boost::shared_ptr<IDirect3DTexture9> SPTexture
	std::vector<D3DMATERIAL9> meshMaterials_;
	//std::vector<LPDIRECT3DTEXTURE9> textures_;
	TextureArray textures_;
	//SPTexture textures_;
	//ComPtr<IDirect3DTexture9> textures_;
	//LPDIRECT3DTEXTURE9* texutres_;
	LPD3DXMESH mesh_;
	//ComPtr<ID3DXMesh> mesh_;
	//boost::intrusive_ptr<ID3DXMesh> mesh_;
	DWORD numMaterials_;
	~XFileData(){
		DOut dout;
		dout << _T("XFileDataのですとらくた") << std::endl;

		dout << _T("mesh_解放") << std::endl;
		safe_release(mesh_);
	}
	//~XFileData(){
	//	this->textures_.clear();
	//}
//    ~XFileData(){
//        試験的にデストラクタを使ってテクスチャの解放を行う
//        for(TextureArray::iterator it = textures_.begin(); it != textures_.end();it++)
//        {
//                const ULONG u = (*it)->Release();
//                DOut dout;
//                dout << _T("XFileDataデストラクタの処理") << u << std::endl;
//        }
//    }
};

//Xファイルの読み込みをおこうなうクラス
class XFile{
public:
SP_TDEF(XFileData)
	static SPXFileData Load(const String& model);
};


}
