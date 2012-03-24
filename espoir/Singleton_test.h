#pragma once

namespace Singleton_test{

//シングルトン化するテストクラス
class TestClass{
private:
	static int count;
public:
	TestClass(){
		this->count++;
		this->x_ = 0;
		this->y_ = 1;
	}
	int getCount(){return this->count;}
	int x_;
	int y_;
};
int TestClass::count = 0;

class TestClass2{};
//シングルトンのテスト
TEST(singleton_test, operator_test){
	using namespace espoir;

	EXPECT_EQ(Singleton<TestClass>::getInst()->x_, 0);
	EXPECT_EQ(Singleton<TestClass>::getInst()->y_, 1);
}


//typedefしてみる
TEST(singleton_test, Disable_constructor_test1){
	using namespace espoir;
	typedef Singleton<TestClass> TestHolder;
	
	TestHolder::getInst();
	TestHolder::getInst();

//    １度しか呼び出されていないはず
	EXPECT_EQ(TestHolder::getInst()->getCount(), 1);


}
}
