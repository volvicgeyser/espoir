#include"stdafx.h"
#include"debug.h"

namespace espoir{



espoir::DStreamBuf::DStreamBuf(){
	ZeroMemory(m_acBuffer, sizeof(m_acBuffer));
}

Int_type espoir::DStreamBuf::overflow(Int_type iChar){
			if(iChar != EOF){
				m_acBuffer[0] = iChar;

				//デバッガに出力
				OutputDebugString(m_acBuffer);
			}
			return iChar;
}

espoir::DOut::~DOut(){
		if(this->m_StmBuf != NULL){
			delete this->m_StmBuf;
		}
}






//エラー用のダイアログ表示関数
void ShowError(String str)
{
		MessageBox(NULL, str.c_str(),  _T(""), MB_OK || MB_ICONEXCLAMATION);
}

void ShowError(String str, String line){
	String s;
	s = str + line;
	MessageBox(NULL, s.c_str(), _T(""), MB_OK || MB_ICONEXCLAMATION);
}




}