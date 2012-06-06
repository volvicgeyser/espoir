#pragma once
#include"ComPtr.h"
#include"spsingleton.h"
#include"singleton.h"
#include"DX3D9Creation.h"
#include"DXDeviceCreation.h"
#include"DXFormCreation.h"
#include"DXBackBufferCreation.h"
#include"xfile.h"
#include "gametime.h"
#include "graphic.h"
namespace espoir{

	SP_TDEF(XFileData);
	typedef std::vector<SPXFileData> XFileArray;

	//SingletonÇsysÇ≈àÕÇ¡Çƒtypedef
	namespace sys{

//        typedef SPSingleton<IDirect3D9, DX3D9Creation, boost::intrusive_ptr> Direct3D;
//
		typedef SPSingleton<IDirect3D9, DX3D9Creation, ComPtr> Direct3D;
		typedef SPSingleton<IDirect3DDevice9, DXDeviceCreation, ComPtr> Device;
		typedef SPSingleton<IDirect3DSurface9, DXBackBufferCreation, ComPtr> Backbuf;
		
		//staticÇ…ê∂ê¨
		typedef Singleton<Graphic> Graphic;

//atl
//        typedef SPSingleton<IDirect3D9, DX3D9Creation, CComPtr> Direct3D;
//        typedef SPSingleton<IDirect3DDevice9, DXDeviceCreation, CComPtr> Device;


//		typedef SPSingleton<Form, DXFormCreation> Form;
		typedef Singleton<Form, DXFormCreation> Form;

		typedef Singleton<GameTime<> > Time;
		typedef Singleton<XFileArray> Models;
		//typedef Singleton<DOut> DOut;
	}
	namespace debug{
		//typedef Singleton<DOut> Dout;
		//extern DOut dout;
	}

}
