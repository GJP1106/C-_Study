#include "stdafx.h"
#include <iostream>
#include <vector>
#include "ca.h"

using namespace std;

//��ʾʵ���� �ֶ��еġ�ʵ�������塱������ʵ��������ֻ��Ҫ��һ��.cpp�ļ�д�Ϳ���
template A<float>;  //������������δ����ֱ�� ʵ��������һ�� A<float>
template void myfunc123(int v1, int v2);


void mfunc() {
	A<float> a(1, 2);
}