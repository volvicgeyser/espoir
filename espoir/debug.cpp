#include"stdafx.h"
#include"debug.h"

namespace espoir{

espoir::DStreamBuf::DStreamBuf(){
	ZeroMemory(acBuf_, sizeof(acBuf_));
}

espoir::DStreamBuf::~DStreamBuf(){}

Int_type espoir::DStreamBuf::overflow(Int_type iChar){
		if(iChar != EOF){
			acBuf_[0] = iChar;

			//�f�o�b�K�ɏo��
			OutputDebugString(acBuf_);
		}
		return iChar;
}


espoir::DOut::~DOut(){
}


//�G���[�p�̃_�C�A���O�\���֐�
void ShowError(const String& str)
{
	MessageBox(NULL, str.c_str(),  _T(""), MB_OK || MB_ICONEXCLAMATION);
}

void ShowError(const String& str, const String& so, const String& line){
	const String s = str + _T(" source: ") + so + _T("line: ") + line;
	MessageBox(NULL, s.c_str(), _T(""), MB_OK || MB_ICONEXCLAMATION);
}




}
