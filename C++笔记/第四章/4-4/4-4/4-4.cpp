// 4-4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "myarray.h"
#include "myvector.h"
#include "ca.h"
using namespace std;

//"��ʾʵ����" �ֶ��е�"ʵ��������"
extern template A<float>;  //��������.cpp�ļ�����ôд
                           //extern����:�����ڱ��ļ�������һ��extern�������ʾ��ģ���ʵ�����汾����
                           //externĿ��:���߱���������������Դ�ļ�(.cpp�ļ�)���Ѿ�����һ����ģ���ʵ�����汾�ˡ�
extern template void myfunc123(int v1, int v2);


#if 0   //һ����ͨ��ĳ�Ա����ģ��
class A {  //��ͨ��
public:
	template <typename T>
	void myft(T tmpt) {   //��Ա����ģ��
		cout << tmpt << endl;
	}
};
#endif
#if 0  //��ֲ��ca.h
template <typename C>
class A {  //��ͨ��
public:
	template <typename T2>
	A(T2 v1, T2 v2);
	//A(T2 v1, T2 v2) {  //���캯������Ҳ�����Լ���ģ�壬���������ģ��Cû�й�ϵ

	//}
	 
	template <typename T>
	void myft(T tmpt) {   //��Ա����ģ��
		cout << tmpt << endl;
	}
	void myftpt() {}
	C m_ic;
};

template <typename C>  //�ȸ����ģ������б�
template <typename T2> //�ٸ����캯���Լ���ģ������б�
A<C>::A(T2 v1, T2 v2) {
	cout << v1 << v2 << endl;
}
#endif


int main()
{
	//һ����ͨ��ĳ�Ա����ģ��
	//��������ͨ�࣬������ģ�壬���ĳ�Ա����������һ������ģ�壬��Ϊ"��Ա����ģ��"�����������麯��������������ᱨ��
#if 0
	A a;
	a.myft(3);  //�������������������ʱ���������ͻ�ʵ�����������ģ��
#endif

	//������ģ��ĳ�Ա����ģ��
	//��ģ���ģ�����������<>ָ������Ա����ģ��(����ģ��)�Ĳ����������ƶ�
#if 0
	A<float> a(1, 2);
	A<float> a2(1.1, 2.2);
#endif
	//��ģ��ĳ�Ա����(������ͨ��Ա����/��Ա����ģ��)ֻ��Ϊ��������(�����г����˶Ըú������߸ú���ģ��ĵ���ʱ)�Ž���ʵ����
	  //���ĳ������δʹ�ã��򲻻�ʵ�����ó�Ա������


	//����ģ����ʾʵ������ģ������
	//Ϊ�˷�ֹ�ڶ��.cpp�ļ��ж�ʵ������ͬ�� ��ģ�壬����C++11�����һ��������������ǳ�Ϊ"��ʾʵ����"
	  //ͨ��"��ʾʵ����"�������������ɶ����ͬ��ģ��ʵ���Ŀ���
	A<int> tmpobj(6, 7);
	//ģ���ʵ��������ֻ��һ����ʵ�������������ж��

	//�ܽ᣺
	//(1)vs2017��̫�Ƽ������ɫ
	//(2) template A<float>
	    //extern template A<float>






	return 0;
}

