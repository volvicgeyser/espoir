#pragma once
#include"ComPtr.h"

namespace espoir{

//GDI�̕`��Ȃ̂Œx���B

//�t�H���g�̏��\����
struct FontInfo{

	//�����̍���
	INT height;

	//�����̕�
	UINT width;

	//�~�b�v�}�b�v���x���̐�
	UINT mipLevels;

	//�C�^���b�N���ǂ���
	BOOL italic;

	//�t�H���g�̕����Z�b�g
	DWORD charSet;

	//�o�͐��x
	DWORD outputPrecision;

	//�o�͕i��
	DWORD quality;

	//�s�b�`�ƃt�@�~���C���f�b�N�X
	DWORD pitchAndFamily;

	//�t�H���g��
	String pFacename;
	
	//�t�H���g�̃|�C���^
	boost::intrusive_ptr<ID3DXFont> ppFont;
};




}
