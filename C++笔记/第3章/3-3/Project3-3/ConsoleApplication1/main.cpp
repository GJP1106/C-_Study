// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*
������
**/


#include "stdafx.h"
#include "Time.h"
#include <iostream>
using namespace std;
static int g_abc = 15;   //Ҳ�����ھ�̬�洢�������Ƹ�ȫ�ֱ���ֻ�ܹ����ڱ��ļ��У�


void funcm()
{
	static int abc = 5; //�ֲ���̬����

	abc = 8;
}
//��̬��Ա��������(�����ڴ�)
int Time::mystatic = 15; // ���Բ�����ֵ����ôϵͳĬ�ϸ�0������ʱ����Ҫʹ��static

int main()
{

	//һ�����ඨ����ʵ�ֳ�Ա����inline:���ڵĳ�Ա����ʵ����ʵҲ�����ڵĳ�Ա��������
	//����ֱ������Ķ�����ʵ�ֵĳ�Ա�������ᱻ����inline��������������


	//������Ա����ĩβ��const
#if 0
	//const:�������ڳ�Ա����ƨ�ɺ�������һ��const������Ҫ�ڳ�Ա��������������const��ҲҪ�ڳ�Ա��������������const��
	//���ã�����ϵͳ�������Ա���������޸ĸö������κγ�Ա������ֵ�ȵȡ�Ҳ����˵�������Ա���������޸���Time���κ�״̬��
	//ƨ�ɺ�߼���һ��const��׺�ĳ�Ա������������Ա������
	const Time abc; //����const�������ֶ���������
	Time def;
	//abc.initMillTime(1500);  //�����ԣ�initMillTime()������const��Ա���������initMillTime()ֻ�ܱ���const������á�
	def.initMillTime(1500);
	//abc.noone();  //�����Ե���noone(),��Ϊnoone()û��������const
	def.noone();
	//noone�������const��
	abc.noone();

	//const��Ա���� �򲻹���const���� ���Ƿ�const�������Ե���const��Ա������
	//����const��Ա���������ܹ���const������ã�ֻ�ܱ���const������á�
#endif

	//����mutable(���ȶ������׸ı����˼)��const�ķ���ʡ� mutable������Ҳ������Ϊ��ͻ��const�����ơ�
	//��mutable����һ����Ա������һ����Ա����һ����mutable�����ˣ��ͱ�ʾ�����Ա������Զ���ڿ��Ա��޸�״̬��
	//��������const��β�ĳ�Ա�����У�Ҳ���Ա��޸ġ�
	//const Time abc;
	//abc.noone();

	//�ġ����������������ã�this
	//���������this�����ǵ��ó�Ա����ʱ��������������������ĵ�ַ(&mytime)���ݸ������Ա�����е�һ�����ص�this�β�
	//��ϵͳ�Ƕȿ������κζ����Ա��ֱ�ӷ��ʶ���������ͨ��this����ʽ���õġ�
#if 0
	Time mytime;
	mytime.add_hour(3);  //mytime.add_hour(&mytime, 3)
#endif
	//a)thisָ��ֻ���ڳ�Ա������ʹ�ã�ȫ�ֺ�������̬����������ʹ��thisָ�롣
	//b)����ͨ��Ա�����У�this��һ��ָ���const�����constָ��(����ΪTime����ôthis����Time *const this),��ʾthisֻ��ָ��ǰTime����
	//c)��const��Ա�����У�thisָ����һ��ָ��const�����constָ��(����ΪTime, this����const Time *const this���͵�ָ��)
#if 0
	Time mytime;
	mytime.add_hour(3).add_hour(4).add_minute(12);  //mytime.add_hour(&mytime, 3)
#endif


	//�塢static��Ա
	//������������ĳ�Ա���������ֳ�Ա�����ͽ���static��Ա������
	//�ص㣺������ĳ���������������࣬����һ����ĳ���������޸���������Ա������ֵ��������������ֱ���ܹ������޸ĵĽ��
	//���ֳ�Ա����ֻ��һ���������������ֳ�Ա���������ã������õ�������::��Ա������
	//��Ա����ǰ��Ҳ���Լ�static���ɾ�̬��Ա����������������ĳ�Ա����������ʱ ����::��Ա������(...)
	//��ζ��徲̬��Ա����(����):����һ�����ĳ��.cppԴ�ļ��Ŀ�ͷ�����������̬��Ա������
	//�������ܹ���֤�ڵ����κκ���֮ǰ�����̬��Ա�����Ѿ����ɹ���ʼ���ˡ�
#if 0
	Time mytime1;
	mytime1.Minute = 15;

	Time mytime2;
	mytime2.Minute = 30;

	cout << mytime1.Minute << endl;
	cout << mytime2.Minute << endl;
#endif

	
	cout << Time::mystatic << endl;
	Time mytime1;
	mytime1.mystatic = 10;
	Time mytime2;

	cout << Time::mystatic << endl;
	cout << mytime1.mystatic << endl;

	Time::mstafunc(12);
	mytime1.mstafunc(15);
	cout << Time::mystatic << endl;


	
	





	return 0;
}

