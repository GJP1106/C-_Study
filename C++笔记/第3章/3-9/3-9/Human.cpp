#include "stdafx.h"
#include "Human.h"
#include <iostream>
using namespace std;

//实现
Human::Human() {
	cout << "执行了Human::Human()" << endl;
}

Human::Human(int abc) {
	cout << "执行了Human::Human(int abc)" << endl;
}

Human::~Human() {
	cout << "执行了Human::~Human()" << endl;
}

void Human::samenamefunc() {
	cout << "执行了Human::samenamefunc()" << endl;
}
void Human::samenamefunc(int a) {
	cout << "执行了Human::samenamefunc(int a)" << endl;
}

void Human::eat() {
	std::cout << "人类吃各种粮食" << std::endl;
};
