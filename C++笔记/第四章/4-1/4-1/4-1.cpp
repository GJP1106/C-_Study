// 4-1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#if 0
int funcadd(int i1, int i2) {
	int addhe = i1 + i2;
	return addhe;
}

double funcadd(double d1, double d2) {
	double addhe = d1 + d2;
	return addhe;
}
#endif

//函数模板
template<typename T>  //因为T前面有一个typename/class, 这表示T代表一个类型，是一个类型参数
T funcadd(T a, T b) {
	T addhe = a + b;
	return addhe;
}


template<int a, int b>
int funcaddv2()
{
	int addhe = a + b;
	return addhe;
}

template<typename T, int a, int b>
int funcaddv3(T c) {
	int addhe = (int)c + a + b;
	return addhe;
}

template<unsigned L1, unsigned L2>  //本例种仍旧没有类型参数。只有非类型模板参数
inline  //模板函数可以是inline的，inline的位置放在模板参数列表之后
int charscomp(const char(&p1)[L1], const char(&p2)[L2])
{
	return strcmp(p1, p2);
}



int main()
{
	//一、概述、
	//vector ：vector<int>

	//几句话
	//(1)所谓泛型编程，是以独立于任何特定类型的方式编写代码。使用泛型编程时，我们需要提供具体程序实例所操作的类习惯或者值。
	//(2)模板是泛型编程的基础。模板是创建类或者函数的蓝图或者公式。我们给这些蓝图或者公式提供足够的信息，让这些蓝图或者公式真正的
	//转变具体的类或者函数。这种转变发生在编译时。
	//(3)模板支持 将 类型作为参数的程序设计方式，从而实现了对泛型程序设计的直接支持。也就是说，c++模板机制允许在定义类，函数时将类型作为参数。

	//模板一般分为函数模板和类模板。本节课，主要讲解函数模板。

	//二、函数模板的定义
	//(1)模板定义是用template关键字开头的，后边跟<>,<>里边叫模板参数列表(模板实参)，如果模板参数列表里有多个参数，则用逗号分开。
	//<>里必须至少得有一个模板参数， 模板参数前面有个typename/class(不是用来定义类的)关键字
	//template<typename T>这种写法大家硬记
	//如果模板参数列表里边有多个模板参数，那你就要用多个typename/class：<typename T,typename Q>
	//(2)模板参数列表里边表示在函数定义中用到的“类型”或者“值”，也和函数参数列表类似
	//那我们用的时候，有的时候得指定 模板参数给他，指定的时候我们要用<>把模板实参包起来。有的时候 又不需要我们指定模板参数实参给他，
	//系统自己能够根据一些信息推断出来，后续我们会举例；
	//(3)funcadd()这个函数声明了一个名字为T的类型参数。这里注意，T实际是类型，这个T到底代表的是啥类型，编译器在编译的时候会根据针对funcadd函数模板的调用来确定。


	//三、函数模板的使用
	//函数模板调用和函数调用区别不大，调用的时候，编译器会根据你调用这个函数模板时的实参 去 推断模板参数列表里的参数(形参)的类型，
	//所以大家在这里一定要注意措辞：模板参数 有时候是推断出来的，推断的依据是什么？是根据你调用这个函数的时候的实参来推断的；
	  //当然有的时候，光凭借函数实参是推断不出来模板参数，这个时候我们就得用<>来主动的提供模板参数了；
#if 0
	int he = funcadd(3, 1);   //3,1系统认为是int，所以编译器能推断出来
	cout << he << endl;
	//编译器在推断出来这个模板的参数类型之后，编译器就为我们实例化了一个特定版本的函数。
	double he2 = funcadd(3.1f, 3.2f);
	cout << he2 << endl;
	//double he3 = funcadd(3f, 3.2f);  //报错，系统不知道改推断成int还是double
#endif


	//四、非类型模板参数
	//因为T前面有一个typename/class, 这表示T代表一个类型，是一个类型参数。
	//那么在模板参数列表里边，还可以定义非类型参数；非类型参数代表一个值。
	//既然非类型参数代表一个值，那么我们肯定不能用typename/class这种关键字来修饰这个值。
	  //我们当然要用以往学习过的传统类型名来指定非类型参数了。比如你非类型参数S如果是个整型，int s
	//template<typename T, int S>
	//T funcadd(T a, T b)
	//当模板被实例化时，这种非类型模板参数的值 或者是用户提供的，或者是编译器推断的，都有可能。
	  //但是，这些值必须都得是常量表达式，因为实例化这些模板是编译器在编译的时候来实例化的；

	/*template<int a, int b>
	int funcaddv2()*/
	int result = funcaddv2<12, 13>();   //显示的指定模板参数---在<>种提供额外的信息。
	cout << result << endl;
#if 0
	int a = 12;
	int result = funcaddv2<a, 13>();   //这不可以：非类型模板参数 值 必须是在编译的时候就能够确定的,因为实例化函数模板是在编译的时候干的事。
#endif

	/*template<typename T, int a, int b>
	int funcaddv3(T c)*/
	int addv3 = funcaddv3<int, 11, 13>(12);
	cout << addv3 << endl;

	int addv4 = funcaddv3<double, 11, 13>(12);  //系统会 以 我们用<>传递进去的类型为准，而不是用12来推断什么类型
	cout << addv4 << endl;


	//template<unsigned L1, unsigned L2>  //本例种仍旧没有类型参数。只有非类型模板参数
	//int charscomp(const char(&p1)[L1], const char(&p2)[L2])
	int result1 = charscomp("test2", "test");  //没有提供非类型模板参数，系统会根据test2的长度6个，test长度5个，取代L1，L2
	cout << result1 << endl;

	//模板定义并不会导致编译器生成代码。只有在我们调用这个函数模板时，使编译器为我们实例化了一个特定版本的函数之后，
	  //编译器才会生成代码
	//编译器生成代码的时候，需要能够找到函数的函数体，所以，函数模板的定义通常都是在.h文件中







	return 0;
}

