// 4-7.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

namespace _nmspl
{
	//�ɱ��ģ�壺(Variadic Template) :����ģ���к���0���������ģ����������﷨��Ҳ�ʹ�ͳģ�岻̫һ�ۣ�����һ��...
	//һ���ɱ�κ���ģ��
	//(1.1)�򵥷���
	//ֵ��ע�������:
	//a)����һ������args��Ϊһ�� ���� һ�� ������������Щ���������Ϳ��Ը�����ͬ��
	//�������T�������͵�ʱ�򣬲��ܰ�������һ�����ͣ���Ҫ����0�������ͬ�����ͣ�����Ȼ����Ӧ�Ĳ���argsҲӦ���Ƕ����ͬ���͵Ĳ���
	//b)�� һ�������п�������0�����ģ�������������Щģ���������Ϊ��������ͣ�
	//c)���ע���������˳һ��:
	  //T��ߴ���...���ԣ����ǳƺ�T:�ɱ�����ͣ� ���������������һ����������ʵ������߰�������0�������ͬ������(һ������)��
	  //args���ɱ��βΣ���ȻT�������һ�����ͣ�����Ȼargs����ľ���һ���βΣ�
	//d)�ھ��庯���β��У�&��λ�ó������������ĺ��

	//(1.2)��������չ��:չ����·�ȽϹ̶���һ�㶼���õݹ麯���ķ�ʽ��չ��������
	       //Ҫ�������ڴ����д�У���һ��������չ����������һ��ͬ���ĵݹ���ֹ���������Ǿ���ͨ�������������Ѳ�����չ���ģ�
#if 0
	template <typename... T>
	void myfunc(T... args) {   //T: һ������ args��һ���β�
		cout << sizeof...(args) << endl;   //sizeof...�ɱ�ε�����
		cout << sizeof...(T) << endl;
	}

	//---------------------------
	//�ݹ���ֹ����
	void myfunc1() {
		cout << "������չ��ʱִ���˵ݹ���ֹ����myfunc1()" << endl;
	}
	template <typename T, typename...U>
	void myfunc1(const T&firstarg, const U&... otherargs) {   //һ��������һ�����������ֿɱ�κ���ģ��д�����ʺϲ�������չ��
		cout << sizeof...(otherargs) << endl;
		cout << "�յ��Ĳ���ֵΪ:" << firstarg << endl;
		myfunc1(otherargs...);  //�ݹ���ã�ע��д��...
	}

	void func() {
		/*myfunc();
		myfunc(1, 2);
		myfunc(1, 2, 3, 43);*/
		myfunc1(1,"abc",10,"ddd");
	}
#endif
}
namespace _nmspl1
{
	//�����ɱ����ģ��:����ģ�嶨���к���0�������ģ�����
	//(2.1)ͨ���ݹ�̳з�ʽչ��������
	template<typename...Args> class myclass {};   //��ģ��

	template<> class myclass<> {
	public:
		myclass() {
			cout << "myclass<>::myclass()ִ���ˣ�this = " << this  << endl;
		}
	};
	template <typename First,typename... Others>
	class myclass<First, Others...> : private myclass<Others...>  //ƫ�ػ�
	{
	public:
		myclass() : m_i() {
			cout << "myclass::myclass()ִ���ˣ�this = " << this << endl;
		}
		myclass(First parf, Others... pargs) : m_i(parf), myclass<Others...>(pargs...) {
			cout << "-----------------begin--------------------" << endl;
			cout << "myclass::myclass(parf,pargs)ִ���ˣ�this = " << this << endl;
			cout << "m_i=" << m_i << endl;
			cout << "-----------------end--------------------" << endl;
		}
		First m_i;
	};

	void func() {
		//myclass<int, float, double> myc;
		myclass<int, float, double> myc(12, 3.5f, 23);
	}
}

int main()
{
	//_nmspl::func();
	_nmspl1::func();
	return 0;
}

