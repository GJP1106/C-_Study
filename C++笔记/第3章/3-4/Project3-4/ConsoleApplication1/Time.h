#ifndef __MYTIME__
#define __MYTIME__

//�ඨ��(������)
class Time //����һ��ʱ����
{
private:
	int Millisecond;
private:
	
public:
	int Hour;  //Сʱ
	int Minute;  //����
	//int Second; //����
	int Second = 0; //����

	mutable int testvale;
	const int ctestvalue;  //������һ������

	//��Ա����

	void initTime(int tmphour, int tmpmin, int tmpsec);
	void initMillTime(int mls);

public:
     //���캯��
	explicit Time(int tmphour, int tmpmin, int tmpsec);
	//���Ӳ���
	Time();
	//�����������Ĺ��캯��
	Time(int tmphour, int tmpmin);
	explicit Time(int tmphour);

public:
	void addhour(int tmphour) const;
	void noone() const 
	{
		testvale = 15;
	};


public:
	//���Լ�������ȥ��
	Time& add_hour(int tmphour);
	Time& add_minute(int tmpminute);

	//static int mystatic; //������̬��Ա��������û�з����ڴ棬����Ҳ�����������ʼ��
	//static void mstafunc(int testvalue);
	





};

void WriteTime(Time &mytime);


#endif