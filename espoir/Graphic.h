#pragma once
#include"GraphicInfo.h"
//#include"vertex.h"

namespace espoir{
class Graphic
{

private:
	
	//std::vector<Vertex> vertexArray;
public:
	Graphic();

	//�e�L�X�g���b�Z�[�W�̕\��
	void DrawString(String text);

	//�~�̕`��
	void DrawCircle(const RECT& rect);

	//�ݒ肳�ꂽ�l�p�`�̒��_�����ɕ`��
	void DrawRect();

	//�l�p�`�̒��_��ݒ�
	void SetRect(const RECT& rect);

	~Graphic(void);
};

}
