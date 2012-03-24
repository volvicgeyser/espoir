#pragma once
#include"GraphicInfo.h"

namespace espoir{
class Graphic
{
SP_TDEF(GraphicInfo);

private:
	SPGraphicInfo gInfo_;
public:
	Graphic(SPGraphicInfo gInfo);

	//�e�L�X�g���b�Z�[�W�̕\��
	void DrawString(String text);

	//�~�̕`��
	void DrawCircle(RECT rect);


	~Graphic(void);
};

}