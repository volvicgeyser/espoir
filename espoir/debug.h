#pragma once

namespace espoir{

//�f�o�b�O�o�͗p�X�g���[���I�u�W�F�N�g
class DStreamBuf : public Streambuf{
private:
	TCHAR m_acBuffer[2];
public:
	DStreamBuf();
	virtual Int_type overflow(Int_type iChar = EOF);
};


//�f�o�b�O�o�̓X�g���[��
//Visual Studio�́u�o�́v�ɏo�͂����
class DOut : public Ostream {
private:
	DStreamBuf* m_StmBuf;
public:
	DOut() : Ostream(m_StmBuf = new DStreamBuf){};
	~DOut();
	
};

}