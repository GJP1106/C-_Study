#ifndef __MEN__
#define __MEN__
#include <iostream>
#include "Human.h" 
//��Ķ���
class Men : public Human{ //��ʾMen��Human������
public:
	Men();
	void samenamefunc(int);
public:
	using Human::samenamefunc;
};



#endif