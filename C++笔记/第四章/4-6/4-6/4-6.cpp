// 4-6.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

template<typename T,typename U>
struct TC  //������TC��ģ��
{
	TC() {
		cout << "�����汾���캯��" << endl;
	}
	void functest()
	{
		cout << "�����汾" << endl;
	}
};

//��T��U����������ģ�������Ϊint����ʱ������ϣ����һ���ػ��汾
//ȫ�ػ���������������ģ�����(����T��U)�������þ�������ʹ���
template<> //ȫ�ػ�����������ģ��������þ������ʹ������������template��ߵ�<>���Ϊ��
struct TC<int, int>  //�ϱߵ�T�󶨵�����ĵ�һ��int���ϱߵ�U�󶨵�����ĵڶ���int
{
	TC() {
		cout << "int int�汾���캯��" << endl;
	}
	//��������ԶԸ��ػ��汾����������
	void functest() {
		cout << "int int���ػ��汾" << endl;
	}
};
template<>
struct TC<double, int>  //�ϱߵ�T�󶨵�����ĵ�һ��double���ϱߵ�U�󶨵�����ĵڶ���int
{
	TC() {
		cout << "double int�汾���캯��" << endl;
	}
	//��������ԶԸ��ػ��汾����������
	void functest() {
		cout << "double int���ػ��汾" << endl;
	}
};
template<>  //ȫ�ػ�
void TC<double, double>::functest()
{
	cout << "double double��functest()�ػ��汾" << endl;
}

//ƫ�ػ��ķ����汾
template <typename T, typename U, typename W>  //����������ģ�����
struct TD {
	void functest()
	{
		cout << "���������ķ����汾" << endl;
	}
};
//�Ӳ��������Ͻ���ƫ�ػ����������ڰ�2������ģ���������һ������ģ�������
template<typename U> //��Ϊ�������������Ұ󶨵��������ͣ���������ֻʣ��һ��U����ģ������ˡ�
struct TD<int, U, double>   //���ע�⣬�������������
{
	void functest()
	{
		cout << "ƫ�ػ�int,U,double�汾" << endl;
	}
};

//��ģ�������Χ�Ϸ����汾
template <typename T>
struct TE
{
	void functest() {
		cout << "ģ�������Χ�Ϸ����汾" << endl;
	}
};
//ģ�������Χ���ػ��汾
template <typename T>
struct TE<const T>   //const���ػ��汾
{
	void functest() {
		cout << "const���ػ��汾" << endl;
	}
};
template <typename T>
struct TE<T *>   //T*���ػ��汾
{
	void functest() {
		cout << "T*���ػ��汾" << endl;
	}
};

template <typename T>
struct TE<T &>   //T&��ֵ���õ��ػ��汾
{
	void functest() {
		cout << "T&��ֵ���õ��ػ��汾" << endl;
	}
};

template <typename T>
struct TE<T &&>   //T&&��ֵ���õ��ػ��汾
{
	void functest() {
		cout << "T&&��ֵ���õ��ػ��汾" << endl;
	}
};

//����ģ�巺��
template <typename T,typename U>
void tfunc(T &tmp1, U &tmp2) {
	cout << "tfunc�����汾" << endl;
	cout << tmp1 << endl;
	cout << tmp2 << endl;
}

//����ģ��ȫ�ػ��汾
template <>
void tfunc(int &tmp1, double &tmp2) {
	cout << "tfuncȫ�ػ��汾" << endl;
	cout << tmp1 << endl;
	cout << tmp2 << endl;
}



int main()
{
	//�ػ��� �෴ ������ģ�壬�������ָ�����͡�
	//�ػ��������������(����ģ�����)��������ĶԴ������������ţ�����д�ʺ�����ר�ô���
	//һ����ģ���ػ�
	//(1.1)��ģ��ȫ�ػ�
	 //a)����ȫ�ػ�
	     //����Ҫ�з����汾���ܴ����ػ��汾��ֻҪ�漰�ػ���һ���ȴ��ڷ���
	//�ػ��汾���������������ѡ��
#if 0
	TC<char, int> tchar;
	tchar.functest();

	TC<int, int> tint;
	tint.functest();

	TC<double, int> tdouble;
	tdouble.functest();
	//�����ػ��汾���������
#endif


	//b)�ػ���Ա����������ģ��
#if 0
	TC<double, double> tdb;  //�����汾���󣬵��õ��Ƿ����汾�Ĺ��캯��
	tdb.functest();  //��Ϊ�����ػ���double��double���͵�functest����������������õ����ػ���functest()������
#endif

	//(1.2)��ģ��ƫ�ػ�(�ֲ��ػ�)
	//ƫ�ػ���������˵��:һ���Ǵ�ģ����������� һ���Ǵ�ģ�������Χ��
	//a)��ģ�����������
#if 0
	TD<double, int, double> td;
	td.functest();
	TD<int, int, double> td1;
	td1.functest();
#endif
	//b)��ģ�������Χ��:int  ->  const int(��intС)
	                     //ԭ��T������T*(����������T��СΪָ������T*)
	                     //ԭ��T������T&��ֵ���ã�����������T&&(��ֵ����)�����з�Χ��С��
#if 0
	TE<double> te;
	te.functest();   //�����汾

	TE<double *> te1;
	te1.functest();  //T*���ػ��汾

	TE<const double *> te2;
	te2.functest();  //T*���ػ��汾

	TE<const double> te3;
	te3.functest();   //const���ػ��汾

	TE<int &> te4;
	te4.functest();  //T&��ֵ���õ��ػ��汾
#endif
	//�ֲ��ػ���ת������֮���������ϻ���ģ�塣ȫ�ػ���ת�����˵���һ�����������

	//��������ģ��ȫ�ػ�
	//(2.1)����ģ��ȫ�ػ�
#if 0
	const char *p = "I Lova China";
	int i = 12;
	tfunc(p, i);   //T = const char *, tmp1 = const char * &
	int a = 1;
	double b = 3.5;
	tfunc(a, b);
#endif
	//ȫ�ػ�����ģ��ʵ���ϵȼ���ʵ����һ������ģ�壬�����ǵȼ���һ���������ء�
	//void tfunc<int,double>(int &,double &)  //ȫ�ػ����ȼ���ʵ����һ������ģ��
	//void tfunc(int &tmp1,double &tmp2)  //���غ���Ӧ�ó�����

	//������ѡ���������:��ͨ���ȣ��ػ��汾�������汾
	//����㴫�ݸ��ַ���������ģ��
	//����ģ����ػ��汾�У������ ��������ģ�������ָ������ģ�������
	//����������Ϊ ��������ģ����� ��ָ������ģ����������ʡ����Ա�������Ϊ��ѡ���������͵�ģ��������ػ��汾

	//(2.2)����ģ��ƫ�ػ�
	 //����ģ�岻��ƫ�ػ�


	//����ģ���ػ��汾 ����λ�ý���
	//ģ�嶨�塢ʵ�ֶ�����һ��.h��
	//ģ����ػ��汾��ģ��ķ����汾��Ӧ�÷���ͬһ��.h�ļ��С�
	//.h�ļ���ǰ�߷ŷ����汾����߷��ػ��汾




	return 0;
}

