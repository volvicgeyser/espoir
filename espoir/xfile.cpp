#include"stdafx.h"
#include"macro.h"
#include"debug.h"
#include"xfile.h"
#include"system.h"
#include"cast.h"

namespace espoir{
	SP_TDEF(XFileData);
	SPXFileData XFile::Load(const String& model){
		if(model.empty()){
			throw std::runtime_error("model�̕����񂪋���ۂł�");
		}
		if(!PathFileExists(model.c_str())){

			//�G���[������̒���
			const unsigned int length = 256;
			boost::array<TCHAR, length> path;
			GetCurrentDirectory(length, path.begin());

			std::stringstream str;
			str << _T("�����ȃt�@�C���p�X�ł�") << model.c_str() << _T("�J�����g�f�B���N�g��:") << path.begin() << std::endl;

//            DOut dout;
//            dout << str << model.c_str() << _T("�J�����g�f�B���N�g��:") << path << DSTM << std::endl;
			throw std::runtime_error(str.str().c_str());
		}
		LPD3DXBUFFER buf = NULL;

		//���b�V��
		//LPD3DXMESH mesh = NULL;


		//3DData�\����
		SPXFileData xData(new_<XFileData>());
		//���b�V���}�e���A���̐�
		xData->numMaterials_ = 0L;
		
		//X�t�@�C���̓ǂݏo��
		const HRESULT hResult = D3DXLoadMeshFromX(model.c_str(), D3DXMESH_SYSTEMMEM, sys::Device::GetInst().GetRef(), NULL,
			&buf, NULL, &xData->numMaterials_, &xData->mesh_);

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
		const D3DXMATERIAL* materials = cast<D3DXMATERIAL*>(buf->GetBufferPointer());
		if(!materials)
			throw std::runtime_error("�}�e���A���̎擾�Ɏ��s���܂���");

		for(DWORD i = 0; i < xData->numMaterials_; i++){
			xData->meshMaterials_.push_back(materials[i].MatD3D);
			
			typedef ComPtr<IDirect3DTexture9> SPTexture;
			//typedef boost::intrusive_ptr<IDirect3DTexture9> SPTexture;

			//NULL�̗v�f��}��
			//SPTexture texture = SPTexture(NULL);
			//xData->textures_.push_back(texture);

			//�\���̂�Unicode�ɑΉ����Ă��Ȃ��I�I
			if(materials[i].pTextureFilename != NULL &&
				lstrlenA(materials[i].pTextureFilename) > 0)
			{

				//X�t�@�C�����u����Ă���f�B���N�g��
				std::string texturePath("../../x/");

				LPDIRECT3DTEXTURE9 texture = NULL;

				const std::string filename = materials[i].pTextureFilename;
				if(filename.empty()){
					throw std::runtime_error("�e�N�X�`���t�@�C��������ł�");
				}
				texturePath = texturePath + filename;
				if(!PathFileExistsA(texturePath.c_str())){
					throw std::runtime_error("�e�N�X�`���t�@�C�������݂��܂���");
				}
				//�����ł��}���`�o�C�g�����Ή��̊֐����g��
				if(FAILED(D3DXCreateTextureFromFileA(sys::Device::GetInst().GetRef(),
					texturePath.c_str(), &texture )))
				{
					throw std::runtime_error("�e�N�X�`���}�b�v��������܂���ł���");
				}

				BOOST_ASSERT(texture);
				//BOOST_ASSERT(texture->Name);
				//if(!texture->Name)
				//	throw std::runtime_error("�e�N�X�`�����������ł�");

				const SPTexture spTexture(texture);
				xData->textures_.push_back(spTexture);
				

				//texture->Release();
				//texture = NULL;
				//ComPtr<IDirect3DTexture9> a;
				//ComPtr<LPDIRECT3DTEXTURE9> a;
				//xData->textures_[i]->Name;
			}
		}
		//�o�b�t�@�̉��
		const ULONG buf_count = buf->Release();
		
		BOOST_ASSERT(!buf_count);
		return xData;

	}

}
