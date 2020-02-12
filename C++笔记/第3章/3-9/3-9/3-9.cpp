// 3-9.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Human.h"
#include "Men.h"
#include "Women.h"
#include "func.h"
#include "A.h"
#include "C.h"
using namespace std;

//class A {
//private:
//	int data;
//
//	friend class C; //这就是友元类的声明，虽然此时类C没有定义，但是系统没报错
//};
//class C {
//public:
//	void callCAF(int x, A &a) {
//		a.data = x;
//		cout << a.data << endl;
//	}
//	void callCAF1(A &a) {
//		a.data;
//	}
//};

int main()
{
	//friend

	//一、友元函数、这是个函数
	//public protected private
	//只要让函数func成为类Men的友元函数，那么func这个函数就能够访问类Men的所有成员(成员变量，成员函数)，private,protected public

	/*Men men;
	func(men);*/

	//总结：友元函数func():是个函数，通过声明为某个类Men的友元函数，他就能访问这个类(Men)的所有成员，包括public protected private

	//二、友元类：类 可以把其他的类定义成友元类。如果 你是 我的 友元类，那么你就可以在你的成员函数中访问我的所有成员，包括public protected private
	//我们修改类A， 让类C成为类A的朋友(也就是让类C成为类A的友元类)

	/*A a;
	C c;
	c.callCAF(3, a);*/
	//注意：每个类都负责控制自己的友元类和友元函数，所以
	//(1)友元关系不能被继承
	//(2)友元关系是单向的，比如上边类C是类A的友元类，但这并不表示类A是类C的友元类；
	//(3)友元关系没有传递性，比如类B是类A的友元类，类C是类B的友元类，这并不表示类C是类A的友元类

	//三、友元成员函数
	//写这种友元成员函数，必须要注意代码组织结构，因为这里边有声明和定义这种依赖关系在里边。
	A a;
	C c;
	c.callCAF(3, a);

	//总结：friend
	//优点:允许在待定情况下某些非成员函数访问类的protected，private成员，从而提出友元这么一个概念，使访问protected private成员更灵活
	//缺点:这也就破坏了类的封装性，降低了类的可靠性和可维护性。


	return 0;
}

