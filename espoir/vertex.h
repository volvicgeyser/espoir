#pragma once
#include"system.h"

//#define FVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
namespace espoir{

//���_�\����
template<typename RealType>
struct VertexImpl{
		RealType x,y,z; //���_���W
		RealType rhw; //���1.0?
		D3DCOLOR diffuse; //���ˌ�
};

typedef VertexImpl<LONG> VertexImplL;

struct Vertex{

	//���_�\����
	VertexImplL vertex;
	typedef boost::intrusive_ptr<IDirect3DVertexBuffer9> SPVertexBuffer;

	//�o�[�e�b�N�X�o�b�t�@
	SPVertexBuffer vertexBuffer;

	static const DWORD D3DFVF_CUSTOMVERTEX = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	Vertex(RECT rect){

		LPDIRECT3DVERTEXBUFFER9 tmp_vertexBuf = NULL;

		//�����A�`�斈��VertexBuffer�𐶐�����̂͌���������
		if (FAILED( 
			sys::Device::GetInst()->CreateVertexBuffer( 3 * sizeof( VertexImplL ),
					0, D3DFVF_CUSTOMVERTEX,
					D3DPOOL_DEFAULT, &tmp_vertexBuf, NULL) ) )
		{
#ifdef _DEBUG
			throw std::runtime_error("VertexBuffer�̍쐬�Ɏ��s");
#else
			MessageBox(NULL, _T("VertextBuffer�̍쐬�Ɏ��s���܂���"), _T("err"), MB_OK);
#endif
		}

		if(this->vertexBuffer)
			throw std::runtime_error("���݂��܂�");
		this->vertexBuffer = SPVertexBuffer(tmp_vertexBuf, false);

	}
};

}
