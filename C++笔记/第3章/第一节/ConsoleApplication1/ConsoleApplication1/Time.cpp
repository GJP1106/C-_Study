#include "stdafx.h"
#include "Time.h"

//��Ա����initTime()ʵ�� 
//����������ð�Ž� ����������� ����ʾinitTime��������Time�ࡣ
void Time::initTime(int tmphour, int tmpmin, int tmpsec)
{
	Hour = tmphour;   //����ע�⵽����Ա�����У����ǿ���ֱ��ʹ�ó�Ա������
	                  //�ĸ�������õĸó�Ա��������Щ��Ա�����������ĸ����󣬴�ҿ����������Ա����֪���ĸ���������Լ���
    Minute = tmpmin;  
	Second = tmpsec;
	initMillTime(0);
}

void Time::initMillTime(int mls)
{
	Millisecond = mls;   //��Ա�������Է��ʳ�Ա���������ܳ�Ա�Ƿ���˽��
}