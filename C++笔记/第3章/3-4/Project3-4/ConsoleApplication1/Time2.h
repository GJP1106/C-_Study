#ifndef __MYTIME2__
#define __MYTIME2__

class Otherclass {
public:
	Otherclass(int);
};


//类定义(类声明)
class Time2   //定义一个时间类
{
public:
	explicit Time2();  //不带参数的构造函数:默认构造函数

	//Time2(int) {};  //待参数的构造函数，也不可以使用 =default
	//Time2() = default; //编译器能够为这种 =default 的函数自动生成函数体。

	//int prfuncX() = default; //非特殊函数，不可以使用 = default;
	//Time2() = delete; //让程序员显式的禁用某个函数
public:
	int Hour;
	int Minute;
	int Second{ 0 };
	Otherclass ocl;
};

#endif