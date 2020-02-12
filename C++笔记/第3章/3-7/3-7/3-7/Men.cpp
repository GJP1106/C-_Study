#include "stdafx.h"
#include "Men.h"
#include <iostream>
using namespace std;
//实现
Men::Men() {
	cout << "执行了Men::Men()" << endl;
}

void Men::samenamefunc(int a) {
	Human::samenamefunc(12); //调用的时父类的带参的samenamefunc函数
	Human::samenamefunc(); //调用的时父类的不带参的samenamefunc函数
	cout << "执行了Men::samenamefunc(int a)" << endl;
}