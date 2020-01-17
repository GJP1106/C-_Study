// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
/*
第三章
**/


#include "stdafx.h"
#include "Time.h"
#include <iostream>
using namespace std;

void func1(Time myt)
{

}

int main()
{
#if 0
	Time myTime; //类对象
	myTime.initTime(11, 14, 15);   //这就是调用成员函数(使用成员函数)
	cout << myTime.Hour << endl;
	cout << myTime.Minute << endl;
	cout << myTime.Second << endl;
	
#endif

	//一、构造函数:在类中，有一种特殊的成员函数，它的名字和类名相同，我们在创建类的对象的时候，
	              //这个特殊的成员函数就会被系统自动调用，这个成员函数，就叫“构造函数”；
	              //因为构造函数会被系统自动调用，所以我们可以简单的理解成:构造函数的目的就是初始化类的对象的数据成员。
	//(1)构造函数没有返回值。这也是构造函数的特殊之处。


	//(2)不可以手动调用构造函数，否则编译就会报错。

	//(3)正常情况下，构造函数应该被声明为public，因为我们创建一个对象时系统要替我们调用构造函数，这说明构造函数它是一个public函数，才能够被系统(外界)调用。
	     //因为类缺省的成员是私有成员，所以我们必须说明构造函数是一个public函数，否则就无法直接创建该类的对象。
	//(4)构造函数中如果有多个参数，则我们创建对象的时候也要带上这些参数。
#if 0
	Time myTime = Time(12, 13, 14);  //创建对象
	Time myTime2(12, 11, 11);
	Time myTime3 = Time{ 12, 13, 14 };
	Time myTime4{ 12, 13, 15 };
	Time myTime5 = { 12, 14, 15 };
#endif

	//二:多个构造函数:一个类中可以有多个构造函数，就可以为类的对象的创建提供多种初始化方法。但是多个构造函数之间总要有点不同的地方。
#if 0
	Time myTime10 = Time();  //创建对象
	//Time myTime12();
	Time myTime11;
	Time myTime13 = Time{};
	Time myTime14{};
	Time myTime15 = {};

	//对象拷贝
	Time myTime20; //可以调用构造函数
	//如下4个对象并没有调用传统意义上的构造函数，这个我们后续会讲，他们调用的实际上是拷贝构造函数。
	Time myTime22 = myTime20;
	Time myTime23(myTime20);
	Time myTime24{ myTime20 };
	Time myTime25 = { myTime20 };
#endif
	//三、默认构造函数
	//规定:
	//(1)默认值只能放在函数声明中，除非该函数没有函数声明。
	//(2)在具有多个参数的函数中指定默认值时，默认参数都必须出现在不默认参数的右边，
	    //一旦某个参数开始指定默认值，它右边的所有参数必须有默认值。
#if 0
	Time myTime30 = Time(12, 13); //可以调用构造函数
	Time myTime32(12, 13);
	Time myTime33 = Time{12, 13};
	Time myTime34{12, 13};
	Time myTime35 = {12, 13};
#endif


	//四、隐式转换和explicit
#if 0
	//编译系统，在私下干了很多我们不知道的事
	Time myTime40 = 14;  //编译系统肯定有个行为，把14这个数字转换成了一个Time类型，调用了单参数的构造函数
	Time myTime41 = (12, 13, 14, 15, 16);   //调用了单参数的构造函数
	func1(16); //16被转换成了一个临时的Time对象导致func1的调用能够成功。调用了单参数的构造函数

	Time myTime100 = { 16 };  //这个写法咱们认为正常，带一个参数16，可以让系统明确的知道调用哪个构造函数
	Time myTime101 = 16;   //含糊不清的写法，就存在临时对象隐式转换。
	func1(16);   //也是含糊不清的写法，存在临时对象或者隐式转换的问题
	//是否可以强制系统，明确要求构造函数不能做隐式类型转换呢？
	//可以，如果构造函数声明中带有explicit，则这个构造函数只能用于初始化和显示类型转换；
#endif
#if 0
	//在头文件的三个参数的构造函数声明时添加了explicit
	Time myTime = Time(12, 13, 14);  //创建对象
	Time myTime2(12, 11, 11);
	Time myTime3 = Time{ 12, 13, 14 };
	Time myTime4{ 12, 13, 15 };
	//Time myTime5 = { 12, 14, 15 };   //隐式类型转换。
#endif
#if 0
	//在头文件的一个参数的构造函数声明时添加了explicit，以下方式都不可以使用
	Time myTime100 = { 16 };
	Time myTime101 = 16;
	func1(16);
//#else if
	//修改后
	Time myTime100 = Time{ 16 };
	Time myTime101 = Time(16);
	func1(Time(16));
#endif
	//对于单参数的构造函数，一般都声明为explicit，除非你有特别原因。

	//五、构造函数初始化列表
	//(1)显得专业、高大上。
	//(2)效率上更高。
	Time myTime = Time(12, 13, 53);

	return 0;
}

