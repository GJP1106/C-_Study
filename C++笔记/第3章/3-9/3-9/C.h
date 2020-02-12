#ifndef __C__
#define __C__
#include <iostream>
#include "A.h"
#include "C.h"
using namespace std;

class A;

class C {
public:
	void callCAF(int x, A &a); //只有public的函数才能成为其他类的友元成员函数
};


#endif