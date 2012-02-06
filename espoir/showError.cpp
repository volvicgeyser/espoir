#include"stdafx.h"
#include"showError.h"

//エラー用のダイアログ表示関数
void espoir::ShowError(String str)
{
		MessageBox(NULL, str.c_str(),  _T(""), MB_OK || MB_ICONEXCLAMATION);
}

void espoir::ShowError(String str, String line){
	String s;
	s = str + line;
	MessageBox(NULL, s.c_str(), _T(""), MB_OK || MB_ICONEXCLAMATION);
}