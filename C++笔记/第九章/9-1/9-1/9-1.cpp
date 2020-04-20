// 9-1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <map>
#include <functional>
using namespace std;

//void func(int i) {
//
//}
//如果值 < 0，那么就返回0，否则返回实际的值
class biggerthanzero {
public:
	/*biggerthanzero(int) {
		cout << "biggerthanzero构造函数执行了" << endl;
	}*/

	//重载圆括号(函数调用运算符)
	int operator()(int value) const {
		if (value < 0) return 0;
		return value;
	}
};
//普通函数:打印value值并原样返回
 int echovalue(int value) { //调用参数和返回值与biggerthanzero中的operator()相同
	cout << value << endl;
	return value;
}


int main()
{
	//一、学习c++体会，总结
	//(1)对语言本身的学习
	//(2)大量练习
	//(3)开始阅读优秀的人写的优秀代码
	//func(5);
	//圆括号()就是函数调用的明显标记，()有一个称呼叫做“函数调用运算符”;
	//如果我在类中重载了函数的调用运算符()，那么我就可以像使用函数一样使用该类的对象了。对象(实参)
	//如何使用函数调用运算符呢？
	//(a)定义一个该类的对象
	//(b)像函数调用一样使用该对象，也就是()增加实参列表。
	//int i = 20;
	//biggerthanzero obj;  //含有函数调用运算符的对象。
	//int result = obj(i);  //等价于调用obj.operator()(i);

	//biggerthanzero obj(1);  //这是对象定义并初始化，所以调用的是构造函数
	//obj(2);  //这个才是调用对象obj的()圆括号。
	//结论：只要这个对象所属的类重载了()"函数调用运算符"，
	//那么这个类对象就变成可调用的了，而且可以调用多个版本的(),只要参数数量和类型不同

	//二、不同调用对象的相同调用形式
	//函数echovalue和类biggerthanzero的重载(),这两个东西，调用参数和返回值相同，就叫做“调用形式相同”
	//一种调用形式 对应 一个函数类型：int(int);
	//函数类型:int(int) //标识接受一个int参数，返回一个int值

	//引入概念叫“可调用对象”，如下两个都是可调用对象。
	//a)echovalue函数
	//b)重载了函数调用运算符的biggerthanzero类对象。

	//把这些可调用对象的指针保存起来，目的是方便我们随时调用这些“可调用对象”，
	//这些指针感觉 我们c语言中的函数指针。
	//int(*p)(int x);//p就是定义的指针变量
	//p = max;  //函数max的入口地址给p；
	//int result = (*p)(5);  //调用函数max ==max(5);

	//map,vector,map里的每一项不是一个数据，是两个数据，一个叫“键”，一个叫“值”。

	//map<string, int(*)(int x)> myoper;
	//myoper.insert({ "ev",echovalue });  //用insert方法往这个容器中增加了一项键值对

	biggerthanzero obj;  //含有函数调用运算符的对象
	/*myoper.insert({ "bt",biggerthanzero });  //不可以
	myoper.insert({ "bt",obj });*/  //不可以

	//三、标准库function类型介绍
	//function 类模板，要提供模板参数来表示该function类型能够表示的“对象的调用形式”
	//function<int(int)> ;  //这就叫 声明了一个function()类型，用来表示一个可调用对象，
	//它所代表的这个可调用对象是:接受一个int参数，返回的也是一个int类型。
	function<int(int)> f1 = echovalue;  //函数指针
	function<int(int)> f2 = obj;   //类对象，因为类中有()重载。
	function<int(int)> f3 = biggerthanzero();  //用类名生成一个对象，也可以，因为类中有()重载
	//调用一下
	f1(5);
	cout << f2(3) << endl;
	cout << f3(-5) << endl;

	map<string, function<int(int)>> myoper = { {"ev",echovalue},{"bt",obj},{"bt2",biggerthanzero()} };

	myoper["ev"](12);  //就是调用echovalue函数
	cout << myoper["bt"](3) << endl;
	cout << myoper["bt2"](-13) << endl;

	//如果函数有重载，就无法放到function<>类型的对象中。
	//我们可以通过定义函数指针来解决
	int(*fp)(int) = echovalue;   //定义函数指针，不会产生二义性，因为函数指针里有对应得参数类型和返回值类型
	function<int(int)> f1 = fp;  //直接塞进去函数指针而不是函数名echovalue。

	//总结：



	return 0;
}
