// 3-13.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "Human.h"
#include "Men.h"
#include "Women.h"
using namespace std;

class CTempValue {
public:
	int val1;
	int val2;
public:
	CTempValue(int v1 = 0, int v2 = 0);
	CTempValue(const CTempValue& t) :val1(t.val1), val2(t.val2) { //�������캯��
		cout << "�����˿������캯��" << endl;
	}

	//������ֵ�����
	CTempValue & operator=(const CTempValue &tmpv) {
		val1 = tmpv.val1;
		val2 = tmpv.val2;
		cout << "�����˿�����ֵ�����" << endl;
		return *this;
	}
	virtual ~CTempValue() //��������
	{
		cout << "��������������" << endl;
	}
public:
	int Add(CTempValue &tobj); //��ͨ����
	CTempValue Double(CTempValue &ts) {
		CTempValue tmp; //�������������һ�����캯����һ�����������ĵ���
		tmp.val1 = ts.val1 * 2;
		tmp.val2 = ts.val2 * 2;
		return tmp;
	}
};
CTempValue::CTempValue(int v1, int v2) :val1(v1), val2(v2) {
	cout << "�����˹��캯��" << endl;
	cout << "val1 = " << val1 << endl;
	cout << "val2 = " << val2 << endl;
}
int CTempValue::Add(CTempValue &tobj) {
	int tmp = tobj.val1 + tobj.val2;
	tobj.val1 = 1000;  //�����޸�ֵ�����û��Ӱ��
	return tmp;
}

//ͳ���ַ�ch���ַ���strsource����ֵĴ������Ѵ�������ȥ
int calc(const string &strsource, char ch) {  //strsource ����βξͰ󶨵���string��ʱ������
	const char *p = strsource.c_str();
	int icount = 0;
	//...�����ͳ�ƴ���

	return icount;
}
//��ͨ����
CTempValue Double(CTempValue &ts) {
	CTempValue tmp; //�������������һ�����캯����һ�����������ĵ���
	tmp.val1 = ts.val1 * 2;
	tmp.val2 = ts.val2 * 2;
	return tmp;
}

class mynum {
public:
	mynum(int x = 0, int y = 0) :num1(x), num2(y){}
public:
	int num1;
	int num2;
};
mynum operator+(mynum &tmpnum1, mynum &tmpnum2) {
	/*mynum result;
	result.num1 = tmpnum1.num1 + tmpnum2.num1;
	result.num2 = tmpnum1.num2 + tmpnum2.num2;
	return result;*/
	//�Ż�Ϊ
	return mynum(tmpnum1.num1 + tmpnum2.num1, tmpnum1.num2 + tmpnum2.num2);
}
int main()
{
	//һ����ʱ����ĸ���
	//i++,++i
#if 0
	int i = 1;
	int &&r1 = i++; // r1��i֮��û��ʲô��ϵ��
	r1 = 19;
	i = 80;
#endif

	//����һЩ��ʱ��������Ϊ���Ǵ�����д����������ġ�ͳһ����ʱ����Ϊ��ʱ����
	//new delete ջ

	//����������ʱ���������ͽ������������ͽ��������
	//��2.1���Դ�ֵ(�����飬������)�ķ�ʽ���������ݲ���CTempValue;
#if 0
	CTempValue tm(10, 20); //���ù��캯��
	int Sum = tm.Add(tm); //����ᵼ�¿���������ִ��
	cout << "Sum = " << Sum << endl;
	cout << "tm.val1 = " << tm.val1 << endl;
#endif
	//(2.2)����ת��������ʱ����/��ʽ����ת���Ա�֤�������óɹ�
#if 0
	CTempValue sum;
	sum = 1000; //���������һ����������ʱ����
	//(1)��1000������ִ�����һ������ΪCTempValue����ʱ����
	//(2)���ÿ�����ֵ������������ʱ������ߵĸ�����Աֵ������sum����
	//(3)���������ʱ������CTempValue����
#endif
	//�Ż�
	//CTempValue sum = 1000; //�Ѷ������͸����󸳳�ֵ����һ�С��Ͳ������ɶ������ʱ����
	                       //Ϊsum����Ԥ���˿ռ䡣��1000����sum���󣬶�����ֱ�ӹ�����sum����Ԥ���ռ���

	//��ʽ����ת���Ա�֤�������óɹ�
#if 0
	char mystr[100] = "I love china, oh, yeah!";
	int result = calc(mystr, 'o');  //char[] ,string
#endif 
	//c++����ֻ��Ϊconst����(const string &strsource) ������ʱ������������Ϊ��const����(string &strsource)���ֲ���������ʱ����
#if 0
	string mystr = "I love china, oh, yeah!";
	int result = calc(mystr, 'o');
#endif

	//2.3)�������ض����ʱ��
	CTempValue ts1(10, 20);
	//Double(ts1); //��Ϊ������ʱ������ռ����һ���������캯����һ����������
	CTempValue ts2 = Double(ts1);
	CTempValue &&ts3 = Double(ts1); //��ʱ������һ����ֵ

	//Double() �������������
	//CTempValue tmp;������һ�����캯����һ����������
	//return tmp; ������ʱ����ռ��һ���������캯������������

	//�پ�һ�����ӣ�����֪ʶ�㣺�������������
	mynum tm1;
	tm1.num1 = 10;
	tm1.num2 = 100;

	mynum tm2;
	tm2.num1 = 20;
	tm2.num2 = 200;
	mynum tmp = tm1 + tm2;

	//(1)�����Ż�
	//(2)��������;���



	return 0;
}

