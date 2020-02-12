#include "stdafx.h"
#include "Time.h"
#include <iostream>
using namespace std;

//普通函数，不是成员函数
void WriteTime(Time &mytime)
{
	cout << mytime.Hour << endl;
}

//成员函数initTime()实现 
//其中这两个冒号叫 作用域运算符 ，表示initTime函数属于Time类。
void Time::initTime(int tmphour, int tmpmin, int tmpsec)
{
	Hour = tmphour;   //我们注意到，成员函数中，我们可以直接使用成员变量名
	                  //哪个对象调用的该成员函数，这些成员变量就属于哪个对象，大家可以理解成类成员函数知道哪个对象调用自己。
    Minute = tmpmin;  
	Second = tmpsec;
	initMillTime(0);
}

void Time::initMillTime(int mls)
{
	Millisecond = mls;   //成员函数可以访问成员变量，不管成员是否是私有
}

//构造函数的实现
Time::Time(int tmphour, int tmpmin, int tmpsec) :Hour(tmphour), Minute(tmpmin), Second(tmpsec), Millisecond(0), ctestvalue(10)
{
	/*Hour = tmphour;
	Minute = tmpmin;
	Second = tmpsec;
	initMillTime(0);*/
	cout << "调用了Time::Time(int tmphour, int tmpmin, int tmpsec)构造函数" << endl;
}

//构造函数
Time::Time() : Hour(12), Minute(59), Second(50), ctestvalue(10)
{
	//Hour = 12;
	//Minute = 59;
	//Second = 59;
	initMillTime(50);

	cout << "调用了Time::Time()构造函数" << endl;
}

//带两个参数的构造函数
Time::Time(int tmphour, int tmpmin) :ctestvalue(10)
{
	Hour = tmphour;
	Minute = tmpmin;
	Second = 59;
	initMillTime(0);
	cout << "调用了Time::Time(int tmphour, int tmpmin)构造函数" << endl;
}

//带一个参数的构造函数
Time::Time(int tmphour) :ctestvalue(10)
{
	Hour = tmphour;
	Minute = 59;
	Second = 59;
	initMillTime(0);
	cout << "调用了Time::Time(int tmphour)构造函数" << endl;
}

//拷贝构造函数
Time::Time(const Time &tmptime, int a) {
	cout << "调用了Time::Time()拷贝构造函数" << endl;
}

//void Time::addhour(int tmphour) const
//{
	//Minute = tmphour;    //错误
//}

Time& Time::add_hour(int tmphour)
{
	Hour += tmphour;  //this->Hour += tmphour;
	return *this;   //把对象自己给返回去了
}
//编译器实际是这样传参的
//const char *p, char const *p, char *const p;
//Time& Time::add_hour(Time *const this, int tmphour)

Time& Time::add_minute(int Minute)
{
	this->Minute += Minute;  //this->Minute += Minute;
	return *this;   //把对象自己给返回去了
}
#if 0
void Time::mstafunc(int testvalue)
{
	//Minute = 12;    //错误，因为Minute成员变量是和对象相关的成员变量。
	mystatic = testvalue;    //可以，因为mystatic和类相关的
	cout << testvalue << endl;
}
#endif