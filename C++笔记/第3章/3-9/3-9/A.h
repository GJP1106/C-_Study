#ifndef __A__
#define __A__
#include <iostream>
#include "C.h"

using namespace std;

class A {
	friend void C::callCAF(int x, A &a);
private:
	int data;
};

#endif