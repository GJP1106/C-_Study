#include "stdafx.h"
#include "Time.h"
#include <iostream>
using namespace std;

//��ͨ���������ǳ�Ա����
void WriteTime(Time &mytime)
{
	cout << mytime.Hour << endl;
}

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
Time::Time(int tmphour, int tmpmin, int tmpsec) :Hour(tmphour), Minute(tmpmin), Second(tmpsec), Millisecond(0), ctestvalue(10)
{
	/*Hour = tmphour;
	Minute = tmpmin;
	Second = tmpsec;
	initMillTime(0);*/
	cout << "������Time::Time(int tmphour, int tmpmin, int tmpsec)���캯��" << endl;
}

//���캯��
Time::Time() : Hour(12), Minute(59), Second(50), ctestvalue(10)
{
	//Hour = 12;
	//Minute = 59;
	//Second = 59;
	initMillTime(50);

	cout << "������Time::Time()���캯��" << endl;
}

//�����������Ĺ��캯��
Time::Time(int tmphour, int tmpmin) :ctestvalue(10)
{
	Hour = tmphour;
	Minute = tmpmin;
	Second = 59;
	initMillTime(0);
	cout << "������Time::Time(int tmphour, int tmpmin)���캯��" << endl;
}

//��һ�������Ĺ��캯��
Time::Time(int tmphour) :ctestvalue(10)
{
	Hour = tmphour;
	Minute = 59;
	Second = 59;
	initMillTime(0);
	cout << "������Time::Time(int tmphour)���캯��" << endl;
}

//�������캯��
Time::Time(const Time &tmptime, int a) {
	cout << "������Time::Time()�������캯��" << endl;
}

//void Time::addhour(int tmphour) const
//{
	//Minute = tmphour;    //����
//}

Time& Time::add_hour(int tmphour)
{
	Hour += tmphour;  //this->Hour += tmphour;
	return *this;   //�Ѷ����Լ�������ȥ��
}
//������ʵ�����������ε�
//const char *p, char const *p, char *const p;
//Time& Time::add_hour(Time *const this, int tmphour)

Time& Time::add_minute(int Minute)
{
	this->Minute += Minute;  //this->Minute += Minute;
	return *this;   //�Ѷ����Լ�������ȥ��
}
#if 0
void Time::mstafunc(int testvalue)
{
	//Minute = 12;    //������ΪMinute��Ա�����ǺͶ�����صĳ�Ա������
	mystatic = testvalue;    //���ԣ���Ϊmystatic������ص�
	cout << testvalue << endl;
}
#endif