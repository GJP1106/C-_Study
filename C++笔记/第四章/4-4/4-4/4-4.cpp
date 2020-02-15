// 4-4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "myarray.h"
#include "myvector.h"
#include "ca.h"
using namespace std;

//"显示实例化" 手段中的"实例化声明"
extern template A<float>;  //其他所有.cpp文件都这么写
                           //extern作用:不会在本文件中生成一个extern后边所表示的模板的实例化版本代码
                           //extern目的:告诉编译器，在其他的源文件(.cpp文件)中已经有了一个该模板的实例化版本了。
extern template void myfunc123(int v1, int v2);


#if 0   //一、普通类的成员函数模板
class A {  //普通类
public:
	template <typename T>
	void myft(T tmpt) {   //成员函数模板
		cout << tmpt << endl;
	}
};
#endif
#if 0  //移植到ca.h
template <typename C>
class A {  //普通类
public:
	template <typename T2>
	A(T2 v1, T2 v2);
	//A(T2 v1, T2 v2) {  //构造函数我们也引入自己的模板，和整个类的模板C没有关系

	//}
	 
	template <typename T>
	void myft(T tmpt) {   //成员函数模板
		cout << tmpt << endl;
	}
	void myftpt() {}
	C m_ic;
};

template <typename C>  //先跟类的模板参数列表
template <typename T2> //再跟构造函数自己的模板参数列表
A<C>::A(T2 v1, T2 v2) {
	cout << v1 << v2 << endl;
}
#endif


int main()
{
	//一、普通类的成员函数模板
	//不管是普通类，还是类模板，它的成员函数可以是一个函数模板，称为"成员函数模板"，不可以是虚函数，否则编译器会报错
#if 0
	A a;
	a.myft(3);  //编译器在遇到这条语句时，编译器就会实例化这个函数模板
#endif

	//二、类模板的成员函数模板
	//类模板的模板参数必须用<>指定，成员函数模板(函数模板)的参数都可以推断
#if 0
	A<float> a(1, 2);
	A<float> a2(1.1, 2.2);
#endif
	//类模板的成员函数(包括普通成员函数/成员函数模板)只有为程序所用(代码中出现了对该函数或者该函数模板的调用时)才进行实例化
	  //如果某函数从未使用，则不会实例化该成员函数。


	//三、模板显示实例化，模板声明
	//为了防止在多个.cpp文件中都实例化相同的 类模板，所以C++11提出了一个解决方法，我们称为"显示实例化"
	  //通过"显示实例化"来避免这种生成多个相同类模板实例的开销
	A<int> tmpobj(6, 7);
	//模板的实例化定义只有一个，实例化声明可以有多个

	//总结：
	//(1)vs2017不太推荐这个特色
	//(2) template A<float>
	    //extern template A<float>






	return 0;
}

