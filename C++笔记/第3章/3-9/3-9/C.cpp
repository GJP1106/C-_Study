#include "stdafx.h"
#include "A.h"
#include "C.h"


using namespace std;

void C::callCAF(int x, A &a) {
	//cout << x << endl;
	a.data = x;
	cout << a.data << endl;
}