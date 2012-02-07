#pragma once
#include"DXInfo.h"

namespace espoir{
	class GameMain{
		SP_TDEF(DXInfo);
	private:
		SPDXInfo dinfo_;
	public:
		GameMain(SPDXInfo info);
		void Render();
		void Update();
	};

}