#ifndef __MYTIME__
#define __MYTIME__

//类定义(类声明)
class Time //定义一个时间类
{
private:
	int Millisecond;
private:
	
public:
	int Hour;  //小时
	int Minute;  //分钟
	//int Second; //秒钟
	int Second = 0; //秒钟

	mutable int testvale;
	const int ctestvalue;  //定义了一个常量

	//成员函数

	void initTime(int tmphour, int tmpmin, int tmpsec);
	void initMillTime(int mls);

public:
     //构造函数
	explicit Time(int tmphour, int tmpmin, int tmpsec);
	//不加参数
	Time();
	//带两个参数的构造函数
	Time(int tmphour, int tmpmin);
	explicit Time(int tmphour);

public:
	void addhour(int tmphour) const;
	void noone() const 
	{
		testvale = 15;
	};


public:
	//把自己给返回去了
	Time& add_hour(int tmphour);
	Time& add_minute(int tmpminute);

	//static int mystatic; //声明静态成员变量，还没有分配内存，所以也不能在这里初始化
	//static void mstafunc(int testvalue);
	





};

void WriteTime(Time &mytime);


#endif