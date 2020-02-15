#include "stdafx.h"
#include <iostream>
#include <vector>
#include "ca.h"

using namespace std;

//显示实例化 手段中的“实例化定义”，这种实例化定义只需要在一个.cpp文件写就可以
template A<float>;  //编译器遇到这段代码就直接 实例化出来一个 A<float>
template void myfunc123(int v1, int v2);


void mfunc() {
	A<float> a(1, 2);
}