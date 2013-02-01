#pragma once
#include"system.h"

//#define FVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
namespace espoir{

//頂点構造体
template<typename RealType>
struct VertexImpl{
		RealType x,y,z; //頂点座標
		RealType rhw; //常に1.0?
		D3DCOLOR diffuse; //反射光
};

typedef VertexImpl<LONG> VertexImplL;

struct Vertex{

	//頂点構造体
	VertexImplL vertex;
	typedef boost::intrusive_ptr<IDirect3DVertexBuffer9> SPVertexBuffer;

	//バーテックスバッファ
	SPVertexBuffer vertexBuffer;

	static const DWORD D3DFVF_CUSTOMVERTEX = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	Vertex(RECT rect){

		LPDIRECT3DVERTEXBUFFER9 tmp_vertexBuf = NULL;

		//多分、描画毎にVertexBufferを生成するのは効率が悪い
		if (FAILED( 
			sys::Device::GetInst()->CreateVertexBuffer( 3 * sizeof( VertexImplL ),
					0, D3DFVF_CUSTOMVERTEX,
					D3DPOOL_DEFAULT, &tmp_vertexBuf, NULL) ) )
		{
#ifdef _DEBUG
			throw std::runtime_error("VertexBufferの作成に失敗");
#else
			MessageBox(NULL, _T("VertextBufferの作成に失敗しました"), _T("err"), MB_OK);
#endif
		}

		if(this->vertexBuffer)
			throw std::runtime_error("存在します");
		this->vertexBuffer = SPVertexBuffer(tmp_vertexBuf, false);

	}
};

}
