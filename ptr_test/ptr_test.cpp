#include<iostream>
#include<algorithm>
#include<cstdlib>
#define SIZE 256

template <typename T>
void print_array_addr(T* t, size_t size){
	for(size_t i = 0; i < size; i++){
		std::cout << i << ": "<< (t+i) << std::endl;
	}
}
int main(){
	char test[SIZE][SIZE];
	char test2[SIZE];
	char test3[SIZE][SIZE] = { {1, 2, 3, 4, 5,}, {6,7,8,9,10}};
	//std::cout << test3 << std::endl;
	print_array_addr(test3, SIZE);
	std::system("pause");
	//std::copy(test, test+SIZE, std::ostream_iterator<int>(std::cout, " "));
	//std::copy(test, test+256, std::ostream_iterator<int>(std::cout,  " "));
}
