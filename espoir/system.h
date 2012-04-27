#pragma once
#include"singleton.h"
#include"DX3D9Creation.h"
#include"DXFormCreation.h"

namespace espoir{

	//Singleton‚ðsys‚ÅˆÍ‚Á‚Ätypedef
	namespace sys{
		typedef SPSingleton<IDirect3D9, DX3D9Creation, ComPtr> Direct3D;
		typedef SPSingleton<Form, DXFormCreation> Form;
	}

}
