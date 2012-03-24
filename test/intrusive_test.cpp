#include<boost/intrusive_ptr.hpp>
#include<iostream>

class Test{
};


void intrusive_ptr_release(Test* a){
	static int i = 0;
	std::cout << "release" << i << std::endl;
	i++;
}

void intrusive_ptr_add_ref(Test* a){
	static int i = 0;
	std::cout << "add " << i << std::endl;
	i++;
}


int main(){
	using namespace std;
    boost::intrusive_ptr<Test> a;
	a = boost::intrusive_ptr<Test>(new Test());
	cout << "test" << endl;
	
	//ƒRƒs[
	boost::intrusive_ptr<Test> b = a;
}
