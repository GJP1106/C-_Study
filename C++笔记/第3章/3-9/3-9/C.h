#ifndef __C__
#define __C__
#include <iostream>
#include "A.h"
#include "C.h"
using namespace std;

class A;

class C {
public:
	void callCAF(int x, A &a); //ֻ��public�ĺ������ܳ�Ϊ���������Ԫ��Ա����
};


#endif