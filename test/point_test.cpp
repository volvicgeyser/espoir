#include<iostream>
#include<boost/operators.hpp>
#include"../espoir/point.h"

int main(){
	using namespace std;
	Point p1 = { 10, 10};
	Point p2 = { 20, 20};
	Point p3 = { 0, 0};
	p3 = p1 + p2;

	cout << p3.x << " "<< p3.y << endl;
}
