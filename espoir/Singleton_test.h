#pragma once

namespace Singleton_test{

//�V���O���g��������e�X�g�N���X
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
//�V���O���g���̃e�X�g
TEST(singleton_test, operator_test){
	using namespace espoir;

	EXPECT_EQ(SPSingleton<TestClass>::GetInst()->x_, 0);
	EXPECT_EQ(SPSingleton<TestClass>::GetInst()->y_, 1);
}


//typedef���Ă݂�
TEST(singleton_test, Disable_constructor_test1){
	using namespace espoir;
	typedef SPSingleton<TestClass> TestHolder;
	
	TestHolder::GetInst();
	TestHolder::GetInst();

//    �P�x�����Ăяo����Ă��Ȃ��͂�
	EXPECT_EQ(TestHolder::GetInst()->getCount(), 1);


}

//�X�R�[�v�̃e�X�g
TEST(singleton_test, Disable_scope_test1){
	using namespace espoir;
	typedef SPSingleton<TestClass> TestHolder;
	for(int i = 0; i < 10; i++)
	{
		TestHolder::GetInst();
	}
	TestHolder::GetInst();

	//�P�x�����Ăяo����Ă��Ȃ��͂�
	EXPECT_EQ(TestHolder::GetInst()->getCount(), 1);
}

}
