
//#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_set>
#include <functional>
#include <queue>

using namespace std;
//
namespace _nmsp1
{
	//一：类型萃取概述（type traits）:泛型编程，在stl的实现源码中，这种类型萃取技术用的比较多；
	//第八章，五节 过滤器（萃取机）；萃取：提取一些信息出来； 
	//c++11 ，标准库里提供了很多类型萃取的接口 ，这些接口其实就是一些类模板；
	//https://en.cppreference.com/w/cpp/types

	//二：类型萃取范例
	//通过萃取接口 中的value值为true ,false咱们就能够萃取出很多有用信息；

	//三：迭代器萃取概述（iterators traits)
	//八章 STL标准模板库大局观 ，5节； 给定迭代器 ，能够萃取出迭代器的种类；

	//四：总结：
	//c++中，模板与泛型编程 ，模板元编程； 常用于开发标准库，接口库等等；


	template <typename T>
	void printTraitsInfo(const T& t)
	{
		cout << "--------------begin-----------" << endl;

		cout << "我们要萃取的类型名字是：" << typeid(T).name() << endl;

		cout << "is_void = " << is_void<T>::value << endl;                                    //类型是否是void
		cout << "is_class = " << is_class<T>::value << endl;                                  //类型是否是一个class
		cout << "is_object = " << is_object<T>::value << endl;                                //类型是否是 一个对象类型
		cout << "is_pod = " << is_pod<T>::value << endl;                                      //是否普通类（只包含成员变量，不包含成员函数）；   POD(plain old data)
		cout << "is_default_constructible = " << is_default_constructible<T>::value << endl;  //是否有缺省构造函数
		cout << "is_copy_constructible = " << is_copy_constructible<T>::value << endl;        //是否有拷贝构造函数
		cout << "is_move_constructible = " << is_move_constructible<T>::value << endl;        //是否有移动构造函数
		cout << "is_destructible = " << is_destructible<T>::value << endl;                    //是否有析构函数
		cout << "is_polymorphic = " << is_polymorphic<T>::value << endl;                      //是否含有虚函数
		cout << "is_trivially_default_constructible = " << is_trivially_default_constructible<T>::value << endl;      //缺省拷贝构造函数是否是可有可无的(没有也行的),返回1表示确实可有可无

		cout << "has_virtual_destructor = " << has_virtual_destructor<T>::value << endl;      //是否有虚析构函数

		cout << "--------------end-------------" << endl;

	}

	class A
	{
	public:
		A() = default;
		A(A&& ta) = delete;           //移动构造：你要不写delete，系统一般就会认为你有这个成员函数；
		A(const A& ta) = delete;      //拷贝构造 
		virtual ~A() {}
	};
	class B
	{
	public:
		int m_i;
		int m_j;
	};
	class C
	{
	public:
		C(int t) {} //有自己的构造函数，编译器不会给你提供缺省构造函数
	};

	void func()
	{
		printTraitsInfo(int());     //扔一个临时对象进去
		printTraitsInfo(string());
		printTraitsInfo(A());
		printTraitsInfo(B());
		printTraitsInfo(C(1));
		printTraitsInfo(list<int>());
	}
}


int main()
{
	_nmsp1::func();

	return 1;
}


