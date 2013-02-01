#include"stdafx.h"
#include"vertex.h"

namespace espoir{

Vertex::Vertex(int nPrimitive){

		LPDIRECT3DVERTEXBUFFER9 tmp_vertexBuf = NULL;

		//多分、描画毎にVertexBufferを生成するのは効率が悪い
		if (FAILED( 
			sys::Device::GetInst()->CreateVertexBuffer(nPrimitive * sizeof( VertexImplF ),
					0, D3DFVF_CUSTOMVERTEX,
					D3DPOOL_DEFAULT, &tmp_vertexBuf, NULL) ) )
		{
#ifdef _DEBUG
			throw std::runtime_error("VertexBufferの作成に失敗");
#else
			MessageBox(NULL, _T("VertextBufferの作成に失敗しました"), _T("err"), MB_OK);
#endif
		}

		if(!tmp_vertexBuf)
		{
			DOut dout;
			dout << _T("バーテックスバッファの初期化に失敗しました") << DSTM << std::endl;
		}

		this->vertexBuffer = SPVertexBuffer(tmp_vertexBuf, false);
	}

}