// 4-5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <map>

using namespace std;

//C++98的方法
//希望定义一个类型，前边这部分固定不变，是std::map<std::string, 类型自己指定>
template <typename st>
struct map_s {  //定义了一个结构/类，只是结构的成员缺省都是public
	typedef std::map<std::string, st> type;  //定义了一个类型
};

//c++11的方法
template<typename T>
using str_map_t = std::map<std::string, T>;  //str_map_t 是类型别名
                                             //using用来给一个“类型模板”起名字(别名)用的
template <typename T>
using myfunc_M = int(*)(T, T);   //定义类型模板， 是个函数指针模板

int RealFunc(int i, int j) {
	return 1;
}

template <typename T1,typename T2,typename T3>
T1 sum(T2 i, T3 j)
{
	T1 result = i + j;
	return result;
}

int main()
{
	//一、using定义模板别名
#if 0
	//typedef ：一般用来定义类型别名
	typedef unsigned int uint_t;  //相当于给unsigned int类型起了要给别名uint_t
	uint_t abc;
	//std::map<std::string, int>
	typedef std::map<std::string, int> map_s_i;
	map_s_i mymap;
	mymap.insert({ "first", 1 });

	typedef std::map<std::string, std::string> map_s_s;
	map_s_s mymap2;
	mymap2.insert({"first","first"});
#endif

#if 0
	//希望定义一个类型，前边这部分固定不变，是std::map<std::string, 类型自己指定>
	template <typename st>
	struct map_s {  //定义了一个结构/类，只是结构的成员缺省都是public
		typedef std::map<std::string, st> type;  //定义了一个类型
	};
#endif
#if 0
	map_s<int>::type map1;   //等价于std::map<std::string, int>
	map1.insert({ "first", 1 });
	//我们为了实现这种比较通用的以string类型为key，以任意类型为value(值)的map容器，我们不得不自己写一个类来达到这个目的，实现
	//手段比较猥琐。

	str_map_t<int> map2;
	map2.insert({ "first", 1 });
#endif
	//using在用于定义类型(定义类型模板)的时候，是包含了typedef的所有功能的。
	/*typedef unsigned int uint_t;
	using uint_t = unsigned int;

	typedef std::map<std::string, int> map_s_i;    //typedef定义类型的方法感觉像 定义一个变量:类型名 变量名
	using map_s_i = std::map<std::string, int>;*/

	//typedef int(*FuncType)(int, int); //用typedef来定义函数指针
	//using FuncType = int(*)(int, int); //using定义类型的方法感觉像赋值
#if 0
	myfunc_M<int> pointFunc;   //myfunc_M<int> 是一个函数指针类型，是一个类型名
	                           //pointFunc是一个函数指针
	pointFunc = RealFunc;   //把函数地址赋给函数指针变量
	cout << pointFunc(1, 6) << endl;
#endif

	//总结：
	//using中使用这种模板，既不是类模板，也不是函数模板，我们可以看成是一个新的模板类型:类型模板(模板名)

	//二、显示指定模板参数
	auto result = sum<double,double,double>(2000000000, 2000000000);  //手工指定的类型优先
	cout << result << endl;

	return 0;
}

