//�������
#ifndef __HUMAN__
#define __HUMAN__

#include <iostream>

//�ඨ�����������
class Human {
public:
	Human();
	Human(int);
public:
	int m_Age; //����
	char m_Name[100]; //����

	void funcpub() {
		std::cout << "ִ����funcpub() " << std::endl;
	}
public:
	void samenamefunc();
	void samenamefunc(int);
protected:
	int m_prol;
	void funcpro() {
		std::cout << "ִ����funcpro() " << std::endl;
	}
private:
	int m_privl;
	void funcpriv() {
		std::cout << "ִ����funcpriv() " << std::endl;
	}
};

#endif