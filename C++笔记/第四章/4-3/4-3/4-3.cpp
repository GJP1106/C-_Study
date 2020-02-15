// 4-3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "myarray.h"
#include "myvector.h"
#include <string>
using namespace std;


template<typename T>
typename T::size_type getlength(const T&c) {
	if (c.empty()) {
		return 0;
	}
	return c.size();
}

//����Ҫ�Ѻ���ָ����Ϊ ĳ�������Ĳ������д��ݣ���ô������?
//����ָ��Ҫ�뵱�� �����Ĳ�������Ҫ:
typedef int(*FunType)(int, int);   //����һ������ָ������

int mf(int tmp1, int tmp2) {
	//....
	return 1;
}
/*
void testfunc(int i, int j, FunType funcpoint) //funcpoint���Ǻ���ָ��
{
	//���ǾͿ���ͨ������ָ����ú���:
	int result = funcpoint(i, j);   //�൱�ڵ��ú��� mf
	cout << result << endl;
}
*/

//�ɵ��ö������������
class tc {
public:
	tc() { cout << "���캯��ִ��" << endl; }
	tc(const tc& t) { cout << "�������캯��ִ��" << endl; }

	//����Բ����
	int operator()(int v1, int v2) const {
		return v1 + v2;
	}
};
//��testfunc��Ϊģ�庯��
//testfunc(3, 4, mf);
//testfunc(3,4);
template <typename T, typename F=tc>
void testfunc(const T &i, const T &j, F funcpoint = F()) {
	cout << funcpoint(i,j) << endl;
}



int main()
{
	//һ��typename��ʹ�ó���
	//(1)��ģ�嶨�����������ģ����������Ͳ�����
	//typename
	//template<typename T,int a,int b>  //typename��߸�����һ������
	//int funcaddv2(T c) {...}
	//��ģ��
	//template<class T>  //����ΪT��ģ�������������Ȼ������class�����������class�����ඨ�����˼�����ܺ��ඨ���Ϊһ̸
	//class myvector {...}
	//typename ����д�� class

	//(2)ʹ��������ͳ�Ա����typename����ʶ����һ�����ͣ�
	//::�����������  �������еľ�̬��Ա��ʱ�� ����::��̬��Ա��
	//int Time::mystatic = 5;
	//::�����������������ͳ�Ա
	//typename�ĵڶ����÷���֪ͨ��������һ�����ִ������һ�����͡������typename���ܻ���class
#if 0
	string mytest = "I love china!";

	//string::size_type ������ unsigned int
	string::size_type size = getlength(mytest);
#endif

	//��������ָ�������������Ĳ���
	//testfunc(3, 4, mf);

	//��������ģ��Ȥζ�÷�����
#if 0
	testfunc(3, 4, mf);

	//��ʦ����һ������:�ɵ��ö���  ��δ����֪ʶ�㡱��һ�� ��һ�� ���ɵ��ö��󡱣�
	tc tcobj;
	testfunc(3, 4, tcobj);
	//testfunc(3, 4, tc());  //����
#endif

	//�ġ�Ĭ��ģ�����
	//a)��ģ�壬��ģ������߱�����<>���ṩ�������Ϣ�� <>��ʾ����һ��ģ�壻

	myarray<> abc;  //��ȫ��ģ�������ȱʡֵ
	myarray<int> def;  //�ṩһ����ȱʡֵ��ֻ�ṩһ��������һ���õ���ȱʡֵ

	//b)����ģ�壺�ϱ�׼ֻ��Ϊ��ģ���ṩĬ��ģ�������c++11�±�׼����Ϊ����ģ���ṩĬ�ϲ�����
	//(1)ͬʱ��ģ������ͺ��������ṩȱʡֵ
	//(2)ע��д�� F funcpoint = F()
	//(3)tc���أ�
	testfunc(3, 4);

	return 0;
}

