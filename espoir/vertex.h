#pragma once

//#define FVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

//���_�\����
template<typename RealType>
struct VertexImpl{
		RealType x,y,z; //���_���W
		RealType rhw; //���1.0?
		D3DCOLOR diffuse; //���ˌ�
};

typedef VertexImpl<LONG> VertexL;