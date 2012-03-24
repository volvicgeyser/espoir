#include"stdafx.h"
#include"GameMain.h"
#include"debug.h"
namespace espoir{

	
GameMain::GameMain(SPDXInfo info){
	this->dinfo_ = info;
}

//ゲームの描画
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
		dout << _T("graphicがNULLです ") << DSTM << std::endl;
	}
}

//ゲームのアップデート処理
void GameMain::Update(){
	
}


}
