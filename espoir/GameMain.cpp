#include"stdafx.h"
#include"GameMain.h"
#include"debug.h"
#include"xfile.h"
#include"system.h"

namespace espoir{


//ゲーム内容の初期化処理
GameMain::GameMain(SPDXInfo info){
	this->dinfo_ = info;

	//xfileを読み込まない
	//sys::Models::GetInst()->push_back(SPXFileData(XFile::Load(_T("../../x/kabotha_sensi.x"))));
}

//ゲームの描画
void GameMain::Render(){
	
	BOOST_ASSERT(this->dinfo_);
	BOOST_ASSERT(this->dinfo_->g);

	//描画開始
	const HRESULT hrClear = sys::Device::GetInst()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 50), 1.0f, 0);
	
	//正しく画面クリアされたかどうかtest
	EXPECT_HRESULT_SUCCEEDED(hrClear);




	//3Dの描画
	if(SUCCEEDED(sys::Device::GetInst()->BeginScene())){
		
		//描画環境の設定
		D3DXMATRIXA16 world;
		D3DXMatrixRotationY(&world, sys::Time::GetInst()->GetTimeApp() / 1000.0f);
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
		

		//モデルを描画する関数オブジェクト
		//tuple<XFileのデータ(SmartPtr), ループカウンタ>
        struct DrawModelFunctor{
			void operator()(boost::tuples::tuple<SPXFileData, int> t){

				//i番目の要素
				SPXFileData xData;

				//ループカウンタi
				int i;

				boost::tie(xData, i) = t;

				BOOST_ASSERT(xData.get());

                EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->SetMaterial( &xData->meshMaterials_[i] ));
				
				//for comptr
				EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->SetTexture( 0, xData->textures_[i].GetRef() ));

				//for intrusive_ptr
				//EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->SetTexture( 0, xData->textures_[i].get() ));
                
				//sys::Device::GetInst()->SetTexture( 0, xData->textures_[i].get() );

                xData->mesh_->DrawSubset(i);
            }
        };

		//描画
		boost::for_each(
            boost::combine(
				*sys::Models::GetInst(), 
				boost::counting_range(0, static_cast<int>(sys::Models::GetInst()->size() ) )
			),
		DrawModelFunctor() );

		
		//四角形のサイズ
		const RECT rect2 = {200, 200, 250, 250};
		const RECT rect3 = {2, 2, 4, 4};
		const RECT rect4 = {0,0, 1000, 1000};
		const RECT rect5 = {100, 100 ,50, 50};
		const RECT rect6 = {100,100,150,150};
		const RECT rect7 = {50, 50, 100, 100};


		//四角形の描画テスト
		this->dinfo_->g->DrawRect(rect2);
		this->dinfo_->g->DrawRect(rect3);
		this->dinfo_->g->DrawRect(rect4);
		this->dinfo_->g->DrawRect(rect5);
		this->dinfo_->g->DrawRect(rect6);
		this->dinfo_->g->DrawRect(rect7);

		//プリミティブ描画てすと
		//    try{
		//        sys::Device::GetInst()->DrawPrimitive(D3DPT_TRIANGLELIST,
		//            0,
		//            2);
		//    }
		//    catch(TCHAR* str){
		//        const String tmp = str;
		//        ShowError(tmp);
		//    }

		//描画終了関数を呼び出すと共に成功したかどうかテスト
		EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->EndScene());

	}
	else
	{
		throw std::runtime_error("3Dの描画に失敗しました");
	}
	
	//円のサイズ left top right bottom
	const RECT circle_rect1 = {100, 100, 150, 150};
	const RECT circle_rect2 = {10, 10, 15, 15};
	const RECT circle_rect3 = {50, 50, 51, 51};
	const RECT circle_rect4 = {0, 0, 1, 1};
	const RECT circle_rect5 = {1000, 1000, 1500, 1500};

	//円を描画
//    this->dinfo_->g->DrawCircle(circle_rect1);
//    this->dinfo_->g->DrawCircle(circle_rect2);
//    this->dinfo_->g->DrawCircle(circle_rect3);
//    this->dinfo_->g->DrawCircle(circle_rect4);
//    this->dinfo_->g->DrawCircle(circle_rect5);

	const RECT rect2 = {200, 200, 250, 250};
	const RECT rect3 = {2, 2, 4, 4};
	const RECT rect4 = {0,0, 1000, 1000};
	const RECT rect5 = {100, 100 ,50, 50};
	const RECT rect6 = {100,100,150,150};
	const RECT rect7 = {50, 50, 100, 100};


	//ここでも四角形を描画してみる
//    this->dinfo_->g->DrawRect(rect2);
//    this->dinfo_->g->DrawRect(rect3);
//    this->dinfo_->g->DrawRect(rect4);
//    this->dinfo_->g->DrawRect(rect5);
//    this->dinfo_->g->DrawRect(rect6);
//    this->dinfo_->g->DrawRect(rect7);


	//次のバッファのコンテンツをプレゼンテーション
	sys::Device::GetInst()->Present(NULL, NULL, NULL, NULL);
}

void GameMain::Render3D(){
}

//ゲームのアップデート処理
void GameMain::Update(){
	
}


}
