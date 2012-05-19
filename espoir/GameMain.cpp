#include"stdafx.h"
#include"GameMain.h"
#include"debug.h"
#include"xfile.h"
#include"system.h"
namespace espoir{

//�Q�[�����e�̏���������
GameMain::GameMain(SPDXInfo info){
	this->dinfo_ = info;
	sys::Models::GetInst()->push_back(SPXFileData(XFile::Load(_T("../../x/kabotha_sensi.x"))));
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

                sys::Device::GetInst()->SetMaterial( &xData->meshMaterials_[i] );
                sys::Device::GetInst()->SetTexture( 0, xData->textures_[i] );

                //���[�v�񐔂��K�v�c
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

//        for(){
//        }
		//for(DWORD i = 0; i < numMaterials; i++){
			//sys::Device::GetInst()->SetMaterial( // �}�e���A��);
			//sys::Device::GetInst()->SetTexture( //�e�N�X�`��);
			//���b�V���̃h���[�T�u�Z�b�g
			
		//}
		
		//�`��I���֐����Ăяo���Ƌ��ɐ����������ǂ����e�X�g
		EXPECT_HRESULT_SUCCEEDED(sys::Device::GetInst()->EndScene());

	}
	else
	{
		throw std::runtime_error("3D�̕`��Ɏ��s���܂���");
	}
	


	//�~�̃T�C�Y left top right bottom
	const RECT rect = {50, 50, 100, 100};

	//�~��`��
	this->dinfo_->g->DrawCircle(rect);

	//���̃o�b�t�@�̃R���e���c���v���[���e�[�V����
	sys::Device::GetInst()->Present(NULL, NULL, NULL, NULL);
}

//�Q�[���̃A�b�v�f�[�g����
void GameMain::Update(){
	
}


}
