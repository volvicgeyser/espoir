#include"stdafx.h"
#include"Console.h"


namespace espoir{
	Console::Console(){
		AllocConsole();
	}
	Console::~Console(){
		FreeConsole();
	}
}
