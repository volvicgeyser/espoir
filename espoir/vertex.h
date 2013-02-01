#pragma once
#include"system.h"


//const DWORD D3DFVF_CUSTOMVERTEX = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

//#define FVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
namespace espoir{

//頂点構造体
template<typename RealType>
struct VertexImpl{
		RealType x,y,z; //頂点座標
		FLOAT rhw; //常に1.0?
		D3DCOLOR diffuse; //反射光
		//RealType u, v; 	//　テクスチャ座標
};

//typedef VertexImpl<LONG> VertexImplL;
typedef VertexImpl<FLOAT> VertexImplF;

struct Vertex{

	//頂点構造体
	//VertexImplL vertex;
	typedef boost::intrusive_ptr<IDirect3DVertexBuffer9> SPVertexBuffer;

	//バーテックスバッファ
	SPVertexBuffer vertexBuffer;

	Vertex(int nPrimitive);
};

}
