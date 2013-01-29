#include "StdAfx.h"
#include "Graphic.h"
#include "debug.h"
#include "intrusive_func.h"
//#include "Singleton.h"
//#include "DXDeviceCreation.h"
#include "system.h"
#include "vertex.h"

namespace espoir{

Graphic::Graphic()
{
}


void Graphic::DrawCircle(const RECT& rect)
{
	//�f�o�C�X�R���e�L�X�g
	HDC hDC;

	//if(this->gInfo_->backBuf != NULL){
	const HRESULT hr = sys::Backbuf::GetInst()->GetDC(&hDC);
//        const HRESULT hr = this->gInfo_->backBuf->GetDC(&hDC);

	//������DC�擾�ł�����test
	EXPECT_HRESULT_SUCCEEDED(hr);

	if(hr == S_OK){

		//�񎟌��̉~��`��
		const BOOL rEllipse = Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
			
		//�~���������`��ł��Ă��邩�ǂ����e�X�g
		EXPECT_NE(rEllipse, FALSE);
 			
		sys::Backbuf::GetInst()->ReleaseDC(hDC);
//        this->gInfo_->backBuf->ReleaseDC(hDC);
	}
	else{
		//DOut dout;
		//dout << _T("Error: ") << hr << _T(" �~�̕`��Ɏ��s���܂��� ") << DSTM << std::endl;

		//throw std::runtime_error("�~�̕`��Ɏ��s���܂���");

		const char* str = "�~�̕`��Ɏ��s���܂���";
		//�^�`�F�b�N�e�X�g
		typedef ::testing::Types<long> testTypes;
			TYPED_TEST_CASE(getdc_result_test, testTypes);

		switch(hr){
			case E_FAIL:
				throw std::runtime_error( (boost::format("%1% E_FAIL") % str).str() );
				break;
			case D3DERR_INVALIDCALL :
				throw std::runtime_error( (boost::format("%1% �����ȌĂяo��") % str).str() );
				break;
		}
	}
}

//�摜�̃��[�h
Graphic::SPTexture Graphic::LoadGraphic(const String& filename)
{
	//���[�h���ꂽ�摜�t�@�C�������o���Ă���
	static std::vector<String> loadedName;

	if(std::find( loadedName.begin(), loadedName.end(), filename) != loadedName.end())
	{
		//���Ƀ��[�h�ς݂̉摜�f�[�^�͖�������
		SPTexture spTexture(NULL);
		return spTexture;
	}
	
	//���[�h���ꂽ�t�@�C������ۑ�����
	loadedName.push_back(filename);

	LPDIRECT3DTEXTURE9 texture = NULL;
	if(FAILED(D3DXCreateTextureFromFile( sys::Device::GetInst().GetRef(), filename.c_str(), &texture )))
	{
		DOut dout;
		dout << _T("�摜�̓ǂݍ��݂Ɏ��s���܂���") << DSTM << std::endl;
		dout << _T("�t�@�C����:") << filename << std::endl;
		throw std::runtime_error("�摜�̓ǂݍ��݂Ɏ��s���܂���");
	}

	//const ComPtr<IDirect3DTexture9> spTexture(texture);
	SPTexture spTexture(texture, false);

	return spTexture;
}

//�l�p�`�̕`��
void Graphic::DrawRect(){
}

void Graphic::SetRect(const RECT& rect){
}

//�摜���w��̈ʒu�ɕ`��
void Graphic::DrawGraphic(const SPTexture& spTexture, const RECT& rect)
{
	if(!spTexture)
	{
		return;
	}
	const D3DXVECTOR3 vec3Center(0, 0, 0);
	const D3DXVECTOR3 vec3Position(220, 170, 0);

	typedef std::map<SPTexture, SPSprite> SpriteMap;

	SPSprite spSprite;
	static SpriteMap spriteMap;
	if( spriteMap.find(spTexture) == spriteMap.end() )
	{
		//�Y���̃e�N�X�`���[�f�[�^�����݂��Ȃ��ꍇ
		
		LPD3DXSPRITE sprite = NULL;

		if(FAILED(D3DXCreateSprite(sys::Device::GetInst().GetRef(), &sprite)))
		{
			DOut dout;
			dout << _T("�X�v���C�g�̏������Ɏ��s���܂���") << DSTM;
		}
		spSprite = SPSprite(sprite, false);

		//�e�N�X�f�[�^���L�[�ɃX�v���C�g���i�[
		spriteMap[spTexture] = spSprite;
	}
	else
	{
		//�Y���̃e�N�X�`���[�f�[�^�����݂���ꍇ
		spSprite = spriteMap[spTexture];
	}

	
	RECT lrect = rect;

	//�T�C�Y�̍���������0�Ȃ�摜�T�C�Y�������擾
	if(rect.bottom == 0 || rect.right == 0)
	{
		D3DSURFACE_DESC desc;
		if(spTexture->GetLevelDesc(0, &desc) )
		{
			//�摜�T�C�Y�̎擾�Ɏ��s
		}
		else
		{
			lrect.bottom = desc.Height;
			lrect.right = desc.Width;
		}
	}

	spSprite->Begin(D3DXSPRITE_ALPHABLEND);
    spSprite->Draw( spTexture.get(),
                   &lrect,
                   &vec3Center,
                   &vec3Position,
                   0xFFFFFFFF);
	spSprite->End();
}

Graphic::~Graphic(void)
{
}


}
