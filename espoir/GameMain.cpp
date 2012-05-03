#include"stdafx.h"
#include"GameMain.h"
#include"debug.h"
#include"xfile.h"
#include"system.h"
namespace espoir{


GameMain::GameMain(SPDXInfo info){
	this->dinfo_ = info;

	XFile(_T("../../x/kabotha_sensi.x"));
}

//ゲームの描画
void GameMain::Render(){
	
	//描画開始
	const HRESULT hrClear = sys::Device::GetInst()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 50), 1.0f, 0);
	

	//3Dの描画
	if(SUCCEEDED(sys::Device::GetInst()->BeginScene())){
		//描画環境の設定
		D3DXMATRIXA16 world;
		D3DXMatrixRotationY(&world, sys::Time::GetInst()->GetStartTime() / 1000.0f);
		sys::Device::GetInst()->SetTransform(D3DTS_WORLD, &world);
		D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 view;
		D3DXMatrixLookAtLH(&view, &vEyePt, &vLookatPt, &vUpVec);
		sys::Device::GetInst()->SetTransform(D3DTS_VIEW, &view);
		D3DXMATRIXA16 proj;
		D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI/ 4,1.0f,1.0f,100.0f);
		sys::Device::GetInst()->SetTransform(D3DTS_PROJECTION, &proj);

		//for(DWORD i = 0; i < numMaterials; i++){
			//sys::Device::GetInst()->SetMaterial( // マテリアル);
			//sys::Device::GetInst()->SetTexture( //テクスチャ);
			//メッシュのドローサブセット
			
		//}
		sys::Device::GetInst()->EndScene();

	}
	
	//正しく画面クリアされたかどうかtest
	EXPECT_HRESULT_SUCCEEDED(hrClear);

	//left top right bottom
	const RECT rect = {50, 50, 100, 100};

	if(this->dinfo_->g != NULL)
		this->dinfo_->g->DrawCircle(rect);
	else{
		DOut dout;
		dout << _T("graphicがNULLです ") << DSTM << std::endl;
	}

	//次のバッファのコンテンツをプレゼンテーション
	sys::Device::GetInst()->Present(NULL, NULL, NULL, NULL);
}

//ゲームのアップデート処理
void GameMain::Update(){
	
}


}
