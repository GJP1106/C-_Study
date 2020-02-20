// 4-6.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

template<typename T,typename U>
struct TC  //泛化的TC类模板
{
	TC() {
		cout << "泛化版本构造函数" << endl;
	}
	void functest()
	{
		cout << "泛化版本" << endl;
	}
};

//当T和U这两个类型模板参数都为int类型时，我们希望做一个特化版本
//全特化：就是所有类型模板参数(这里T和U)，都得用具体的类型代表
template<> //全特化：所有类型模板参数都用具体类型代表，所以这里的template后边的<>里就为空
struct TC<int, int>  //上边的T绑定到这里的第一个int，上边的U绑定到这里的第二个int
{
	TC() {
		cout << "int int版本构造函数" << endl;
	}
	//在这里可以对该特化版本做单独处理
	void functest() {
		cout << "int int的特化版本" << endl;
	}
};
template<>
struct TC<double, int>  //上边的T绑定到这里的第一个double，上边的U绑定到这里的第二个int
{
	TC() {
		cout << "double int版本构造函数" << endl;
	}
	//在这里可以对该特化版本做单独处理
	void functest() {
		cout << "double int的特化版本" << endl;
	}
};
template<>  //全特化
void TC<double, double>::functest()
{
	cout << "double double的functest()特化版本" << endl;
}

//偏特化的泛化版本
template <typename T, typename U, typename W>  //带三个类型模板参数
struct TD {
	void functest()
	{
		cout << "三个参数的泛化版本" << endl;
	}
};
//从参数数量上进行偏特化，我们现在绑2个类型模板参数，留一个类型模板参数。
template<typename U> //因为另外连两个被我绑定到具体类型，所以这里只剩下一个U类型模板参数了。
struct TD<int, U, double>   //大家注意，这里可以跳着来
{
	void functest()
	{
		cout << "偏特化int,U,double版本" << endl;
	}
};

//从模板参数范围上泛化版本
template <typename T>
struct TE
{
	void functest() {
		cout << "模板参数范围上泛化版本" << endl;
	}
};
//模板参数范围上特化版本
template <typename T>
struct TE<const T>   //const的特化版本
{
	void functest() {
		cout << "const的特化版本" << endl;
	}
};
template <typename T>
struct TE<T *>   //T*的特化版本
{
	void functest() {
		cout << "T*的特化版本" << endl;
	}
};

template <typename T>
struct TE<T &>   //T&左值引用的特化版本
{
	void functest() {
		cout << "T&左值引用的特化版本" << endl;
	}
};

template <typename T>
struct TE<T &&>   //T&&右值引用的特化版本
{
	void functest() {
		cout << "T&&右值引用的特化版本" << endl;
	}
};

//函数模板泛化
template <typename T,typename U>
void tfunc(T &tmp1, U &tmp2) {
	cout << "tfunc泛化版本" << endl;
	cout << tmp1 << endl;
	cout << tmp2 << endl;
}

//函数模板全特化版本
template <>
void tfunc(int &tmp1, double &tmp2) {
	cout << "tfunc全特化版本" << endl;
	cout << tmp1 << endl;
	cout << tmp2 << endl;
}



int main()
{
	//特化： 相反 泛化：模板，可以随便指定类型。
	//特化：对特殊的类型(类型模板参数)进行特殊的对待，给它开后门，给他写适合它的专用代码
	//一、类模板特化
	//(1.1)类模板全特化
	 //a)常规全特化
	     //必须要有泛化版本才能存在特化版本，只要涉及特化，一定先存在泛化
	//特化版本代码编译器会优先选择
#if 0
	TC<char, int> tchar;
	tchar.functest();

	TC<int, int> tint;
	tint.functest();

	TC<double, int> tdouble;
	tdouble.functest();
	//这种特化版本可以任意多
#endif


	//b)特化成员函数而不是模板
#if 0
	TC<double, double> tdb;  //泛化版本对象，调用的是泛化版本的构造函数
	tdb.functest();  //因为我们特化了double，double类型的functest函数，所以这里调用的是特化的functest()函数。
#endif

	//(1.2)类模板偏特化(局部特化)
	//偏特化从两方面说起:一个是从模板参数数量上 一个是从模板参数范围上
	//a)从模板参数数量上
#if 0
	TD<double, int, double> td;
	td.functest();
	TD<int, int, double> td1;
	td1.functest();
#endif
	//b)从模板参数范围上:int  ->  const int(比int小)
	                     //原来T，现在T*(从任意类型T缩小为指针类型T*)
	                     //原来T，现在T&左值引用，或者现在是T&&(右值引用)，都叫范围缩小。
#if 0
	TE<double> te;
	te.functest();   //泛化版本

	TE<double *> te1;
	te1.functest();  //T*的特化版本

	TE<const double *> te2;
	te2.functest();  //T*的特化版本

	TE<const double> te3;
	te3.functest();   //const的特化版本

	TE<int &> te4;
	te4.functest();  //T&左值引用的特化版本
#endif
	//局部特化，转化完了之后它本质上还是模板。全特化，转化完了等于一个具体的类了

	//二、函数模板全特化
	//(2.1)函数模板全特化
#if 0
	const char *p = "I Lova China";
	int i = 12;
	tfunc(p, i);   //T = const char *, tmp1 = const char * &
	int a = 1;
	double b = 3.5;
	tfunc(a, b);
#endif
	//全特化函数模板实际上等价于实例化一个函数模板，并不是等价于一个函数重载。
	//void tfunc<int,double>(int &,double &)  //全特化，等价于实例化一个函数模板
	//void tfunc(int &tmp1,double &tmp2)  //重载函数应该长这样

	//编译器选择最最合适:普通优先，特化版本，泛化版本
	//如果你传递个字符串给函数模板
	//函数模板的特化版本中，如果右 数组类型模板参数，指针类型模板参数。
	//编译器会认为 数组类型模板参数 比指针类型模板参数更合适。所以编译器会为你选择数组类型的模板参数的特化版本

	//(2.2)函数模板偏特化
	 //函数模板不能偏特化


	//三、模板特化版本 放置位置建议
	//模板定义、实现都放在一个.h中
	//模板的特化版本和模板的泛化版本都应该放在同一个.h文件中。
	//.h文件中前边放泛化版本，后边放特化版本




	return 0;
}

