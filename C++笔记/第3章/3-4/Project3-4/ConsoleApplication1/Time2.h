#ifndef __MYTIME2__
#define __MYTIME2__

class Otherclass {
public:
	Otherclass(int);
};


//�ඨ��(������)
class Time2   //����һ��ʱ����
{
public:
	explicit Time2();  //���������Ĺ��캯��:Ĭ�Ϲ��캯��

	//Time2(int) {};  //�������Ĺ��캯����Ҳ������ʹ�� =default
	//Time2() = default; //�������ܹ�Ϊ���� =default �ĺ����Զ����ɺ����塣

	//int prfuncX() = default; //�����⺯����������ʹ�� = default;
	//Time2() = delete; //�ó���Ա��ʽ�Ľ���ĳ������
public:
	int Hour;
	int Minute;
	int Second{ 0 };
	Otherclass ocl;
};

#endif