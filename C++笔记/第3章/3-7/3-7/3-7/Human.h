//定义基类
#ifndef __HUMAN__
#define __HUMAN__

#include <iostream>

//类定义或者类声明
class Human {
public:
	Human();
	Human(int);
public:
	int m_Age; //年龄
	char m_Name[100]; //名字

	void funcpub() {
		std::cout << "执行了funcpub() " << std::endl;
	}
public:
	void samenamefunc();
	void samenamefunc(int);
protected:
	int m_prol;
	void funcpro() {
		std::cout << "执行了funcpro() " << std::endl;
	}
private:
	int m_privl;
	void funcpriv() {
		std::cout << "执行了funcpriv() " << std::endl;
	}
};

#endif