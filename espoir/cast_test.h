#pragma once

namespace cast_test{

class TestClass{
public:
	int a;
};

TEST(cast, cast_test){
	using namespace espoir;
	//const int a = Cast<int>::Convert(10);
	TestClass* t;
	TestClass t2;
	t = cast<TestClass*>(&t2);
	type_check<int>(10);
}

}