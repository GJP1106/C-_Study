// 5-1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

void myfunc() {
	int i;
	i = 5;
	static int j; //�ֲ���̬����
}

class A {
public:
	A() {
		cout << "A" << endl;
	}
};

int main()
{
	//һ��ֱ���ڴ����(new/delete)
	myfunc();
	//A a; //�������������Ǵ���a����
	//�����Ľ� ���� ջ �Ѹ���
	//�������� new delete����
	//new���䷽ʽ���ǳ�Ϊ ��̬����(���䵽����)��ֱ���ڴ����(new/delete)
	//��γ�ʼ��:
#if 0
	//int i;
	//int *point = new int;  //��ֵδ����
	int *point = new int(100);
	string *mystr = new string;  //���ַ�����˵��������string��Ĭ�Ϲ��캯��
	string *mystr2 = new string(5, 'a');   //����һ���ַ������ַ���������5��'a'
	vector<int> *pointv = new vector<int>{ 1, 2, 3, 4, 5 }; //һ���������������5������

	//���ֵ��ʼ����:��()����ʼ��
	string *mystr3 = new string();  //Ҳ�ǿ��ַ�������mystrûɶ����
	int *point2 = new int();  //ֵ��ʼ���ķ�ʽ������point2��ֵ����ʼ����0

	A *pa = new A;
	A *pa2 = new A();   //�Ƿ��ǡ�ֵ��ʼ����Ч��һ�������ǵ���A�Ĺ��캯����
	//new�����ʱ���ܹ����С�ֵ��ʼ�����ͽ���һ��Ϊ�ã���ֹ����ֵû�б���ʼ����
#endif
#if 0
	//c++11�У�auto���Ժ�new���ʹ��
	string *mystr4 = new string(5, 'a');
	auto mystr5 = new auto(mystr4);   //mystr5 = string **
	delete mystr4;

	//const����Ҳ���Զ�̬����
	const int *pointci = new const int(200);
#endif
	//new �� delete˵��:
	//a)�ɶ�ʹ�ã�delete�������ǻ�����new������ڴ�(�ͷ��ڴ�)������new�������ڴ棬�ǲ�����delete���ͷ�
	//b)deleteһ���ڴ棬ֻ��deleteһ�Σ�����delete��Ρ�delete������ڴ�Ͳ���ʹ����,��ָ�����ɾ����Σ���ɾ�����û��ʲô����
	/*int i = 12;
	int *p = &i;
	delete p; */  //����new�������ڴ棬����delete������ִ�� �ᱨ�쳣

	//int *p = new int();
	//int *p2 = p;
	//delete p2;           //û������
	//delete p;            //�쳣����Ϊp��p2��ָ��ͬһ���ڴ�

	//ע�������һ���ܽ�
	//(1)new ������ǧ��Ҫ����delete�������ڴ�й©��ʱ��һ�����ܵ���ϵͳ��Դ���ţ����б�����
	//(2)delete����ڴ治����ʹ�ã������쳣
	int *pci = new int(300);
	*pci = 500;
	delete pci;
	//*pci = 600;
	pci = nullptr;   //���Ǹ���ϰ�ߣ�������ָ�벻ָ���κζ����ˣ���ʦ�ᳫdeleteһ��ָ��󣬸���ָ��һ��nullptr

	//3)ͬһ���ڴ��ͷ����ε����⣻Ҳ�ᱨ�쳣
	//��new/deleteֱ�ӽ����ڴ����Ҫ��С��
	//c++11��ʼ�����ˡ�����ָ�롱��new��������delete������ָ���ܹ�������delete

	//���������¹��̣��۲��ڴ�й©
	//MFCӦ�ó����ܹ���һ���̶���(�����˳���ʱ��),�ܹ��������Ƿ����ڴ�й©��



	return 0;
}

