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
};


#endif