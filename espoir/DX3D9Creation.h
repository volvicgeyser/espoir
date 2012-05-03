#pragma once

#include"intrusive_func.h"
#include"ComPtr.h"
namespace espoir{

template <class ObjType>
class DX3D9Creation{
	typedef ComPtr<IDirect3D9> SPObjType;
public:
	static SPObjType Create(){
		IDirect3D9* tmp = Direct3DCreate9(D3D_SDK_VERSION);
		if(!tmp){
			throw std::runtime_error("Direct3Dの初期化に失敗しました");
		}
		SPObjType obj = SPObjType(tmp);
		
		//obj.Attach(tmp);
		if(obj == NULL){
			throw std::runtime_error("スマートポインタに格納できていません");
		}
		
		//テスト
		//obj->AddRef();
		return obj;
	}
};

template <class ObjType>
class old_DX3D9Creation{
//SP_TDEF(ObjType);
typedef boost::intrusive_ptr<ObjType> SPObjType ;
public:

	static SPObjType Create(){
		//Direct3D生成
		const IDirect3D9* tmp = Direct3DCreate9(D3D_SDK_VERSION);
		if(!tmp)
			throw std::runtime_error("Direct3Dの初期化に失敗しました");
		const SPObjType obj(tmp, false);
		return obj;
	}
private:
	struct Direct3DDeleter{
		template<class T>
		void operator()(T* t){
			if(!t){
				throw std::runtime_error("Direct3Dが初期化されていないか、不正に削除されています");
			}
			t->Release();
			t=NULL;
		}
	};
};

}
