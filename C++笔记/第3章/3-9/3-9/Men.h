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
	//��Ϊ��Ԫ�������������Ա��������Ԫ������������public protected private������
	friend void func(const Men &tempmen);  //�ú�������Ԫ����
};



#endif