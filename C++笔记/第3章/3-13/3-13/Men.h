#ifndef __MEN__
#define __MEN__
#include <iostream>
#include "Human.h" 
//类的定义
class Men : public Human{ //表示Men是Human的子类
public:
	Men();
	~Men();
	void samenamefunc(int);
	void funcmen() {

	}
public:
	using Human::samenamefunc;

	void eat();
	virtual void eat1() {

	}

	void testfunc() {
		std::cout << "Men   testfunc()" << std::endl;
	}
};



#endif