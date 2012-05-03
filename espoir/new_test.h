#pragma once

namespace new_test{

class TestClass{int a;};
TEST(new_test, new_test){

	using namespace espoir;
	//int* i = new_(int);
	TestClass* i = new_<TestClass>();
	delete_<TestClass>(i);

	DOut dout;
	dout << _T("GetAllocCount() = ") << GetAllocCount() << std::endl;
	dout << _T("GetDeallocCount() = ") << GetDeallocCount() << std::endl;
}

}