#pragma once
//�}�N���W


//�X�}�[�g�|�C���^�œ����Ă�L�q�ɒu��������
#define SP(x) boost::shared_ptr<x>

//�X�}�[�g�|�C���^�œ���ꂽ�^���`����
#define SP_TDEF(name) typedef SP(name) BOOST_PP_CAT(SP, name);


//�t�@�C�������s�ԍ��\���}�N��
#define DSTM _T(" File: ") <<  __FILE__ << _T("Line: ") << __LINE__

//���[�v�}�N��(i��)
#define loop_i(n, statement) \
	for(int i = 0; i < n; i++){\
			statement\
	}
//���[�v�}�N��(j�Łj
#define loop_j(n, statement) \
	for(int j = 0; j < n; j++){\
		statement\
	}

