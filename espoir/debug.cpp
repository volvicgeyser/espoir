#include"stdafx.h"
#include"debug.h"


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