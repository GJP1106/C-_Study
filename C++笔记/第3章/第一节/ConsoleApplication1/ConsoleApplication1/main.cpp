// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
/*
第三章
**/


#include "stdafx.h"
#include "Time.h"
#include <iostream>
using namespace std;


//for 二(3)
class student {
public:
	int number;
	char name[100];
};


//for 三、成员函数
#if 0 //移到Time.h
class Time //定义一个时间类
{
public:
	int Hour;  //小时
	int Minute;  //分钟
	int Second; //秒钟

	//成员函数
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

	//一:综述：类是我们自己定义的数据类型(新类型)
	//设计类时要考虑的角度:
	//(1)站在设计和实现者的角度来考虑；
	//(2)站在使用者的角度来考虑；
	//(3)父类、子类；


	//二、类的基础
	//(1)一个类就是一个用户自己定义的数据类型，我们可以把类想象成一个命名空间，包括一堆东西(成员函数，成员变量)；
	//(2)一个类的构成:成员变量，成员变量，成员函数(有许多特殊成员函数，后续慢慢讲解)。
	//(3)我们访问类成员时，如果是类的对象，我们就使用 对象名.成员名  来访问成员。
	     //如果是指向这个对象的指针，我们就用 指针名->成员名  来访问成员。
#if 0
	student someone; //定义类的对象
	someone.number = 1000;
	student *psomeone = &someone;
	psomeone->number = 1005;

	cout << someone.number << endl;
#endif

	//(4)public成员提供类的接口，暴漏给外界，供外界调用。private成员提供各种实现类功能的细节方法，但不暴漏给使用
	//   这些private成员。
	//(5)struct 是成员默认为public的class; struct A{....}
	//(6)class成员默认是private(私有);  class A{....}
	//struct A{....}  等价于  class A {public: ...}


	//三、成员函数
#if 0
	Time myTime;
#if 0  //和开头initTime非成员函数相对应
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

	//四、对象拷贝
#if 0
	//对象本身是可以拷贝的
	//默认情况下，这种类对象的拷贝，是每个成员变量逐个拷贝。
	//如果在类Time中我们要定义适当的 赋值运算符 就能够控制对象的这种拷贝行为
	Time myTime; //
	myTime.Hour = 12;
	myTime.Minute = 15;
	myTime.Second = 40;

	Time myTime2 = myTime;
	Time myTime3(myTime);   //int a = 4; int b(a);
#if 0
	Time myTime4{ myTime };  //C++11支持
	Time myTime5 = { myTime }; //C++11支持
	myTime5.Hour = 8;
#endif
#endif

	//五、私有成员
	Time myTime; //类对象
	myTime.Hour = 5;
	//myTime.Millisecond = 1000;    //私有的不能直接，成员变量名引用
	//myTime.initMillTime();  //不能访问私有成员函数
	myTime.initTime(11,11,11);

	return 0;
}

