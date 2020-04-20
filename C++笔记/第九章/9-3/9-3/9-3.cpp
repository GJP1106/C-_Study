// 9-3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <boost/type_index.hpp>
using namespace std;

template<typename T>  //T是类型模板参数，所以T是有类型的
//void myfunc(T& tmprv) {  //tmprv形参，形参也是有类型的，往往temprv形参的类型和T类型模板参数的类型 不一样
//void myfunc(const T& tmprv) {  //tmprv是一个常量引用
//void myfunc(T* tmprv) {  //tmprv是一个指针
//void myfunc(T&& tmprv) {
//void myfunc(T tmprv) {
void myfunc(T &tmprv) {
 	cout << "----------------------begin---------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;  //显示T类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl;
	cout << "----------------------end---------------" << endl;
}

void testFunc() {}

int main()
{

	//一、如何查看类型推断结果
	//推断(推导) auto。本节主要讲解模板类型推断的知识
	//我们为了学习类型推断相关知识，我们有必要知道编译器给我们推断出来的模板参数类型 以及
	// 普通参数类型是个什么样子。

	//老师的目的就是希望通过“查看编译器类型推断的结果”这个手段来让大家学习并掌握c++类型
	//推断的规则，也就是说最终老师要求大家掌握c++类型推断规则，而不是依赖什么手段去查看
	//编译器给我们推断出来的结果；
	//依赖boost库：如何利用boost库来吧编译器给我们推断出来的类型信息打印出来

	//二、理解模板类型推断
	//myfunc(100);  //T被推断为int，tmprv会被推断为const int &

	//(2.1)指针或者引用类型
	//如果tmprv类型是个指针或者引用，但不是个万能引用。
#if 0
	int i = 18;  //int
	const int j = i;  //const int
	const int &k = i;  //const int &

	myfunc(i);  //T = int, tmprv = int &
	myfunc(j);  //T = int const , tmprv = const int &
	myfunc(k);  //T = int const, tmprv = const int &
#endif
	//a)若实参是引用类型，则引用类型会被忽略掉，T不会被推导为引用类型。
	//b)当我们向引用类型的形参tmprv传入const类型实参时，形参就会成为const &；
	   //实参的const属性会成为类型模板参数T类型推导的组成部分，所以不用担心
	   //在myfunc中能够修改原来有const属性的实参。
#if 0
	int i = 18;  //int
	const int j = i;  //const int
	const int &k = i;  //const int &

	myfunc(i);  //T = int, tmprv = const int &
	myfunc(j);  //T = int, tmprv = const int &
	myfunc(k);  //T = int, tmprv = const int &
#endif
	//a)若实参是引用类型，则引用类型会被忽略掉，T不会被推导为引用类型。
	//b)对于有const属性的实参，在T中推导后，T中的const属性没有，因为模板函数myfunc的形参tmprv里边出现了const。
#if 0
	int i = 18;  //int
	const int j = i;  //const int
	const int &k = i;  //const int &
	const int *p = &i;
	myfunc(&i);   //T = int, tmprv = int *
	myfunc(p);    //T = const int, tmprv = cosnt int *
#endif
	//结论，如果tmprv中没有const，则实参中的const就会被带到T类型中。如果tmprv中有const，则T类型中不会带const；


	//(2.2)万能引用：如果tmprv类型是个万能引用：T&& 能接受左值也能接受右值，而且
	               //你传递进来左值/右值，万能引用的表现是不同的
#if 0
	int i = 18;  //int
	const int j = i;  //const int
	const int &k = i;  //const int &

	myfunc(i);   //i是左值，T = int &, tmprv = int &
	myfunc(j);   //j是左值， T = const int &, tmprv = const int &
	myfunc(k);   //k是个左值， T = const int &, tmprv = const int &
	myfunc(100);  //100是个右值，T = int, tmprv = int &&
#endif

	//(2.3)传值方式:如果tmprv类型不是指针，也不是引用，而是常规的传值方式传递
#if 0
	int i = 18;  //int
	const int j = i;  //const int
	const int &k = i;  //const int &

	myfunc(i);   //T = int, tmprv = int
	myfunc(j);   //T = int, tmprv =int  ,const 属性没传递进去，因为对方是新副本
	myfunc(k);   //T =int, tmprv = int  ，const 属性没传递进去，因为对方是新副本
#endif
	//现在我们传递指针进去
#if 0
	char mystr[] = "I love china";
	const char *const point = mystr;  //第一个从上图表示point指向的目标中的内容不能通过point来改变
	                                  //第二个const表示point指向一个内容后，不可以再指向其他内容。
	myfunc(point);   //T = const char *, tmprv = const char *
	                    //第二个const没有了，第一个const保留
#endif
	//总结：如果你传递的是const char *或者const char[]数组，那这个const会被保留

	//(2.4)数组做实参
	//数组名代表数组首地址。
	//const char mystr[] = "I love china";
	//myfunc(mystr);  //T = const char *, tmprv = const char *

	//将形参改为引用
#if 0
	const char mystr[] = "I love china";
	myfunc(mystr);  //T = const char [13], tmprv = const char(&)[13]
	//T被推导成了数组类型，而tmprv中(&)代表该数组的一个引用
#endif

	//(2.5)函数名做实参
	//函数名相当于函数首地址，可以赋给一个函数指针
	//传值时
	//myfunc(testFunc);  //T = void(*)(void), tmprv = void(*)(void)
	//传引用时
	myfunc(testFunc);   //T = void(void), tmprv = void (&)(void)

	//总结：
	//(1)推断中，引用类型实参的引用类型等于不存在
	//(2)万能引用，实参为左值或者右值，推断的结果不一样
	//(3)按值传递的实参，传递给形参时的const属性不起作用，则传递过去指针则另当别论
	//(4)数组或者函数类型在类型推断中被看做是指针，除非函数模板的形参是个引用。

	return 0;
}
