#pragma once

namespace espoir{

//デバッグ出力用ストリームオブジェクト
class DStreamBuf : public Streambuf{
private:
	TCHAR m_acBuffer[2];
public:
	DStreamBuf();
	virtual Int_type overflow(Int_type iChar = EOF);
};


//デバッグ出力ストリーム
//Visual Studioの「出力」に出力される
class DOut : public Ostream {
private:
	DStreamBuf* m_StmBuf;
public:
	DOut() : Ostream(m_StmBuf = new DStreamBuf){};
	~DOut();
	
};

}