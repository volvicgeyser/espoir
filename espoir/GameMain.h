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
		void Render3D();
		void Update();
	};

}