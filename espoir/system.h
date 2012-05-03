#pragma once
#include"singleton.h"
#include"DX3D9Creation.h"
#include"DXDeviceCreation.h"
#include"DXFormCreation.h"
#include"xfile.h"
#include "gametime.h"
namespace espoir{

	//Singleton‚ðsys‚ÅˆÍ‚Á‚Ätypedef
	namespace sys{
		typedef SPSingleton<IDirect3D9, DX3D9Creation, ComPtr> Direct3D;
		typedef SPSingleton<IDirect3DDevice9, DXDeviceCreation, ComPtr> Device;
		typedef SPSingleton<Form, DXFormCreation> Form;
		typedef SPSingleton<std::vector<XFile> > Models;
		typedef SPSingleton<GameTime<> > Time;
	}

}
