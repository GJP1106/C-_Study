// 3-15.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class A {
public:
	A(int i, int j, int k) {

	}
};

class B : public A {
public:
	//B(int i, int j, int k) : A(i, j, k) {}
	using A::A; //继承A的构造函数。using：就让某个名字在当前作用域可见。
	            //遇到这条代码的时候，会把基类的每个构造函数，都生成一个与之对应的派生类构造函数。
	                //B(构造函数形参列表...):A(照抄的构造函数形参列表){} 函数为空
	                   //B(int i, int j, int k):A(i,j,k){}
	//如果基类A的构造函数有默认参数的话，那么编译器遇到这种using A::A的时候，就会帮咱们在派生类B中构造出多个构造函数来。
	//a)第一个构造函数是带有所有参数的构造函数；
	//b)其余的构造函数，每个分别省略掉 一个默认参数。
	//B(int i,int j,int k):A(i,j,k) {}
	//B(int i,int j):A(i,j) {}
	//如果类B，只含有using A::A从A类继承来的构造函数的话，那么编译器是会给它合成默认的构造函数的。
};

class Grand {
public:
	Grand(int i) : m_valuegrand(i) {
		cout << "Grand构造函数执行" << endl;
	}
	virtual ~Grand() {
		cout << "Grand析构函数执行" << endl;
	}
	void myinfo() {
		cout << m_valuegrand << endl;
	}
public:
	int m_valuegrand;
	static int m_static; //声明一个静态成员
};

//为了能够使用，我们定义这个静态成员变量(分配内存)
int Grand::m_static = 5; //如果你在代码中不用m_static,那么你可以不定义，如果代码中用到m_static，则必须定义，否则链接出错
//class AG : public Grand
class AG : virtual public Grand {
public:
	AG(int i) :Grand(i), m_valuea(i) {
		cout << "AG构造函数执行" << endl;
	}
	virtual ~AG() {
		cout << "AG析构函数执行" << endl;
	}
	void myinfo() {
		cout << m_valuea << endl;
	}
public:
	int m_valuea;
};
//class AG2 : public Grand
class AG2 : virtual public Grand { //类AG从Grand虚继承 virtual的位置和public可以调换
public:
	AG2(int i) :Grand(i), m_valuea2(i) {
		cout << "AG2构造函数执行" << endl;
	}
	virtual ~AG2() {
		cout << "AG2析构函数执行" << endl;
	}
	void myinfo() {
		cout << m_valuea2 << endl;
	}
public:
	int m_valuea2;
};

class BG {
public:
	BG() {
		cout << "BG默认构造函数执行" << endl;
	}
	BG(int i) :m_valueb(i) {
		cout << "BG构造函数执行" << endl;
	}
	virtual ~BG() {
		cout << "BG析构函数执行" << endl;
	}
	void myinfo() {
		cout << m_valueb << endl;
	}
public:
	int m_valueb;
};
//类CG同时继承AG BG
//class CG : public AG, public BG
class CG : public AG, public AG2, public BG {
public:
	//CG(int i, int j, int k) :AG(i),AG2(j), m_valuec(k) //隐式的使用B的默认构造函数(不带参数的构造函数)来初始化B的子对象。
	CG(int i, int j, int k) :AG(i),AG2(j),Grand(i), m_valuec(k) {   //虚基类时，孙子CG来初始化爷爷Grand
		cout << "CG构造函数执行" << endl;
	}
	virtual ~CG() {
		cout << "CG析构函数执行" << endl;
	}

	void myinfoC() {
		cout << m_valuec << endl;
	}
public:
	int m_valuec;
};

//(2.4)
#if 0
class A {
public:
	A(int tv) {

	}
};
class B {
public:
	B(int tv) {

	}
};
class C : public A, public B {
public:
	using A::A;   //继承A的构造函数 C(int tv):A(tv) {}
	using B::B;   //继承A的构造函数 C(int tv):B(tv) {}
	//如果一个类从它的基类中继承了相同的构造函数，这个类必须为该构造函数定义它自己的版本。
	C(int tv) :A(tv), B(tv) {

	}
};
#endif


int main()
{
	//一、继承的构造函数
	//一个类只继承其基类(父类)的构造函数。默认、拷贝、移动构造函数是不能被继承的
	//B ad(3, 4, 5);
	//如果基类含多个构造函数，则多数情况下，派生类会继承所有这些构造函数，但如下例外情况:
	//1)如果你在派生类中定义的构造函数与基类构造函数有相同的参数列表，那么从基类中继承来的构造函数会被你在派生类中的定义覆盖掉
	//(相当于你只继承了一部分基类中的构造函数)。
	//2)默认、拷贝、移动构造函数 不会被继承
	//B ad1(3, 4);

	//二、多重继承
	//单继承 ，如果从多个父类来产生出子类:多重继承；
#if 0
	CG ctest(10, 20, 30);
	ctest.myinfoC();
	//ctest.myinfo(); //要增加作用域，明确的告诉系统调用的是类A还是父类B的成员函数
	ctest.AG::myinfo();
	//如果在自己的类中定义了myinfo，则就会覆盖掉父类中的同名函数。
	//派生类会包含每个基类的子对象

#endif
	//(2.2)静态成员变量
#if 0
	//静态成员属于类,不属于对象
	CG ctest(10, 20, 30);
	Grand::m_static = 1;  //可以用类名来引用静态变量
	AG::m_static = 2;
	//BG::m_static = 5;
	CG::m_static = 4;
	ctest.m_static = 10; //可以用对象名来引用静态变量
#endif

	//(2.3)派生类析构函数与析构函数
	//a)构造一个派生类对象将同时构造并初始化所有的基类子对象。
	//b)派生类的构造函数初始化列表只初始化它的直接基类。每个类的构造函数都负责初始化它的直接基类，就会让所有类都得到初始化；
	//c)派生类构造函数初始化将实参分别传递给每个直接基类；基类的构造函数顺序跟“派生列表”中基类的出现顺序保持一致。
	//概念:显示的初始化基类和隐式初始化基类问题:
	//CG ctest(10, 20, 50);

	//(2.4)从多个父类继承构造函数
	//子类要定义同参数的构造函数，自己的版本


	//三、类型转换
	//基类指针可以指向一个派生类对象:编译器帮助我们隐式执行这种派生类到基类的转换。转换成功的原因是因为每个派生类对象都包含一个基类对象部分。
	  //所以基类的引用或者指针是可以绑到基类对象这部分上来的。
#if 0
	Grand *pg = new CG(1, 2, 3);
	AG *pa = new CG(1, 2, 3);
	BG *pb = new CG(4, 5, 6);
	CG myc(6, 7, 8);
	Grand mygrand(myc);
#endif


	//四、虚基类(virtual base class)、虚继承(虚派生)
	//派生类列表中，同一个基类只能出现一次，但是如下两种情况例外
	//a)派生类可以通过它的两个直接基类分别继承分别继承同一个间接基类；
	//b)直接继承某个基类，然后通过另一个基类间接继承该类
	//这样导致Grand被构造了两次，继承2次Grand是多余的，占空间，还可能产生名字冲突。
	CG ctest(10, 20, 50);
	//ctest.m_valuegrand = 18; //名字冲突
	//虚基类：无论这个类在继承体系中出现多少次，派生类中，都只会包含唯一一个共享的虚基类(Grand)子内容
	//大家观察到一个现象，这种虚继承只对CG类有意义，其实对于CG的父类AG,AG2没有意义；
	//换句话来说，AG、AG2从Grand类虚继承，只影响到从AG、AG2这些类中进一步派生出来的类CG，而对AG、AG2本身没有影响
	//每个Grand的子类都要虚继承Grand类，那么才能保证Grand的孙类能够虚继承Grand；
	//只要子类中都加virtual继承，那么Grand类自然就成为了“虚基类”；virtual：表达一种意愿：表示后续从我(类AG，AG2)派生的类中应该
	//共享虚基类Grand的同一份实例

	//说明两点:
	//(1)现在是CG类初始化Grand类，如果以后C类有了孩子，则由CG类的孩子初始化Grand类，换句话说，虚基类Grand是由最底层的派生类来初始化的。
	//(2)初始化顺序问题:先初始化虚基类部分，然后再按照派生列表中出现顺序来初始化其他类
	//如果多个虚基类，哪个虚基类先被初始化呢？按照派生类列表中的直接基类来往回追溯，看是否这些直接基类含有虚基类，反正是追溯到哪个基类，那就先构造哪个虚基类的内容
	//销毁和构造相反
	ctest.m_valuegrand = 18;

	//五、总结
	//小心虚继承，不太提倡使用
	//简单，不容易出现二义性，实在必要，才使用多重继承。能用单一继承解决的问题就不要用多重继承了。

	return 0;
}

