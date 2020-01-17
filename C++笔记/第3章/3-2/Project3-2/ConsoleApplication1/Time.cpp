#include "stdafx.h"
#include "Time.h"
#include <iostream>
using namespace std;

//��Ա����initTime()ʵ�� 
//����������ð�Ž� ����������� ����ʾinitTime��������Time�ࡣ
void Time::initTime(int tmphour, int tmpmin, int tmpsec)
{
	Hour = tmphour;   //����ע�⵽����Ա�����У����ǿ���ֱ��ʹ�ó�Ա������
	                  //�ĸ�������õĸó�Ա��������Щ��Ա�����������ĸ����󣬴�ҿ����������Ա����֪���ĸ���������Լ���
    Minute = tmpmin;  
	Second = tmpsec;
	initMillTime(0);
}

void Time::initMillTime(int mls)
{
	Millisecond = mls;   //��Ա�������Է��ʳ�Ա���������ܳ�Ա�Ƿ���˽��
}

//���캯����ʵ��
Time::Time(int tmphour, int tmpmin, int tmpsec) :Hour(tmphour), Minute(tmpmin), Second(tmpsec), Millisecond(0)
{
	/*Hour = tmphour;
	Minute = tmpmin;
	Second = tmpsec;
	initMillTime(0);*/
	cout << "������Time::Time(int tmphour, int tmpmin, int tmpsec)���캯��" << endl;
}

//���캯��
Time::Time()
{
	Hour = 12;
	Minute = 59;
	Second = 59;
	initMillTime(50);

	cout << "������Time::Time()���캯��" << endl;
}

//�����������Ĺ��캯��
Time::Time(int tmphour, int tmpmin)
{
	Hour = tmphour;
	Minute = tmpmin;
	Second = 59;
	initMillTime(0);
	cout << "������Time::Time(int tmphour, int tmpmin)���캯��" << endl;
}

//��һ�������Ĺ��캯��
Time::Time(int tmphour)
{
	Hour = tmphour;
	Minute = 59;
	Second = 59;
	initMillTime(0);
	cout << "������Time::Time(int tmphour)���캯��" << endl;
}