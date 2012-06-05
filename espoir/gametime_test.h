#pragma once
#include"gametime.h"

namespace gametime_test{

TEST(gametime_test, singleton_policy){
	using namespace espoir;
	typedef Singleton<GameTime<DWORD> > a;
}

}