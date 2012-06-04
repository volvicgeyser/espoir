#include"stdafx.h"
#include"GameMain.h"
#include"debug.h"
#include"xfile.h"
#include"system.h"

namespace espoir{


//�Q�[�����e�̏���������
GameMain::GameMain(SPDXInfo info){
	this->dinfo_ = info;

	//xfile��ǂݍ��܂Ȃ�
	//sys::Models::GetInst()->push_back(SPXFileData(XFile::Load(_T("../../x/kabotha_sensi.x"))));
}

//�Q�[���̕`��
void GameMain::Render(){
	
	BOOST_ASSERT(this->dinfo_);
	BOOST_ASSERT(this->dinfo_->g);

	//�`��J�n
	const HRESULT hrClear = sys::Device::GetInst()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 50), 1.0f, 0);
	
	//��������ʃN���A���ꂽ���ǂ���test
	EXPECT_HRESULT_SUCCEEDED(hrClear);




	//3D�̕`��
	if(SUCCEEDED(sys::Device::GetInst()->BeginScene())){
		
		//�`����̐ݒ�
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
		

		//���f����`�悷��֐��I�u�W�F�N�g
		//tuple<XFile�̃f�[�^(SmartPtr), ���[�v�J�E���^>
        struct DrawModelFunctor{
			void operator()(boost::tuples::tuple<SPXFileData, int> t){

				//i�Ԗڂ̗v�f
				SPXFileData xData;

				//���[�v�J�E���^i
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

		//�`��
		boost::for_each(
            boost::combine(
				*sys::Models::GetInst(), 
				boost::counting_range(0, static_cast<int>(sys::Models::GetInst()->size() ) )
			),
		DrawModelFunctor() );

		
		//�l�p�`�̃T�C�Y
		const RECT rect2 = {200, 200, 250, 250};
		const RECT rect3 = {2, 2, 4, 4};
		const RECT rect4 = {0,0, 1000, 1000};
		const RECT rect5 = {100, 100 ,50, 50};
		const RECT rect6 = {100,100,150,150};
		const RECT rect7 = {50, 50, 100, 100};


		//�l�p�`�̕`��e�X�g
		this->dinfo_->g->DrawRect(rect2);
		this->dinfo_->g->DrawRect(rect3);
		this->dinfo_->g->DrawRect(rect4);
		this->dinfo_->g->DrawRect(rect5);
		this->dinfo_->g->DrawRect(rect6);
		this->dinfo_->g->DrawRect(rect7);

		//�v���~�e�B�u�`��Ă���
		//    try{
		//        sys::Device::GetInst()->DrawPrimitive(D3DPT_TRIANGLELIST,
		//            0,
		//            2);
		//    }
		//    catch(TCHAR* str){
		//        const String tmp = str;
		//        ShowError(tmp);
		//    }

		//�`��I���֐����Ăяo���Ƌ��ɐ����������ǂ����e�X�g
		EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->EndScene());

	}
	else
	{
		throw std::runtime_error("3D�̕`��Ɏ��s���܂���");
	}
	
	//�~�̃T�C�Y left top right bottom
	const RECT circle_rect1 = {100, 100, 150, 150};
	const RECT circle_rect2 = {10, 10, 15, 15};
	const RECT circle_rect3 = {50, 50, 51, 51};
	const RECT circle_rect4 = {0, 0, 1, 1};
	const RECT circle_rect5 = {1000, 1000, 1500, 1500};

	//�~��`��
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


	//�����ł��l�p�`��`�悵�Ă݂�
//    this->dinfo_->g->DrawRect(rect2);
//    this->dinfo_->g->DrawRect(rect3);
//    this->dinfo_->g->DrawRect(rect4);
//    this->dinfo_->g->DrawRect(rect5);
//    this->dinfo_->g->DrawRect(rect6);
//    this->dinfo_->g->DrawRect(rect7);


	//���̃o�b�t�@�̃R���e���c���v���[���e�[�V����
	sys::Device::GetInst()->Present(NULL, NULL, NULL, NULL);
}

void GameMain::Render3D(){
}

//�Q�[���̃A�b�v�f�[�g����
void GameMain::Update(){
	
}


}
