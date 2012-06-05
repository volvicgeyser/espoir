#pragma once

namespace espoir{

//�f�o�b�O�o�͗p�X�g���[���I�u�W�F�N�g
class DStreamBuf : public Streambuf{
private:
	TCHAR acBuf_[2];
public:
	DStreamBuf();
	virtual Int_type overflow(Int_type iChar = EOF);
	virtual ~DStreamBuf();
};


//�f�o�b�O�o�̓X�g���[��
//Visual Studio�́u�o�́v�ɏo�͂����
class DOut : public Ostream {
private:
	DStreamBuf stmBuf_;
public:
	DOut() : Ostream(&stmBuf_){}
	virtual ~DOut();
};

void ShowError(const String& str);
void ShowError(const String& str, const String& line);

}
