// 9-10.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <initializer_list>
#include <stdarg.h>
using namespace std;

void printvalue(initializer_list<string> tmpstr) {
	for (auto beg = tmpstr.begin(); beg != tmpstr.end(); ++beg) {
		cout << (*beg).c_str() << endl;
	}
	cout << tmpstr.size() << endl;   //用size方法来打印列表中元素的数量
}

class CT {
public:
	CT(const initializer_list<int> &tmpvalue) {
		int i;
		i = 100;
	}
};

//带...的可变参数函数，我们需要用到几个宏
double average(int num, ...) {
	va_list valist;   //创建一个va_list类型的变量

	double sum = 0;
	va_start(valist, num);  //使valist指向起始的参数
	for (int i = 0; i < num; i++) {
		//遍历参数
		sum = sum + va_arg(valist, int);  //参数2说明返回的类型为int
	}
	va_end(valist);  //释放va_list
	return sum;
}

void funcTest(const char *msg, ...) {
	va_list valist;
	int cags = atoi(msg);  //这个就是拿到可变参数数量，这个数量我们后续要用于获取可变参数；
	va_start(valist, msg); //使valist指向起始的参数
	int paramcout = 0;
	while (paramcout < cags) {
		char *p; //这块我们假定给的可变参数都是字符串；如果是printf你就要根据%d、%s来分析可变参数类型。
		p = va_arg(valist, char *);
		printf("第%d个参数是:%s\n", paramcout, p);
		paramcout++;

	}
	va_end(valist);
}

int main()
{
    //一、可变参数函数
	//这种能够接收非固定个数参数的函数是可变参数函数；
	//initializer_list标准库类型，该类型能够使用的前提条件是 所有的实参类型相同；

	//二、initializer_list(初始化列表)
	//如果一个函数，它的实参数量不可预知的，但是所有参数的类型相同，我们就可以使用这个initlializer_list类型的形参来接收；
	//initializer_list 是c++11里提供的新类型，也是 一个类模板，vector；
	//我们把initializer_list理解成某中类型值得数组，这个类模板里指定的类型模板参数就是这个数组里保存的数据的类型。
#if 0
	initializer_list<int> myarray; //数组，元素类型是int,空列表(空数组);
	initializer_list<int> myarray2 = { 12,14,16,18,20,11 };  //数组，元素是int类型
#endif

	//注意initializer_list队形中的元素，永远是常量值，不能被改变
	//(2.1)begin(),end()遍历，size()获取元素的个数
	//printvalue({"aa","bb"});   //t若要往initializer_list形参传递值的一个序列，则必须要把这个序列放在{}里括起来作为一个整体
	//其实c++11将使用大括号{}的初始化{初始化列表}作为一种比较通用的初始化方式，可用于很多的类型，大家可以注意观察和收集；
	//函数initializer_list形参的函数也可以包含其他形参；

	//(2.2)拷贝和赋值
	//拷贝、赋值一个initializer_list、不会拷贝列表中的元素。原来对象和拷贝或者赋值出来的对象共享表中的元素。
#if 0
	initializer_list<string> myarray3 = { "aa","bb","c" };
	initializer_list<string> myarray4(myarray3);
	initializer_list<string> myarray5;
	myarray5 = myarray4;
#endif

	//(2.3)初始化列表做构造函数参数
#if 0
	CT ct1 = { 10,20,30,40 };   //隐式类型转换
	CT ct1{ 10,20,30,40 };  //显式的
#endif

	//三、省略号形参(...)
	//省略号形参一般无法正确处理类类型对象；能正确处理的int，char *

	//这种省略形参式的可变参数函数，虽然参数数量不固定，但是函数的所有参数式存储在线性连续的栈空间中的，
	//而且带。。。的可变参数函数必须至少要有一个普通参数，我们就可以通过这个普通参数来寻找后续的所有可变参数的类型以及值。
	//cout << average(3, 100, 200, 300) << endl;
	funcTest("3", "aa", "bb", "cc");

	//注意：
	//a)至少有一个有效的形参，形参不能是完全的
	//b)...形参只能出现在形参列表最后一个位置。
	//c)...之前的,可以省略
	//d)如果有多个普通函数，那么va_start(valist,msg),第二个参数必须绑...之前的那个参数
	//e)一般这些可变参数类型是数值型或者字符串型还能正常处理，其他类类型一般都不能正常处理，所以...用的场合并不多。
	//f)不建议大家在c++中使用...但是遇到了这种写法能看懂

	return 0;
}

