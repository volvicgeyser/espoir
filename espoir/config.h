#pragma once


//�f�o�b�O�E�B���h�E���g��
//#define USE_DX_DBG_WND;


#ifdef _MSC_VER
#else
#define OutputDebugString(str) std::cout << str << std::endl
#define _CrtSetDbgFlag(str)
#endif