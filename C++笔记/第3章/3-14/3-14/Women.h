#ifndef __WOMEN__
#define __WOMEN__
#include <iostream>
#include "Human.h" 
//类的定义
class Women : public Human{ //表示Men是Human的子类
public:
	Women();
	~Women();
	void samenamefunc(int);
	void funcmen() {

	}
public:
	using Human::samenamefunc;

	void eat();
	virtual void eat1() {

	}
};



#endif