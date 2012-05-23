#pragma once

//#define FVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

//頂点構造体
template<typename RealType>
struct VertexImpl{
		RealType x,y,z; //頂点座標
		RealType rhw; //常に1.0?
		D3DCOLOR diffuse; //反射光
};

typedef VertexImpl<LONG> VertexL;