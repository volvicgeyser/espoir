#include"stdafx.h"
#include"macro.h"
#include"debug.h"
#include"xfile.h"
#include"system.h"
#include"cast.h"

namespace espoir{
	XFile::XFile(const String& model){
		if(model.empty()){
			const String str = _T("model�̕����񂪋���ۂł�");
			DOut dout;
			dout << str << DSTM << std::endl;
#if NDEBUG
			ShowError(str);
#endif
			return;
		}
		if(!PathFileExists(model.c_str())){
			const String str = _T("�����ȃt�@�C���p�X�ł�");
			//������i�o�b�t�@�j�̃T�C�Y
			const unsigned int length = 256;
			TCHAR path[length];
			GetCurrentDirectory(length, path);

			DOut dout;
			dout << str << model.c_str() << _T("�J�����g�f�B���N�g��:") << path << DSTM << std::endl;
#if NDEBUG
			ShowError(str);
#endif
			return;
		}
		LPD3DXBUFFER buf = NULL;

		//���b�V��
		LPD3DXMESH mesh = NULL;


		//���b�V���}�e���A���̐�
		this->numMaterials_ = 0L;
		
		const HRESULT hResult = D3DXLoadMeshFromX(model.c_str(), D3DXMESH_SYSTEMMEM, sys::Device::GetInst().GetRef(), NULL,
			&buf, NULL, &this->numMaterials_, &mesh);

		//�G���[����
		if(FAILED(hResult)){
			switch(hResult){
				case D3DXFERR_FILENOTFOUND:
					throw std::runtime_error("�w�肳�ꂽX�t�@�C�������݂��܂���");
					break;
				case E_FAIL:
					throw std::runtime_error("XFile �����s���̃G���[");
					break;
			}
			throw std::runtime_error("X�t�@�C���̏������Ɏ��s���܂���");
		}

		//�}�e���A���̎擾
		D3DXMATERIAL* materials = cast<D3DXMATERIAL*>(buf->GetBufferPointer());
		if(!materials)
			throw std::runtime_error("�}�e���A���̎擾�Ɏ��s���܂���");

		for(DWORD i = 0; i < this->numMaterials_; i++){
			this->meshMaterials_.push_back(materials[i].MatD3D);
			this->textures_.push_back(NULL);

			//�\���̂�Unicode�ɑΉ����Ă��Ȃ��I�I
			if(materials[i].pTextureFilename != NULL &&
				lstrlenA(materials[i].pTextureFilename) > 0)
			{

				std::string texturePath("../../x/");
				const std::string filename = materials[i].pTextureFilename;
				texturePath = texturePath + filename;
				//�����ł��}���`�o�C�g�����Ή��̊֐����g��
				if(FAILED(D3DXCreateTextureFromFileA(sys::Device::GetInst().GetRef(),
					texturePath.c_str(), &this->textures_[i])))
					throw std::runtime_error("�e�N�X�`���}�b�v��������܂���ł���");
			}
		}
		buf->Release();
}

}
