// 4-7.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

namespace _nmspl
{
	//可变参模板：(Variadic Template) :允许模板中含有0个到任意个模板参数，在语法上也和传统模板不太一眼，多了一个...
	//一、可变参函数模板
	//(1.1)简单范例
	//值得注意的内容:
	//a)我们一般把这个args称为一包 或者 一堆 参数，而且这些参数的类型可以各不相同；
	//我们理解T这种类型的时候，不能把他理解成一个类型，你要理解成0到多个不同的类型，那自然，对应的参数args也应该是多个不同类型的参数
	//b)这 一包参数中可以容纳0到多个模板参数，而且这些模板参数可以为任意的类型；
	//c)大家注意把名字理顺一下:
	  //T后边带了...所以，我们称呼T:可变参类型； 这个东西看起来是一个类型名，实际上里边包含的是0到多个不同的类型(一包类型)；
	  //args：可变形参，既然T代表的是一包类型，那显然args代表的就是一包形参；
	//d)在具体函数形参中，&的位置出现在类型名的后边

	//(1.2)参数包的展开:展开套路比较固定，一般都是用递归函数的方式来展开参数；
	       //要求我们在代码编写中，有一个参数包展开函数，和一个同名的递归终止函数，我们就是通过这两个函数把参数包展开的；
#if 0
	template <typename... T>
	void myfunc(T... args) {   //T: 一包类型 args：一包形参
		cout << sizeof...(args) << endl;   //sizeof...可变参的数量
		cout << sizeof...(T) << endl;
	}

	//---------------------------
	//递归终止函数
	void myfunc1() {
		cout << "参数包展开时执行了递归终止函数myfunc1()" << endl;
	}
	template <typename T, typename...U>
	void myfunc1(const T&firstarg, const U&... otherargs) {   //一个参数，一包参数。这种可变参函数模板写法最适合参数包的展开
		cout << sizeof...(otherargs) << endl;
		cout << "收到的参数值为:" << firstarg << endl;
		myfunc1(otherargs...);  //递归调用，注意写法...
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
	//二、可变参类模板:允许模板定义中含有0到任意个模板参数
	//(2.1)通过递归继承方式展开参数包
	template<typename...Args> class myclass {};   //主模板

	template<> class myclass<> {
	public:
		myclass() {
			cout << "myclass<>::myclass()执行了，this = " << this  << endl;
		}
	};
	template <typename First,typename... Others>
	class myclass<First, Others...> : private myclass<Others...>  //偏特化
	{
	public:
		myclass() : m_i() {
			cout << "myclass::myclass()执行了，this = " << this << endl;
		}
		myclass(First parf, Others... pargs) : m_i(parf), myclass<Others...>(pargs...) {
			cout << "-----------------begin--------------------" << endl;
			cout << "myclass::myclass(parf,pargs)执行了，this = " << this << endl;
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

