#pragma once

namespace espoir{

//デバッグ出力用ストリームオブジェクト
class DStreamBuf : public Streambuf{
private:
	TCHAR acBuf_[2];
public:
	DStreamBuf();
	virtual Int_type overflow(Int_type iChar = EOF);
	virtual ~DStreamBuf();
};


//デバッグ出力ストリーム
//Visual Studioの「出力」に出力される
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
