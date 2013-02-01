#include"stdafx.h"
#include"vertex.h"

namespace espoir{

Vertex::Vertex(int nPrimitive){

		LPDIRECT3DVERTEXBUFFER9 tmp_vertexBuf = NULL;

		//�����A�`�斈��VertexBuffer�𐶐�����̂͌���������
		if (FAILED( 
			sys::Device::GetInst()->CreateVertexBuffer(nPrimitive * sizeof( VertexImplF ),
					0, D3DFVF_CUSTOMVERTEX,
					D3DPOOL_DEFAULT, &tmp_vertexBuf, NULL) ) )
		{
#ifdef _DEBUG
			throw std::runtime_error("VertexBuffer�̍쐬�Ɏ��s");
#else
			MessageBox(NULL, _T("VertextBuffer�̍쐬�Ɏ��s���܂���"), _T("err"), MB_OK);
#endif
		}

		if(!tmp_vertexBuf)
		{
			DOut dout;
			dout << _T("�o�[�e�b�N�X�o�b�t�@�̏������Ɏ��s���܂���") << DSTM << std::endl;
		}

		this->vertexBuffer = SPVertexBuffer(tmp_vertexBuf, false);
	}

}