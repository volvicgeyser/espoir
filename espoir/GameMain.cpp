#include"stdafx.h"
#include"GameMain.h"
#include"debug.h"
namespace espoir{

	
GameMain::GameMain(SPDXInfo info){
	this->dinfo_ = info;
}

//�Q�[���̕`��
void GameMain::Render(){
	RECT rect;
	rect.left = 50;
	rect.top = 50;
	rect.right = 100;
	rect.bottom = 100;
	
	if(this->dinfo_->g != NULL)
		this->dinfo_->g->DrawCircle(rect);
	else{
		DOut dout;
		dout << _T("graphic��NULL�ł� ") << DSTM << std::endl;
	}
}

//�Q�[���̃A�b�v�f�[�g����
void GameMain::Update(){
	
}


}
