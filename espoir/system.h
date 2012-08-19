#pragma once
#include"ComPtr.h"
#include"spsingleton.h"
#include"singleton.h"
#include"DX3D9Creation.h"
#include"DXDeviceCreation.h"
#include"DXFormCreation.h"
#include"DXBackBufferCreation.h"
#include"DXInputCreation.h"
#include"DXInputDeviceCreation.h"
#include"xfile.h"
#include "gametime.h"
#include "graphic.h"
#include "FontCreation.h"
#include "font.h"

namespace espoir{

	SP_TDEF(XFileData);
	typedef std::vector<SPXFileData> XFileArray;

	//class Graphic;
	//SingletonÇsysÇ≈àÕÇ¡Çƒtypedef
	namespace sys{

//        typedef SPSingleton<IDirect3D9, DX3D9Creation, boost::intrusive_ptr> Direct3D;
//
		//typedef Singleton<Form, DXFormCreation> DXForm;
		typedef SPSingleton<IDirect3D9, DX3D9Creation, ComPtr> Direct3D;
		typedef SPSingleton<IDirect3DDevice9, DXDeviceCreation, ComPtr> Device;
		typedef SPSingleton<IDirect3DSurface9, DXBackBufferCreation, ComPtr> Backbuf;
		typedef SPSingleton<IDirectInputDevice8, DXInputDeviceCreation, boost::intrusive_ptr> InputDevice;
		typedef SPSingleton<IDirectInput8, DXInputCreation, boost::intrusive_ptr> Input;
		
		//staticÇ…ê∂ê¨
		typedef Singleton<Graphic> Graphic;

//		typedef SPSingleton<Form, DXFormCreation> Form;
		typedef Singleton<Form, DXFormCreation> Form;

		typedef Singleton<GameTime<> > Time;
		typedef Singleton<XFileArray> Models;
		//typedef std::vector<Font> FontArray;
		
		typedef SPSingleton<Font, DebugFontCreation> DebugFont;

	}
	namespace debug{
		//typedef Singleton<DOut> Dout;
		//extern DOut dout;
	}

}
