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
			throw std::runtime_error("modelの文字列が空っぽです");
		}
		if(!PathFileExists(model.c_str())){

			//エラー文字列の長さ
			const unsigned int length = 256;
			boost::array<TCHAR, length> path;
			GetCurrentDirectory(length, path.begin());

			std::stringstream str;
			str << _T("無効なファイルパスです") << model.c_str() << _T("カレントディレクトリ:") << path.begin() << std::endl;

//            DOut dout;
//            dout << str << model.c_str() << _T("カレントディレクトリ:") << path << DSTM << std::endl;
			throw std::runtime_error(str.str().c_str());
		}
		LPD3DXBUFFER buf = NULL;

		//メッシュ
		//LPD3DXMESH mesh = NULL;


		//3DData構造体
		SPXFileData xData(new_<XFileData>());
		//メッシュマテリアルの数
		xData->numMaterials_ = 0L;
		
		//Xファイルの読み出し
		const HRESULT hResult = D3DXLoadMeshFromX(model.c_str(), D3DXMESH_SYSTEMMEM, sys::Device::GetInst().GetRef(), NULL,
			&buf, NULL, &xData->numMaterials_, &xData->mesh_);

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
		const D3DXMATERIAL* materials = cast<D3DXMATERIAL*>(buf->GetBufferPointer());
		if(!materials)
			throw std::runtime_error("マテリアルの取得に失敗しました");

		for(DWORD i = 0; i < xData->numMaterials_; i++){
			xData->meshMaterials_.push_back(materials[i].MatD3D);
			
			typedef ComPtr<IDirect3DTexture9> SPTexture;
			//typedef boost::intrusive_ptr<IDirect3DTexture9> SPTexture;

			//NULLの要素を挿入
			//SPTexture texture = SPTexture(NULL);
			//xData->textures_.push_back(texture);

			//構造体がUnicodeに対応していない！！
			if(materials[i].pTextureFilename != NULL &&
				lstrlenA(materials[i].pTextureFilename) > 0)
			{

				//Xファイルが置かれているディレクトリ
				std::string texturePath("../../x/");

				LPDIRECT3DTEXTURE9 texture = NULL;

				const std::string filename = materials[i].pTextureFilename;
				if(filename.empty()){
					throw std::runtime_error("テクスチャファイル名が空です");
				}
				texturePath = texturePath + filename;
				if(!PathFileExistsA(texturePath.c_str())){
					throw std::runtime_error("テクスチャファイルが存在しません");
				}
				//ここでもマルチバイト文字対応の関数を使う
				if(FAILED(D3DXCreateTextureFromFileA(sys::Device::GetInst().GetRef(),
					texturePath.c_str(), &texture )))
				{
					throw std::runtime_error("テクスチャマップが見つかりませんでした");
				}

				BOOST_ASSERT(texture);
				//BOOST_ASSERT(texture->Name);
				//if(!texture->Name)
				//	throw std::runtime_error("テクスチャ名が無効です");

				const SPTexture spTexture(texture);
				xData->textures_.push_back(spTexture);
				

				//texture->Release();
				//texture = NULL;
				//ComPtr<IDirect3DTexture9> a;
				//ComPtr<LPDIRECT3DTEXTURE9> a;
				//xData->textures_[i]->Name;
			}
		}
		//バッファの解放
		const ULONG buf_count = buf->Release();
		
		BOOST_ASSERT(!buf_count);
		return xData;

	}

}
