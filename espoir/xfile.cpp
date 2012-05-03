#include"stdafx.h"
#include"macro.h"
#include"debug.h"
#include"xfile.h"
#include"system.h"
#include"cast.h"

namespace espoir{
	XFile::XFile(const String& model){
		if(model.empty()){
			const String str = _T("modelの文字列が空っぽです");
			DOut dout;
			dout << str << DSTM << std::endl;
#if NDEBUG
			ShowError(str);
#endif
			return;
		}
		if(!PathFileExists(model.c_str())){
			const String str = _T("無効なファイルパスです");
			//文字列（バッファ）のサイズ
			const unsigned int length = 256;
			TCHAR path[length];
			GetCurrentDirectory(length, path);

			DOut dout;
			dout << str << model.c_str() << _T("カレントディレクトリ:") << path << DSTM << std::endl;
#if NDEBUG
			ShowError(str);
#endif
			return;
		}
		LPD3DXBUFFER buf = NULL;

		//メッシュ
		LPD3DXMESH mesh = NULL;


		//メッシュマテリアルの数
		this->numMaterials_ = 0L;
		
		const HRESULT hResult = D3DXLoadMeshFromX(model.c_str(), D3DXMESH_SYSTEMMEM, sys::Device::GetInst().GetRef(), NULL,
			&buf, NULL, &this->numMaterials_, &mesh);

		//エラー処理
		if(FAILED(hResult)){
			switch(hResult){
				case D3DXFERR_FILENOTFOUND:
					throw std::runtime_error("指定されたXファイルが存在しません");
					break;
				case E_FAIL:
					throw std::runtime_error("XFile 原因不明のエラー");
					break;
			}
			throw std::runtime_error("Xファイルの初期化に失敗しました");
		}

		//マテリアルの取得
		D3DXMATERIAL* materials = cast<D3DXMATERIAL*>(buf->GetBufferPointer());
		if(!materials)
			throw std::runtime_error("マテリアルの取得に失敗しました");

		for(DWORD i = 0; i < this->numMaterials_; i++){
			this->meshMaterials_.push_back(materials[i].MatD3D);
			this->textures_.push_back(NULL);

			//構造体がUnicodeに対応していない！！
			if(materials[i].pTextureFilename != NULL &&
				lstrlenA(materials[i].pTextureFilename) > 0)
			{

				std::string texturePath("../../x/");
				const std::string filename = materials[i].pTextureFilename;
				texturePath = texturePath + filename;
				//ここでもマルチバイト文字対応の関数を使う
				if(FAILED(D3DXCreateTextureFromFileA(sys::Device::GetInst().GetRef(),
					texturePath.c_str(), &this->textures_[i])))
					throw std::runtime_error("テクスチャマップが見つかりませんでした");
			}
		}
		buf->Release();
}

}
