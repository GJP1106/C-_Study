#include "stdafx.h"
#include "Women.h"
#include <iostream>
using namespace std;
//实现
Women::Women() {
	cout << "执行了Women::Women()" << endl;
}
Women::~Women() {
	cout << "执行了Women::~Women() " << endl;
}

void Women::samenamefunc(int a) {
	Human::samenamefunc(12); //调用的时父类的带参的samenamefunc函数
	Human::samenamefunc(); //调用的时父类的不带参的samenamefunc函数
	cout << "执行了Women::samenamefunc(int a)" << endl;
}

void Women::eat() {
	std::cout << "女人喜欢吃面食" << std::endl;
};