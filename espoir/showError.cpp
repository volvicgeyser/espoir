#include"stdafx.h"
#include"showError.h"

//�G���[�p�̃_�C�A���O�\���֐�
void espoir::ShowError(String str)
{
		MessageBox(NULL, str.c_str(),  _T(""), MB_OK || MB_ICONEXCLAMATION);
}

void espoir::ShowError(String str, String line){
	String s;
	s = str + line;
	MessageBox(NULL, s.c_str(), _T(""), MB_OK || MB_ICONEXCLAMATION);
}