#ifndef __MYTIME__
#define __MYTIME__

//�ඨ��(������)
class Time //����һ��ʱ����
{
private:
	int Millisecond;
private:
	void initMillTime(int mls);
public:
	int Hour;  //Сʱ
	int Minute;  //����
	int Second; //����

	//��Ա����

	void initTime(int tmphour, int tmpmin, int tmpsec);

public:
     //���캯��
	explicit Time(int tmphour, int tmpmin, int tmpsec);
	//���Ӳ���
	Time();
	//�����������Ĺ��캯��
	Time(int tmphour, int tmpmin);
	explicit Time(int tmphour);
};


#endif