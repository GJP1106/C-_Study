// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;


int main()
{
	//一、隐式类型转换:系统自动进行，不需要程序开发人员介入
	int m = 3 + 45.6;  //48.600000000,把小数部分截掉，也属于隐式类型转换的一种行为。
	double n = 3 + 45.6;

	//二、显示类型转换(强制类型转换)
	//int k = 5 % 3.2; //语法错
	//int k = 5 % (int)3.2;  //ok,c语言风格的强制类型转换
	//int k = 5 % int(3.2);   //函数风格的强制类型转换

	//C++强制类型转换分为4种：我们现在写程序应该用C++风格的强制类型转换。
	//这4种强制类型转换，分别用于不同的目的，每一个都有一个不同的名字。提供4种类型的目的:提供更丰富的含义和功能，更好的类型检查机制，方便代码的维护
	//a)static_cast
	//b)dynamic_cast
	//c)const_cast
	//d)reinterpret_cast
	//这四个强制类型转换都被称呼为"命名的强制类型转换(因为他们每一个都有一个名字并且名字各不相同)"
	//通用形式:
	//强制类型转换名<type>
	//强制类型转换名:是上边的a、b、c、d四个名字之一。
	//type：抓换的目标类型
	//express：你要转换的值(你要转换的是谁)
	//(2.1) static_cast : 静态转换，大家就理解成“正常转换”，编译的时候就会进行类型转换的检查。
	                      //代码中要保证转换的安全性和正确性，static_cast含义跟c语言中的强制类型转换这种感觉差不多。
	                      //c风格的强制类型转换，以及编译器能够进行的隐式类型转换，都可以用static_cast类显式完成

	//可用于：
	//a）相关类型转换，比如整型和实型之间的转换：
#if 0
	double f = 100.34f;
	int i = (int)f;  //c风格的
	int i2 = static_cast<int>(f); //c++风格的类型转换
#endif
	//b)后续学习类的时候子类转成父类类型(继承关系)，也能用这个static_cast转；
	//class A {};
	//class B : public A{};
	//B b;
	//A a = static_cast<A>(b);  //把子类转成父类的对象

	//A a;
	//B b = static_cast<B>(a);  //把父类转成子类，这种方式不行

	//c)void *与其他类型指针之间的转换，void * :无类型指针：可以指向任何指针类型(万能指针)；
#if 0
	int i = 10;
	int *p = &i;
	void *q = static_cast<void *>(p);   //int *转成void *
	int *db = static_cast<int *>(q);
#endif

	//不可用于：
	//a)一般不能用于指针类型之间的转换比如int *转double *, float *转double *等等。
#if 0
	double f = 100.0f;
	double *pf = &f;
	//int *i = static_cast<int *>(pf); //不可以
	//float *fd = static_cast<float *>(pf); //不可以
#endif

	//(2.2)dynamic_cast:主要应用于运行时类型识别和检查，主要用来父类型和子类型之间转换用的（父类型指针指向子类对象，然后用dynamic_cast把父指针类型往子指针类型转）
	//第三章10节详细讲解dynamic_cast,这里不多说。

	//(2.3)const_cast:去除指针或引用的const属性，该转换能够将const性质转换掉。
	                  //编译时就会进行类型转换
#if 0
	const int ai = 90;
	//int ai2 = const_cast<int>(ai);   //ai不是指针也不是引用，不能转
	const int *pai = &ai;
	int *pai2 = const_cast<int *>(pai);    //语法正确
	*pai2 = 120;   //这种写值行为，是属于一种未定义行为。大家不要这么干；
	cout << ai << endl;    //打印出来为90，是不是很奇怪？
	cout << *pai << endl;   //打印出来为120
#endif
#if 0
	//C语言风格
	const int ai = 90;
	int *pai = (int *)&ai;
	*pai = 120;  //未定义行为
	cout << ai << endl;
	cout << *pai << endl;
#endif

	//(2.4)reinterpret_cast:编译的时候就会进行类型转换的检查
	//reinterpret :重新编译。(将操作数内容解释为另一种不同的类型【能把操作数的类型都转了】)。
	//处理无关类型的转换。也就是两个转换类型之间没有什么关系。就等于可以乱转，自由转，怎么转都行，很随意。
	//常用于如下两种转换：
	//a)将一个整型(地址)转换成指针，一种类型指针转换成另一种类型指针，按照转换后的内容重新解释内存中的内容；
	//b)也可以从一个指针转换成一个整型。
#if 0
	int i = 10;
	int *pi = &i;
	int *p2 = reinterpret_cast<int *>(&i);
	char *pc = reinterpret_cast<char *>(pi);
#endif

#if 0
	int i = 10;
	int *pi = &i;
	void *pvoid = reinterpret_cast<void *>(pi);
	//....
	int *pi2 = reinterpret_cast<int *>(pvoid);

	//被认为是危险的类型转换,随便转，怎么搞都行，编译器都不报错。

#endif

	int iv1 = 100;
	long long lvl = 8898899400; //8字节的。 十六进制:2 126A 6DC8
	int *piv1 = (int *)iv1; //c语言风格； piv1 = 0x00000064 {???}
	int *piv2 = reinterpret_cast<int *>(iv1); //piv2 = 0x00000064 {???}
	
	piv2 = reinterpret_cast<int *>(lvl);  //piv2 = 0x126a6dc8 {???}  把前边的2丢了，因为piv2是4字节
	long long ne = reinterpret_cast<long long>(piv2);  //ne = 308964808  指针类型转整型   十六进制:126A 6DC8


	//总结:
	//(1)强制类型转换，不建议使用，强制类型转换能够抑制编译器报错。
	//(2)学习目的:认识这些类型转换符，方便大家阅读别人的代码。
	//(3)资料说:reinterpret_cast危险。使用const_cast意味着设计缺陷。
	//(4)如果实在需要使用类型转换，不再使用c语言风格的类型转换了，而用c++风格的类型转换。
	//(5)一般static_cast和reinterpret_cast 就能够很好的取代c语言风格的类型转换。

	//reinterpret_cast只要好好用，合乎规则的使用，不要乱用，其实reinterpret_cast很好用。




	return 0;
}

