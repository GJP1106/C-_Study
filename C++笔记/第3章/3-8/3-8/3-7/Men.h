#ifndef __MEN__
#define __MEN__
#include <iostream>
#include "Human.h" 
//��Ķ���
class Men : public Human{ //��ʾMen��Human������
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
};



#endif