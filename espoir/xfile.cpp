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
#if NDEBUG
			ShowError(str);
#endif
		}
		LPD3DXBUFFER buf = NULL;

		//���b�V��
		LPD3DXMESH mesh = NULL;


		//3DData�\����
		SPXFileData xData(new XFileData);
		//���b�V���}�e���A���̐�
		xData->numMaterials_ = 0L;
		
		const HRESULT hResult = D3DXLoadMeshFromX(model.c_str(), D3DXMESH_SYSTEMMEM, sys::Device::GetInst().GetRef(), NULL,
			&buf, NULL, &xData->numMaterials_, &mesh);

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

		for(DWORD i = 0; i < xData->numMaterials_; i++){
			xData->meshMaterials_.push_back(materials[i].MatD3D);
			xData->textures_.push_back(NULL);

			//�\���̂�Unicode�ɑΉ����Ă��Ȃ��I�I
			if(materials[i].pTextureFilename != NULL &&
				lstrlenA(materials[i].pTextureFilename) > 0)
			{

				//X�t�@�C�����u����Ă���f�B���N�g��
				std::string texturePath("../../x/");

				const std::string filename = materials[i].pTextureFilename;
				texturePath = texturePath + filename;
				//�����ł��}���`�o�C�g�����Ή��̊֐����g��
				if(FAILED(D3DXCreateTextureFromFileA(sys::Device::GetInst().GetRef(),
					texturePath.c_str(), &xData->textures_[i])))
					throw std::runtime_error("�e�N�X�`���}�b�v��������܂���ł���");
			}
		}
		//�o�b�t�@�̉��
		buf->Release();
		return xData;

	}

}
