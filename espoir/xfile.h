#pragma once
#include"ComPtr.h"
//#include"intrusive_func.h"
#include"safedelete.h"
namespace espoir{



//X�t�@�C������ǂ݂������f�[�^���i�[���Ă����\����
struct XFileData{
	typedef ComPtr<IDirect3DTexture9> SPTexture;
    typedef std::vector<SPTexture> TextureArray;

	std::vector<D3DMATERIAL9> meshMaterials_;
	TextureArray textures_;
//    LPD3DXMESH mesh_;
	boost::intrusive_ptr<ID3DXMesh> mesh_;
	DWORD numMaterials_;
};

//X�t�@�C���̓ǂݍ��݂��������Ȃ��N���X
class XFile{
public:
SP_TDEF(XFileData)
	static SPXFileData Load(const String& model);
};


}
