#include "StdAfx.h"
#include "Graphic.h"

namespace espoir{

Graphic::Graphic(SPGraphicInfo gInfo)
{
	if(gInfo_.get() == NULL)
		this->gInfo_ = gInfo;
}

Graphic::~Graphic(void)
{
}


}