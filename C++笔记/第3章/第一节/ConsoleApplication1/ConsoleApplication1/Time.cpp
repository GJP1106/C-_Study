#include "stdafx.h"
#include "Time.h"

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