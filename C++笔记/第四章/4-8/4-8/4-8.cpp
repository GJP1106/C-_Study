// 4-8.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <list>
using namespace std;

namespace _nmsp
{
	//һ���ɱ����ģ��:����ģ�嶨���к���0�������ģ�����
	//(1.1)ͨ���ݹ���Ϸ�ʽչ��������
	//��Ϲ�ϵ(���Ϲ�ϵ):��A����B֮�����һ����Ϲ�ϵ
	class B {
	public:
		//
	};
	class A {
	public:
		B b;
	};


	template<typename...Args> class myclass {};   //��ģ��

	template<> class myclass<> {
	public:
		myclass() {
			cout << "myclass<>::myclass()ִ���ˣ�this = " << this << endl;
		}
	};
	template <typename First, typename... Others>
	class myclass<First, Others...>   //ƫ�ػ�
	{
	public:
		myclass() : m_i() {
			cout << "myclass::myclass()ִ���ˣ�this = " << this << endl;
		}
		myclass(First parf, Others... pargs) : m_i(parf), m_o(pargs...) {
			cout << "-----------------begin--------------------" << endl;
			cout << "myclass::myclass(parf,pargs)ִ���ˣ�this = " << this << endl;
			cout << "m_i=" << m_i << endl;
			cout << "-----------------end--------------------" << endl;
		}
		First m_i;
		myclass<Others...> m_o;  //��Ϲ�ϵ(���Ϲ�ϵ)
	};

	

	void func() {
		//myclass<int, float, double> myc;
		myclass<int, float, double> myc(12, 3.5f, 23);
	}
}

namespace _nmsp1
{
	//һ���ɱ����ģ��
	//(1.2)ͨ��tuple�͵ݹ����չ��������
	//����չ���������ķ�ʽ��Ҫд����ػ��汾����һ���Ѷȣ�
	//ʵ��˼·:��������0��ʼ��ÿ����һ��������������+1.һֱ�������в��������꣬����һ��ģ���ػ�����Ϊ�ݹ���ý���
	
	//(1.3)�ܽ�
	//��ȡ������������ķ�ʽ�кܶ���:һ�㶼�벻���ݹ��ֶ�


	//mycount����ͳ�ƣ���0��ʼ��mymaxcount��ʾ��������
	template<int mycount,int mymaxcount, typename...T>
	class myclass
	{
	public:
		static void mysfunc(const tuple<T...>&t)
		{
			cout << "value = " << get<mycount>(t) << endl;
			myclass<mycount + 1, mymaxcount, T...>::mysfunc(t);
		}
	};
	//��Ҫ��һ���ػ��汾�����ڽ����ݹ����
	template <int mymaxcount, typename...T>
	class myclass<mymaxcount, mymaxcount, T...>
	{
	public:
		static void mysfunc(const tuple<T...>&t)
		{

		}
	};

	template <typename...T>
	void myfunc(const tuple<T...>&t)   //�ɱ����ģ��
	{
		myclass<0, sizeof...(T), T...>::mysfunc(t);
	}

	void func() {
		tuple<float, int, int> mytuple(12.5f, 100, 52);  //һ��tuple(Ԫ��)��һ�Ѹ��ֶ��������
		/*cout << get<0>(mytuple) << endl;
		cout << get<1>(mytuple) << endl;
		cout << get<2>(mytuple) << endl;*/
		myfunc(mytuple);
	}

}

namespace _nmsp2
{
	//����ģ�� ģ����������ʾ ���Ǹ�ģ����������ģ�������������һ��ģ�壻
	template <
		    typename T,  //����ģ�����
			template<class> class Containter   //����һ��ģ�� ģ�����
			//template<typename W> typename Container
	        >   //T U ��ģ���������Ϊ����ǰ�߶���typename�������ֳ�Ϊ ���� ģ�����
	class myclass
	{
	public:
		T m_i;

		Containter<T> myc;  //Container��Ϊһ����ģ����ʹ�õ�(��Ϊ��ƨ�ɺ�ߴ���<T>),�������Ǹ���ģ�壻
		                    //���Ҫ���ף������Ҫ���Containter����һ����ģ�����ã���ͱ������Ū�ɡ�ģ��ģ�����������д��
		myclass()
		{
			for (int i = 0; i < 10; ++i) {
				myc.push_back(i);
			}
		}
	};

	template<typename T>
	using MYvec = vector<T, allocator<T>>;   //������·��д���̶ܹ�
	template<typename T>
	using MYList = list<T, allocator<T>>;   //������·��д���̶ܹ�
	void func() {
		myclass<int, MYvec> myvecobj;  //������������������Ԫ�أ�Ԫ������Ϊint
		myclass<int, MYList> myvecobj1;
	}
}

int main()
{
	//_nmsp::func();
	//_nmsp1::func();
	_nmsp2::func();

	return 0;
}

