#ifndef __WOMEN__
#define __WOMEN__
#include <iostream>
#include "Human.h" 
//��Ķ���
class Women : public Human{ //��ʾMen��Human������
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