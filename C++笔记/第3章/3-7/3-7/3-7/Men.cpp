#include "stdafx.h"
#include "Men.h"
#include <iostream>
using namespace std;
//ʵ��
Men::Men() {
	cout << "ִ����Men::Men()" << endl;
}

void Men::samenamefunc(int a) {
	Human::samenamefunc(12); //���õ�ʱ����Ĵ��ε�samenamefunc����
	Human::samenamefunc(); //���õ�ʱ����Ĳ����ε�samenamefunc����
	cout << "ִ����Men::samenamefunc(int a)" << endl;
}