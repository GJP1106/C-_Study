#include "stdafx.h"
#include "Women.h"
#include <iostream>
using namespace std;
//ʵ��
Women::Women() {
	cout << "ִ����Women::Women()" << endl;
}
Women::~Women() {
	cout << "ִ����Women::~Women() " << endl;
}

void Women::samenamefunc(int a) {
	Human::samenamefunc(12); //���õ�ʱ����Ĵ��ε�samenamefunc����
	Human::samenamefunc(); //���õ�ʱ����Ĳ����ε�samenamefunc����
	cout << "ִ����Women::samenamefunc(int a)" << endl;
}

void Women::eat() {
	std::cout << "Ů��ϲ������ʳ" << std::endl;
};