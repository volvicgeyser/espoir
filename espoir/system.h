#pragma once
#include"singleton.h"
#include"DX3D9Creation.h"
#include"DXDeviceCreation.h"
#include"DXFormCreation.h"
#include"xfile.h"
#include "gametime.h"
namespace espoir{

	SP_TDEF(XFileData);
	typedef std::vector<SPXFileData> XFileArray;

	//Singleton‚ðsys‚ÅˆÍ‚Á‚Ätypedef
	namespace sys{

//        typedef SPSingleton<IDirect3D9, DX3D9Creation, boost::intrusive_ptr> Direct3D;
//
		typedef SPSingleton<IDirect3D9, DX3D9Creation, ComPtr> Direct3D;
		typedef SPSingleton<IDirect3DDevice9, DXDeviceCreation, ComPtr> Device;

//atl
//        typedef SPSingleton<IDirect3D9, DX3D9Creation, CComPtr> Direct3D;
//        typedef SPSingleton<IDirect3DDevice9, DXDeviceCreation, CComPtr> Device;


		typedef SPSingleton<Form, DXFormCreation> Form;

		typedef Singleton<GameTime<> > Time;
		typedef Singleton<XFileArray> Models;
		//typedef Singleton<DOut> DOut;
	}
	namespace debug{
		//typedef Singleton<DOut> Dout;
		//extern DOut dout;
	}

}
