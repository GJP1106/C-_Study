// 4-3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "myarray.h"
#include "myvector.h"
#include <string>
using namespace std;


template<typename T>
typename T::size_type getlength(const T&c) {
	if (c.empty()) {
		return 0;
	}
	return c.size();
}

//我们要把函数指针作为 某个函数的参数进行传递，怎么做到呢?
//函数指针要想当做 函数的参数就需要:
typedef int(*FunType)(int, int);   //定义一个函数指针类型

int mf(int tmp1, int tmp2) {
	//....
	return 1;
}
/*
void testfunc(int i, int j, FunType funcpoint) //funcpoint就是函数指针
{
	//我们就可以通过函数指针调用函数:
	int result = funcpoint(i, j);   //相当于调用函数 mf
	cout << result << endl;
}
*/

//可调用对象所代表的类
class tc {
public:
	tc() { cout << "构造函数执行" << endl; }
	tc(const tc& t) { cout << "拷贝构造函数执行" << endl; }

	//重载圆括号
	int operator()(int v1, int v2) const {
		return v1 + v2;
	}
};
//将testfunc改为模板函数
//testfunc(3, 4, mf);
//testfunc(3,4);
template <typename T, typename F=tc>
void testfunc(const T &i, const T &j, F funcpoint = F()) {
	cout << funcpoint(i,j) << endl;
}



int main()
{
	//一、typename的使用场合
	//(1)在模板定义里，表明其后的模板参数是类型参数。
	//typename
	//template<typename T,int a,int b>  //typename后边跟的是一个类型
	//int funcaddv2(T c) {...}
	//类模板
	//template<class T>  //名字为T的模板参数。这里虽然可以用class，但是这里的class不是类定义的意思，不能和类定义混为一谈
	//class myvector {...}
	//typename 可以写成 class

	//(2)使用类的类型成员，用typename来标识这是一个类型；
	//::作用域运算符  访问类中的静态成员的时候， 类名::静态成员名
	//int Time::mystatic = 5;
	//::还可以用来访问类型成员
	//typename的第二个用法：通知编译器，一个名字代表的是一个类型。这里的typename不能换成class
#if 0
	string mytest = "I love china!";

	//string::size_type 类似于 unsigned int
	string::size_type size = getlength(mytest);
#endif

	//二、函数指针做其他函数的参数
	//testfunc(3, 4, mf);

	//三、函数模板趣味用法举例
#if 0
	testfunc(3, 4, mf);

	//老师引入一个感念:可调用对象。  “未归类知识点”这一章 第一节 “可调用对象”；
	tc tcobj;
	testfunc(3, 4, tcobj);
	//testfunc(3, 4, tc());  //奇特
#endif

	//四、默认模板参数
	//a)类模板，类模板名后边必须用<>来提供额外的信息。 <>表示这是一个模板；

	myarray<> abc;  //完全用模板参数的缺省值
	myarray<int> def;  //提供一个非缺省值，只提供一个，另外一个用的是缺省值

	//b)函数模板：老标准只能为类模板提供默认模板参数，c++11新标准可以为函数模板提供默认参数；
	//(1)同时个模板参数和函数参数提供缺省值
	//(2)注意写法 F funcpoint = F()
	//(3)tc重载；
	testfunc(3, 4);

	return 0;
}

