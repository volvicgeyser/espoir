#pragma once


//デバッグウィンドウを使う
//#define USE_DX_DBG_WND;


#ifdef _MSC_VER
#else
#define OutputDebugString(str) std::cout << str << std::endl
#define _CrtSetDbgFlag(str)
#endif