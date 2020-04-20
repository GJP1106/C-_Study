// 9-7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>
#include <functional>
using namespace std;

void myfunc(int tv) {
	cout << "myfunc()函数执行了，tv = " << tv << endl;
}

class TC {
public:
	TC() :m_a(1) {

	}
	void operator()(int tv) {
		cout << "TC::operator()执行了tv = "<< tv << endl;
	}
	void ptfunc(int tv) {
		cout << "TC::ptfunc()执行了tv = " << tv << endl;
	}
	int m_a;
	static int stcfunc(int tv) {
		cout << "TC::stcfunc()静态函数执行了tv = " << tv << endl;
		return tv;
	}
};

class TC1 {
public:
	using tfpoint = void(*)(int);  //定义一个函数指针类型
	static void mysfunc(int tv) {
		cout << "TC1::mysfunc()静态成员函数执行了，tv = " << tv << endl;
	}
	operator tfpoint() {
		return mysfunc;
	}
};

class TB {
	std::function<void()> fcallback;
public:
	TB(const std::function<void()>&f) : fcallback(f) {
		int i;
		i = 1;
	}
	void runcallback(void) {
		fcallback();
	}
};

class CB {
public:
	void operator()(void) {
		cout << "CB::operator()执行了" << endl;
	}
};

void mycallback(int cs, const std::function<void(int)> &f) {
	f(cs);
}
void runfunc(int x) {
	cout << x << endl;
}

void myfunc1(int x, int y, int z) {
	cout << "x = " << x << " y = " << y << " z = " << z << endl;
}
void myfunc2(int &x, int &y) {
	x++;
	y++;
}

class CT2 {
public:
	CT2() {
		cout << "CT2构造函数" << endl;
	}
	CT2(const CT2& tm) {
		cout << "CT2拷贝构造函数" << endl;
	}
	~CT2() {
		cout << "~CT2析构函数" << endl;
	}
	void myfunpt(int x, int y) {
		cout << "x = " << x << " y = " << y << endl;
		m_a = x;
	}
	void operator() () {
		cout << "operator()被调用" << endl;
	}
	int m_a = 0;
};


int main()
{
	//一、可调用对象
	//1：函数；2：重载了()运算符的类的对象
	//(1.1)函数指针
#if 0
	void(*pmf)(int) = &myfunc;  //定义一个函数指针pmf并给了初值
	pmf(15);    //调用函数，这就是个可调用对象。
#endif
	//(1.2)具有operator()成员函数的类对象(仿函数)
	//仿函数的定义：仿函数(functor),它的行为类似于函数的东西(something that performs a function)
	//c++仿函数就是通过在类中重载()运算符实现。又称为函数对象(function object):能行使函数功能的类。
#if 0
	TC tc;
	tc(20);   //调用的是()操作符，这也是个可调用对象
#endif
	//(1.3)可被转换为函数指针的类对象(仿函数/函数对象)
#if 0
	TC1 tc1;
	tc1(50);  //先调用tfpoint，再调用mysfunc，这也是个可调用对象。
#endif

	//(1.4)类成员函数指针
#if 0
	TC tc;
	void (TC::*myfpoint)(int) = &TC::ptfunc;   //类成员函数指针变量myfpoint定义并给初值
	(tc.*myfpoint)(68);  //也是一个可调用对象
#endif

	//(1.5)总结
	//a)看成对象
	//b)我们可以对其使用()调用运算符，如果a是可调用对象，那么我们就可以编写a(param...)代码。

	//如何能把各种不同的可调用对象的形式统一一下，统一的目的是方便咱们调用；
	//二、std::function(可调用对象包装器) c++11，std::function是个类模板，用来装各种可调用对象
	//不能装类成员函数指针。
	//std::function类模板的特点：就是能够通过给它指定模板参数，它就能够用统一的方式来处理函数。
#if 0
	//(2.1)绑定普通函数
	std::function<void(int)> f1 = myfunc;
	f1(100);
	//(2.1)绑定类的静态成员函数
	std::function<int(int)> fs2 = TC::stcfunc;   //绑定一个类的静态成员函数
	cout << fs2(110) << endl;

	//(2.3)绑定仿函数
	TC tc3;
	std::function<void(int)> f3 = tc3;
	f3(123);

	TC1 tc4;
	std::function<void(int)> f4 = tc4;
	f4(120);
#endif
	//(2.4)范例演示
#if 0
	CB cb;   //可调用对象
	TB tb(cb);  //tb需要可调用对象做参数来构造，ct因为有operator()所以可以转为std::function(void()&)对象；
	tb.runcallback();   //执行的是CB里的operator
#endif
#if 0
	for (int i = 0; i < 10; i++) {
		mycallback(i, runfunc);  //runfunc(i)
	}
#endif

	//三、std::bind绑定器，也是个类模板，c++引入的
	//std::bind能够将对象以及相关的参数绑定到一起，绑定完后可以直接调用，也可以 用std::function进行保存，
	//在需要的时候调用
	//格式：
	//std::bind(待绑定的函数对象/函数指针/成员函数指针，参数绑定值1，参数绑定值2...参数绑定值n);
	//总结
	//a)将可调用对象和参数绑定到一起，构成一个仿函数，所以可以直接调用
	//b)如果函数有多个参数，可以绑定一部分参数，其他参数在调用的时候指定；
#if 0
	auto bf1 = std::bind(myfunc1, 10, 20, 30);  //auto表示不关心bind的返回类型，
	//其实bind它返回的是一个仿函数类型，可以直接调用，也可以赋给std::function
	bf1();  //执行myfunc1函数
#endif

	//表示绑定函数myfunc1的第三个参数为30，myfunc1的第一个和第二个参数分别由调用bf2是的第一、二个参数指定
	//_1是标准库里定义的，占位符的含义，类似这样的占位符有20个，足够我们使用
	//这里这个placeholders::_1表示这个位置(当前placeholders::_1所在的位置)将在函数调用时，被
	//传入的第一个参数
#if 0
	auto bf2 = std::bind(myfunc1, placeholders::_1, placeholders::_2, 30);
	bf2(100,200);
	std::bind(myfunc1, placeholders::_1, placeholders::_2, 30)(10,30);
	std::bind(myfunc1, placeholders::_2, placeholders::_1, 30)(10, 30);
#endif
#if 0
	int a = 2;
	int b = 3;
	auto bf4 = std::bind(myfunc2, a, placeholders::_1);  //a没有自加1
	bf4(b);
	cout << "a = " << a << " b = " << b << endl;//a = 2 b = 4
	//这说明：bind对于预先绑定的函数参数是通过值传递的，所以这个a实际上是值传递的。
	//bind对于不事先绑定的参数，通过std::placeholders传递的参数，是通过引用传递的，所以b实际上是引用传递
#endif
#if 0
	CT2 ct;  //一个CT2类的对象
	//auto bf5 = std::bind(&CT2::myfunpt, ct, std::placeholders::_1, std::placeholders::_2);
	//bf5(10, 20);  //上行第二个参数ct， 会导致调用CT2的拷贝构造函数来生成一个CT2类的临时对象，作为std::bind的返回值(bind返回仿函数类型对象)
	              //后续的myfuncpt调用修改的是这个临时对象的m_a值，并不影响真实的ct对象的m_a的值
	auto bf5 = std::bind(&CT2::myfunpt, &ct, std::placeholders::_1, std::placeholders::_2);
	bf5(10, 20);   //上行第二个参数ct前边如果加了&，就不生成临时的CT2对象了，后续myfunpt调用修改的是ct对象的m_a值。
	              //这说明此时bind返回的这个对象其实是ct对象本身(仿函数类型对象)
#endif

	//std::bind和std::function的配合使用
#if 0
	CT2 ct;  
	std::function<void(int, int)> bfc6 = std::bind(&CT2::myfunpt, ct, std::placeholders::_1,std::placeholders::_2);
	bfc6(10, 20);
#endif

	//把成员变量地址当函数一样绑定，绑定的结果放在std::function<int &(void)>里保存：
	//说白了就是用一个可调用对象的方式来表示这个变量
#if 0
	CT2 ct;
	//std::function<int &()> bf7 = std::bind(&CT2::m_a, &ct);
	std::function<int &()> bf7 = std::bind(&CT2::m_a, ct); 
	                         //如果bind第二个参数用的不是&，那么这个bind会导致产生两次CT2拷贝构造函数的执行
	                      //第一次拷贝构造函数的执行是因为系统利用ct来产生一个临时的CT2对象
	                      //第二次拷贝构造函数的执行是因为std::bind本身要返回一个CT2对象，要返回的CT2对象(仿函数)拷贝自临时的CT2对象
	                         //但是std::bind执行完毕后，临时CT对象会被释放，返回的这个CT对象(仿函数)就弄到bf7
	bf7() = 60;     
#endif
#if 0
	//CT2 ct;
	auto rt = std::bind(CT2()); //CT2()是构造临时对象，然后又调用了拷贝构造函数生成了一个可调用对象，
	                            //作为std::bind()的返回仿函数类型对象，就是这个用拷贝构造函数构造出来的对象
	rt();
#endif
	auto bf = std::bind(runfunc, std::placeholders::_1); //runfunc的第一个参数由调用时的第一个参数指定
	for (int i = 0; i < 10; i++) {
		mycallback(i,bf);  //调用的是runfunc
	}

	//四、总结
	//a)bind思想：所谓的延迟调用，将可调用对象统一格式，保存起来，需要的时候再调用；
	//b)我们有用std::function绑定一个可调用的对象，类型成员不能绑。std::bind成员函数，成员变量都能绑













	return 0;
}
