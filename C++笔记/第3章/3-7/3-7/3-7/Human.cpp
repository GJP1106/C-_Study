#include "stdafx.h"
#include "Human.h"
#include <iostream>
using namespace std;

//ʵ��
Human::Human() {
	cout << "ִ����Human::Human()" << endl;
}

Human::Human(int abc) {
	cout << "ִ����Human::Human(int abc)" << endl;
}

void Human::samenamefunc() {
	cout << "ִ����Human::samenamefunc()" << endl;
}
void Human::samenamefunc(int a) {
	cout << "ִ����Human::samenamefunc(int a)" << endl;
}
