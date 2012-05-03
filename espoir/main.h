#pragma once

#include "resource.h"

namespace espoir{

inline void ShowStart(){
	OutputDebugString(_T("\n\n\n"));
	OutputDebugString(_T("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n"));
	OutputDebugString(_T("☆☆☆☆☆☆☆☆☆☆　　S T A R T！　！　　　　　☆☆☆☆☆☆☆☆☆☆☆\n"));
	OutputDebugString(_T("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n"));
	OutputDebugString(_T("\n\n\n"));
}

inline void CheckMemoryLeaks(){
	OutputDebugString(_T("終了間際にメモリリークのチェックが行われます\n"));
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
}

}
