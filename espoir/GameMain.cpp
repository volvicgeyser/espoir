#include"stdafx.h"
#include"GameMain.h"
#include"debug.h"
#include"xfile.h"
#include"system.h"
#include"vertex.h"
#include"font.h"

namespace espoir{

static float modelZ = 0;

//ゲーム内容の初期化処理
GameMain::GameMain(){
    //sys::Models::GetInst()->push_back(SPXFileData(XFile::Load(_T("../../x/kabotha_sensi.x"))));
    //sys::Models::GetInst()->push_back(SPXFileData(XFile::Load(_T("../../x/tiger.x"))));
	//sys::Models::GetInst()->push_back(SPXFileData(XFile::Load(_T("../../x/green_box.x"))));
	sys::Models::GetInst()->push_back(SPXFileData(XFile::Load(_T("../../x/violin.x"))));
	//sys::Models::GetInst()->push_back(SPXFileData(XFile::Load(_T("../../x/box3.x"))));
	//sys::Models::GetInst()->push_back(SPXFileData(XFile::Load(_T("../../x/kame.x"))));

	//DOut dout;
	//dout << "DirectInput初期化テスト" << std::endl;
	//sys::Input::GetInst();

	//Z軸
	const LONG z = 1;

	const RECT rect = {10, 10, 100, 100};
	//四角形のvertex
	const VertexImplL pt[4] = {
		{rect.left, rect.top, z, 1, 0xFFFF0000},
		{rect.left, rect.bottom, z, 1, 0xFF0000FF},
		{rect.right, rect.bottom, z, 1, 0xFF0000FF},
		{rect.right, rect.top, z, 1, 0xFF0000FF}
	};

	//フォントのテスト	
	SP_TDEF(Font);
	SPFont font = boost::make_shared<Font>( (Format(_T("MS ゴシック"))).str() );
}

//ゲームの描画
void GameMain::Render(){
	//描画開始
//    const HRESULT hrClear = sys::Device::GetInst()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 50), 1.0f, 0);
	
	const HRESULT hrClear = sys::Device::GetInst()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0xff), 1.0f, 0);
	//正しく画面クリアされたかどうかtest
	EXPECT_HRESULT_SUCCEEDED(hrClear);

	//3Dの描画
	if(SUCCEEDED(sys::Device::GetInst()->BeginScene())){
		//フォントの描画テスト
		sys::DebugFont::GetInst()->DrawString( Format( _T("デバッグ実行中") ).str() );

		//描画環境の設定
		D3DXMATRIXA16 world;
		D3DXMatrixRotationY(&world, sys::Time::GetInst()->GetTimeApp() / 1000.0f);
		sys::Device::GetInst()->SetTransform(D3DTS_WORLD, &world);
//        D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
		D3DXVECTOR3 vEyePt(modelZ, 3.0f, -4.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 view;
		D3DXMatrixLookAtLH(&view, &vEyePt, &vLookatPt, &vUpVec);
		sys::Device::GetInst()->SetTransform(D3DTS_VIEW, &view);
		D3DXMATRIXA16 proj;

		//視野角　アスペクト比　最近接距離　最遠方距離
		D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI/ 4,1.0f,0.01f,100.0f);

		sys::Device::GetInst()->SetTransform(D3DTS_WORLD, &world);
		sys::Device::GetInst()->SetTransform(D3DTS_VIEW, &view);
		sys::Device::GetInst()->SetTransform(D3DTS_PROJECTION, &proj);
		

		//モデルを描画する関数オブジェクト
		//tuple<XFileのデータ(SmartPtr), ループカウンタ>
//        struct DrawModelFunctor{
//            void operator()(boost::tuples::tuple<SPXFileData, int> t){

//                i番目の要素
//                SPXFileData xData;

//                ループカウンタi
//                int i;

//                boost::tie(xData, i) = t;

//                BOOST_ASSERT(xData);

//                EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->SetMaterial( &xData->meshMaterials_[i] ));
//                
//                EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->SetTexture( 0, xData->textures_[i].GetRef() ));

//                xData->mesh_->DrawSubset(i);
//            }
//        };

		//描画
//        boost::for_each(
//            boost::combine(
//                *sys::Models::GetInst(), 
//                boost::counting_range(0, static_cast<int>(sys::Models::GetInst()->size() ) )
//            ),
//        DrawModelFunctor() );

//        

		//モデルデータの表示
		for(XFileArray::iterator it = sys::Models::GetInst()->begin(); it != sys::Models::GetInst()->end(); it++){
			const DWORD size = (*it)->numMaterials_;
			BOOST_ASSERT(0 < size);
			BOOST_ASSERT(size == (*it)->meshMaterials_.size());

			//マテリアルをセット
			for(DWORD i = 0; i < size; i++){
				sys::Device::GetInst()->SetMaterial( &(*it)->meshMaterials_.at(i) ); 
			}
			//テクスチャをセット
			//for(DWORD i = 0; i < (*it)->textures_.size(); i++){
			for(DWORD i = 0; i < size; i++){
				//if((*it)->textures_.at(i) != NULL){
					sys::Device::GetInst()->SetTexture(0, (*it)->textures_.at(i).GetRef() );
					(*it)->mesh_->DrawSubset(i);
				//}
			}
			 
		}

		//四角形のサイズ
//        const RECT rect2 = {200, 200, 250, 250};
//        const RECT rect3 = {2, 2, 4, 4};
//        const RECT rect4 = {0,0, 1000, 1000};
//        const RECT rect5 = {100, 100 ,50, 50};
//        const RECT rect6 = {100,100,150,150};
//        const RECT rect7 = {50, 50, 100, 100};


		//四角形の描画テスト
//        sys::Graphic::GetInst()->DrawRect(rect2);
//        sys::Graphic::GetInst()->DrawRect(rect3);
//        sys::Graphic::GetInst()->DrawRect(rect4);
//        sys::Graphic::GetInst()->DrawRect(rect5);
//        sys::Graphic::GetInst()->DrawRect(rect6);
//        sys::Graphic::GetInst()->DrawRect(rect7);

//        this->dinfo_->g->DrawRect(rect2);
//        this->dinfo_->g->DrawRect(rect3);
//        this->dinfo_->g->DrawRect(rect4);
//        this->dinfo_->g->DrawRect(rect5);
//        this->dinfo_->g->DrawRect(rect6);
//        this->dinfo_->g->DrawRect(rect7);

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

	//小さすぎて描画できない
//	const RECT circle_rect3 = {50, 50, 51, 51};
//    const RECT circle_rect4 = {0, 0, 1, 1};
//
//    const RECT circle_rect5 = {1000, 1000, 1500, 1500};


	//合格
//    const RECT circle_rect6 = {0, 0, 650, 550};

	//円を描画
//    sys::Graphic::GetInst()->DrawCircle(circle_rect1);
//    sys::Graphic::GetInst()->DrawCircle(circle_rect2);

	//小さすぎて描画できない
//    sys::Graphic::GetInst()->DrawCircle(circle_rect3);
//    sys::Graphic::GetInst()->DrawCircle(circle_rect4);

	//大きすぎても描画できない
//    sys::Graphic::GetInst()->DrawCircle(circle_rect5);

	//合格
//    sys::Graphic::GetInst()->DrawCircle(circle_rect6);

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

	//キーの数
	const DWORD max_key = 256;

	boost::array<BYTE, max_key> keyState;

	sys::InputDevice::GetInst()->Acquire();

	//キーボード処理
	const HRESULT devStateErr = sys::InputDevice::GetInst()->GetDeviceState(
			max_key, keyState.begin());

	if(SUCCEEDED(devStateErr)){
		//Escキーで終了
		if(keyState[DIK_ESCAPE]&0xf0) PostMessage(sys::Form::GetInst()->GetHandle(), WM_CLOSE, 0, 0);
		if(keyState[DIK_J]){
			//j key
			modelZ--;
		}
		if(keyState[DIK_K]){
			//k key
			modelZ++;
		}
		if(keyState[DIK_L]){
			//l key
		}
		if(keyState[DIK_H]){
			//h key
		}
		if(keyState[DIK_Q]){
			PostMessage(sys::Form::GetInst()->GetHandle(), WM_CLOSE, 0, 0);
		}
#ifdef _DEBUG
		if(keyState[DIK_D]){
			//call debug menu
		}
#endif
	}
	
}


}
