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
	~Graphic(void);
};

}