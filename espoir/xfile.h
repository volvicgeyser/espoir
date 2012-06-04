#pragma once
#include"ComPtr.h"
//#include"intrusive_func.h"

namespace espoir{

//X�t�@�C������ǂ݂������f�[�^���i�[���Ă����\����
struct XFileData{
	typedef ComPtr<IDirect3DTexture9> SPTexture;
	//typedef boost::intrusive_ptr<IDirect3DTexture9> SPTexture;
	typedef std::vector<SPTexture> TextureArray;

	//typedef boost::shared_ptr<IDirect3DTexture9> SPTexture
	std::vector<D3DMATERIAL9> meshMaterials_;
	//std::vector<LPDIRECT3DTEXTURE9> textures_;
	TextureArray textures_;
	//SPTexture textures_;
	//ComPtr<IDirect3DTexture9> textures_;
	//LPDIRECT3DTEXTURE9* texutres_;
	LPD3DXMESH mesh_;
	DWORD numMaterials_;
//    ~XFileData(){
//        �����I�Ƀf�X�g���N�^���g���ăe�N�X�`���̉�����s��
//        for(TextureArray::iterator it = textures_.begin(); it != textures_.end();it++)
//        {
//                const ULONG u = (*it)->Release();
//                DOut dout;
//                dout << _T("XFileData�f�X�g���N�^�̏���") << u << std::endl;
//        }
//    }
};

//X�t�@�C���̓ǂݍ��݂��������Ȃ��N���X
class XFile{
public:
SP_TDEF(XFileData)
	static SPXFileData Load(const String& model);
};


}
