// 3-9.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Human.h"
#include "Men.h"
#include "Women.h"
#include "func.h"
#include "A.h"
#include "C.h"
using namespace std;

//class A {
//private:
//	int data;
//
//	friend class C; //�������Ԫ�����������Ȼ��ʱ��Cû�ж��壬����ϵͳû����
//};
//class C {
//public:
//	void callCAF(int x, A &a) {
//		a.data = x;
//		cout << a.data << endl;
//	}
//	void callCAF1(A &a) {
//		a.data;
//	}
//};

int main()
{
	//friend

	//һ����Ԫ���������Ǹ�����
	//public protected private
	//ֻҪ�ú���func��Ϊ��Men����Ԫ��������ôfunc����������ܹ�������Men�����г�Ա(��Ա��������Ա����)��private,protected public

	/*Men men;
	func(men);*/

	//�ܽ᣺��Ԫ����func():�Ǹ�������ͨ������Ϊĳ����Men����Ԫ�����������ܷ��������(Men)�����г�Ա������public protected private

	//������Ԫ�ࣺ�� ���԰��������ඨ�����Ԫ�ࡣ��� ���� �ҵ� ��Ԫ�࣬��ô��Ϳ�������ĳ�Ա�����з����ҵ����г�Ա������public protected private
	//�����޸���A�� ����C��Ϊ��A������(Ҳ��������C��Ϊ��A����Ԫ��)

	/*A a;
	C c;
	c.callCAF(3, a);*/
	//ע�⣺ÿ���඼��������Լ�����Ԫ�����Ԫ����������
	//(1)��Ԫ��ϵ���ܱ��̳�
	//(2)��Ԫ��ϵ�ǵ���ģ������ϱ���C����A����Ԫ�࣬���Ⲣ����ʾ��A����C����Ԫ�ࣻ
	//(3)��Ԫ��ϵû�д����ԣ�������B����A����Ԫ�࣬��C����B����Ԫ�࣬�Ⲣ����ʾ��C����A����Ԫ��

	//������Ԫ��Ա����
	//д������Ԫ��Ա����������Ҫע�������֯�ṹ����Ϊ������������Ͷ�������������ϵ����ߡ�
	A a;
	C c;
	c.callCAF(3, a);

	//�ܽ᣺friend
	//�ŵ�:�����ڴ��������ĳЩ�ǳ�Ա�����������protected��private��Ա���Ӷ������Ԫ��ôһ�����ʹ����protected private��Ա�����
	//ȱ��:��Ҳ���ƻ�����ķ�װ�ԣ���������Ŀɿ��ԺͿ�ά���ԡ�


	return 0;
}

