#ifndef __MEN__
#define __MEN__
#include <iostream>
#include "Human.h" 
//类的定义
class Men : public Human{ //表示Men是Human的子类
public:
	Men();
	void samenamefunc(int);
public:
	using Human::samenamefunc;
};



#endif