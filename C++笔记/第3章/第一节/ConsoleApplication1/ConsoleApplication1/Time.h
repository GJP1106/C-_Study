#ifndef __MYTIME__
#define __MYTIME__

//类定义(类声明)
class Time //定义一个时间类
{
private:
	int Millisecond;
private:
	void initMillTime(int mls);
public:
	int Hour;  //小时
	int Minute;  //分钟
	int Second; //秒钟

	//成员函数

	void initTime(int tmphour, int tmpmin, int tmpsec);
};


#endif