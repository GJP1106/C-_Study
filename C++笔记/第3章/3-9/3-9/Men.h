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
	/*void funcmen() {

	}*/
public:
	using Human::samenamefunc;

	void eat();
	virtual void eat1() {

	}
private:
	void funcmen() const {
		std::cout << "test" << std::endl;
	}
	//因为友元函数不属于类成员，所以友元函数声明不受public protected private的限制
	friend void func(const Men &tempmen);  //该函数是友元函数
};



#endif