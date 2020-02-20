// 4-8.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <list>
using namespace std;

namespace _nmsp
{
	//一、可变参类模板:允许模板定义中含有0到任意个模板参数
	//(1.1)通过递归组合方式展开参数包
	//组合关系(复合关系):类A和类B之间就是一种组合关系
	class B {
	public:
		//
	};
	class A {
	public:
		B b;
	};


	template<typename...Args> class myclass {};   //主模板

	template<> class myclass<> {
	public:
		myclass() {
			cout << "myclass<>::myclass()执行了，this = " << this << endl;
		}
	};
	template <typename First, typename... Others>
	class myclass<First, Others...>   //偏特化
	{
	public:
		myclass() : m_i() {
			cout << "myclass::myclass()执行了，this = " << this << endl;
		}
		myclass(First parf, Others... pargs) : m_i(parf), m_o(pargs...) {
			cout << "-----------------begin--------------------" << endl;
			cout << "myclass::myclass(parf,pargs)执行了，this = " << this << endl;
			cout << "m_i=" << m_i << endl;
			cout << "-----------------end--------------------" << endl;
		}
		First m_i;
		myclass<Others...> m_o;  //组合关系(复合关系)
	};

	

	void func() {
		//myclass<int, float, double> myc;
		myclass<int, float, double> myc(12, 3.5f, 23);
	}
}

namespace _nmsp1
{
	//一、可变参数模板
	//(1.2)通过tuple和递归调用展开参数包
	//这种展开参数包的方式需要写类的特化版本，有一定难度：
	//实现思路:计数器从0开始，每处理一个参数，计数器+1.一直到把所有参数处理完，最后搞一个模板特化。作为递归调用结束
	
	//(1.3)总结
	//获取参数包里参数的方式有很多种:一般都离不开递归手段


	//mycount用于统计，从0开始，mymaxcount表示参数数量
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
	//需要有一个特化版本，用于结束递归调用
	template <int mymaxcount, typename...T>
	class myclass<mymaxcount, mymaxcount, T...>
	{
	public:
		static void mysfunc(const tuple<T...>&t)
		{

		}
	};

	template <typename...T>
	void myfunc(const tuple<T...>&t)   //可变参数模板
	{
		myclass<0, sizeof...(T), T...>::mysfunc(t);
	}

	void func() {
		tuple<float, int, int> mytuple(12.5f, 100, 52);  //一个tuple(元组)：一堆各种东西的组合
		/*cout << get<0>(mytuple) << endl;
		cout << get<1>(mytuple) << endl;
		cout << get<2>(mytuple) << endl;*/
		myfunc(mytuple);
	}

}

namespace _nmsp2
{
	//二、模板 模板参数：这表示 这是个模板参数。这个模板参数本身，又是一个模板；
	template <
		    typename T,  //类型模板参数
			template<class> class Containter   //这是一个模板 模板参数
			//template<typename W> typename Container
	        >   //T U 叫模板参数，因为他们前边都有typename，所以又称为 类型 模板参数
	class myclass
	{
	public:
		T m_i;

		Containter<T> myc;  //Container作为一个类模板来使用的(因为他屁股后边代码<T>),所以它是个类模板；
		                    //大家要明白，如果你要想把Containter当成一个类模板来用，你就必须把他弄成“模板模板参数”这种写法
		myclass()
		{
			for (int i = 0; i < 10; ++i) {
				myc.push_back(i);
			}
		}
	};

	template<typename T>
	using MYvec = vector<T, allocator<T>>;   //这种套路，写法很固定
	template<typename T>
	using MYList = list<T, allocator<T>>;   //这种套路，写法很固定
	void func() {
		myclass<int, MYvec> myvecobj;  //本意是往容器中塞入元素，元素类型为int
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

