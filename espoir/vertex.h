#pragma once
#include"system.h"


//const DWORD D3DFVF_CUSTOMVERTEX = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

//#define FVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
namespace espoir{

//���_�\����
template<typename RealType>
struct VertexImpl{
		RealType x,y,z; //���_���W
		FLOAT rhw; //���1.0?
		D3DCOLOR diffuse; //���ˌ�
		//RealType u, v; 	//�@�e�N�X�`�����W
};

//typedef VertexImpl<LONG> VertexImplL;
typedef VertexImpl<FLOAT> VertexImplF;

struct Vertex{

	//���_�\����
	//VertexImplL vertex;
	typedef boost::intrusive_ptr<IDirect3DVertexBuffer9> SPVertexBuffer;

	//�o�[�e�b�N�X�o�b�t�@
	SPVertexBuffer vertexBuffer;

	Vertex(int nPrimitive);
};

}
