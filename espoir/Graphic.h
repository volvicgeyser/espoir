#pragma once
#include"GraphicInfo.h"
//#include"vertex.h"
#include"ComPtr.h"

namespace espoir{
class Graphic
{

private:
	//std::vector<Vertex> vertexArray;

public:
	//typedef ComPtr<IDirect3DTexture9> SPTexture;
	typedef boost::intrusive_ptr<IDirect3DTexture9> SPTexture;
	typedef boost::intrusive_ptr<ID3DXSprite> SPSprite;

	Graphic();

	//�e�L�X�g���b�Z�[�W�̕\��
	void DrawString(String text);

	//�~�̕`��
	void DrawCircle(const RECT& rect);

	//�ݒ肳�ꂽ�l�p�`�̒��_�����ɕ`��
	void DrawRect();

	//�l�p�`�̒��_��ݒ�
	void SetRect(const RECT& rect);

	//�摜�����[�h����
	SPTexture LoadGraphic(const String& filename);

	SPTexture LoadGraphicFromCache(const String& filename);

	void DrawGraphic(const SPTexture& spTexture, const RECT& rect);

	~Graphic(void);
};

}
