// 3-14.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Human.h"
#include "Men.h"
#include "Women.h"
#include <vector>
using namespace std;

class B {
public:
	B() :m_b(100) {
		cout << "类B的构造函数执行了" << endl;
	}
	B(const B& tmp) :m_b(tmp.m_b) {
		cout << "类B的拷贝构造函数执行了" << endl;
	}
	virtual ~B() {
		cout << "类B的析构函数执行了" << endl;
	}
	int m_b;
};
class A {
public:
	//默认构造函数
	A() :m_pb(new B()) {  //这里会调用类B的构造函数
		cout << "类A的构造函数执行了" << endl;
	}
	//拷贝构造函数：
	A(const A& tmpa) :m_pb(new B(*(tmpa.m_pb))) {
		cout << "类A的拷贝构造函数执行了" << endl;
	}
	//移动构造函数
	//noexcept:通知标准库我们这个移动构造函数不抛出任何异常(提高编译器工作效率)
	A(A &&tmpa) :m_pb(tmpa.m_pb) {  //原来对象a指向的内存m_pb,我直接就让这个临时对象指向这段内存。
		tmpa.m_pb = nullptr;
		cout << "类A的移动构造函数执行了" << endl;
	}
	//拷贝赋值运算符
	A& operator=(const A& src) {
		if (this == &src) {
			return *this;
		}
		delete m_pb; //把自己这块内存干掉
		m_pb = new B(*(src.m_pb)); //重新分配一块内存
		cout << "类A的拷贝赋值运算符执行了" << endl;
		return *this;
	}

	//移动赋值运算符
	A &operator=(A && src) {
		if (this == &src) {
			return *this;
		}
		delete m_pb; //把自己这块内存干掉
		m_pb = src.m_pb; //对方的内存直接拿过来(直接指过来)
		src.m_pb = nullptr; //斩断掉(也就是对方和那个内存的关联我要斩断)
		cout << "类A的移动赋值运算符执行了" << endl;
		return *this;
	}

	virtual ~A() {
		delete m_pb;
		cout << "类A的析构函数执行了" << endl;
	}
private:
	B *m_pb;
};

static A getA() {
	A a;
	return a; //临时对象,调用拷贝构造函数
	          //如果类A有移动构造函数，那么会调用移动构造函数：把a对象的数据移动给了 临时对象
}


struct TC {
	int i;  //内置类型可以移动
	std::string s; //string类型定义了自己的移动操作
};

int main()
{
	//一、对象移动的概念
	//对象拷贝，c++11“对象移动”

	//二、移动构造函数和移动赋值运算符概念
	//c++11 std::move 解决效率问题
	//移动构造函数：c++11 进一步提高程序效率
	//vector:
	//说明：
	//（1）A移动给B，那么A对象我们就不能再使用了。
	//(2)移动：并不是把内存中的数据从一个地址 倒腾到另外一个地址。知识所有者变更。
	//....
	//拷贝构造函数:Time::Time(const Time &tmptime) {...}  //const 左值引用
	//移动构造函数:Time::Time(const Time &&tmptime) {...}  //右值引用 &&

	//移动构造函数 和移动赋值运算符应该完成的功能
	//(1)完成必要的内存移动，斩断原对象和内存的关系。
	//(2)确保移动后源对象处于一种“即便被销毁也没有什么问题”的一种状态。 B <- A。确保不再使用A，而是应该去使用B。

	//三、移动构造函数的演示
#if 0
	B *pb = new B(); //new 调用类B的构造函数
	pb->m_b = 19;
	B *pb2 = new B(*pb); //这种给参数的new方法会调用B类的拷贝构造函数

	delete pb;
	delete pb2;
#endif

#if 0
	A a = getA();
	//调用了一次 构造函数， 1次拷贝构造函数，2次析构函数从而整个程序执行完毕
	//增加移动构造函数后：调用1次构造函数，1次移动构造函数，2次析构函数，从而整个程序执行完毕
	//A a1(a); //会调用拷贝构造函数
	//A a2(std::move(a)); //调用移动构造函数
	A &&a3(std::move(a)); //这里没有建立新对象，根本不会调用什么移动构造函数
	                      //效果等同于把对象a有了一个新的别名叫a3，后续建议用a3来操作，不要再使用a。
	//A &&c = getA();  //从getA()返回的临时对象被c接管了。1个构造函数，1个移动构造函数， 1个析构函数
#endif

#if 0
	//四、移动赋值运算符演示
	A a = getA(); //1个构造函数，1个移动构造函数，1个析构函数
	A a2; //1个构造函数
	a2 = std::move(a); //调用移动赋值运算符。
#endif

	//五、合成的移动操作
	//某些条件下，编译器能合成移动构造函数，移动赋值运算符
	//a)有自己的拷贝构造函数，自己的拷贝赋值运算符，或者自己的析构，那么编译器就不会为它合成 移动构造函数和移动赋值运算符。
	 //所以 有一些类是没有移动构造函数和移动赋值运算符的；
	//b)如果我们没有自己的移动构造函数和移动赋值运算符，那么系统会调用我们自己写的拷贝构造函数和拷贝赋值运算符来代替。
	//c)只有一个类没定义任何自己版本的拷贝构造成员(没有拷贝构造函数也没有拷贝赋值运算符)，且类的每个非静态成员都可以移动时，编译器才会为该类合成移动构造函数或者移动赋值运算符。
	//什么叫成员可以移动呢？
	   //(1)内置类型是可以移动的
	   //(2)类类型的成员，则这个类要有对应的移动操作相关的函数，就可以移动。
	       //此时编译器就能够为我们合成移动构造函数和移动赋值运算符；
	TC a;
	a.i = 100;
	a.s = "I Love china";
	const char *p = a.s.c_str();

	TC b = std::move(a);  //导致TC类的移动构造函数(系统帮助我们生成的)的执行，string 类里的移动构造函数把a.s移动到b.s。
	const char *q = b.s.c_str();

	//六、总结
	//(1)尽量给类增加移动构造函数和移动赋值运算符；
	//(2)noexcept
	//(3)该给nullptr的就要给nullptr，让被移动对象随时处于一种能够被析构的状态
	//(4)没有移动，会调用拷贝代替

	return 0;
}

