#pragma once
#include"GraphicInfo.h"

namespace espoir{
class Graphic
{

private:
public:
	Graphic();

	//�e�L�X�g���b�Z�[�W�̕\��
	void DrawString(String text);

	//�~�̕`��
	void DrawCircle(const RECT& rect);

	//�l�p�`�̕`��
	void DrawRect(const RECT& rect);


	~Graphic(void);
};

}