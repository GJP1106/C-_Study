// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*
������
**/


#include "stdafx.h"
#include "Time.h"
#include <iostream>
using namespace std;


//for ��(3)
class student {
public:
	int number;
	char name[100];
};


//for ������Ա����
#if 0 //�Ƶ�Time.h
class Time //����һ��ʱ����
{
public:
	int Hour;  //Сʱ
	int Minute;  //����
	int Second; //����

	//��Ա����
#if 1
	void initTime(int tmphour, int tmpmin, int tmpsec)
	{
		Hour = tmphour;
		Minute = tmpmin;
		Second = tmpsec;
	}
#endif
};
#endif
#if 0 
void initTime(Time &stmptime, int tmphour, int tmpmin, int tmpsec)
{
	stmptime.Hour = tmphour;
	stmptime.Minute = tmpmin;
	stmptime.Second = tmpsec;
}
#endif



int main()
{

	//һ:���������������Լ��������������(������)
	//�����ʱҪ���ǵĽǶ�:
	//(1)վ����ƺ�ʵ���ߵĽǶ������ǣ�
	//(2)վ��ʹ���ߵĽǶ������ǣ�
	//(3)���ࡢ���ࣻ


	//������Ļ���
	//(1)һ�������һ���û��Լ�������������ͣ����ǿ��԰��������һ�������ռ䣬����һ�Ѷ���(��Ա��������Ա����)��
	//(2)һ����Ĺ���:��Ա��������Ա��������Ա����(����������Ա������������������)��
	//(3)���Ƿ������Աʱ���������Ķ������Ǿ�ʹ�� ������.��Ա��  �����ʳ�Ա��
	     //�����ָ����������ָ�룬���Ǿ��� ָ����->��Ա��  �����ʳ�Ա��
#if 0
	student someone; //������Ķ���
	someone.number = 1000;
	student *psomeone = &someone;
	psomeone->number = 1005;

	cout << someone.number << endl;
#endif

	//(4)public��Ա�ṩ��Ľӿڣ���©����磬�������á�private��Ա�ṩ����ʵ���๦�ܵ�ϸ�ڷ�����������©��ʹ��
	//   ��Щprivate��Ա��
	//(5)struct �ǳ�ԱĬ��Ϊpublic��class; struct A{....}
	//(6)class��ԱĬ����private(˽��);  class A{....}
	//struct A{....}  �ȼ���  class A {public: ...}


	//������Ա����
#if 0
	Time myTime;
#if 0  //�Ϳ�ͷinitTime�ǳ�Ա�������Ӧ
	initTime(myTime, 11, 14, 5);

	cout << myTime.Hour << endl;
	cout << myTime.Minute << endl;
	cout << myTime.Second << endl;
#endif
#if 0
	myTime.initTime(11, 14, 15);
	cout << myTime.Hour << endl;
	cout << myTime.Minute << endl;
	cout << myTime.Second << endl;
#endif
#endif

	//�ġ����󿽱�
#if 0
	//�������ǿ��Կ�����
	//Ĭ������£����������Ŀ�������ÿ����Ա�������������
	//�������Time������Ҫ�����ʵ��� ��ֵ����� ���ܹ����ƶ�������ֿ�����Ϊ
	Time myTime; //
	myTime.Hour = 12;
	myTime.Minute = 15;
	myTime.Second = 40;

	Time myTime2 = myTime;
	Time myTime3(myTime);   //int a = 4; int b(a);
#if 0
	Time myTime4{ myTime };  //C++11֧��
	Time myTime5 = { myTime }; //C++11֧��
	myTime5.Hour = 8;
#endif
#endif

	//�塢˽�г�Ա
	Time myTime; //�����
	myTime.Hour = 5;
	//myTime.Millisecond = 1000;    //˽�еĲ���ֱ�ӣ���Ա����������
	//myTime.initMillTime();  //���ܷ���˽�г�Ա����
	myTime.initTime(11,11,11);

	return 0;
}

