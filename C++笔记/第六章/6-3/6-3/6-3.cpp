// 6-3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
using namespace std;
//void myprint(const int &i, char *pmybuf)
//void myprint(const int i, char *pmybuf)
void myprint(const int i, const string &pmybuf) {
	cout << i << endl;  //分析认为，i并不是mvar的引用，实际是值传递，那么我们认为，即便主线程detach了子线程，那么子线程中用i仍然是安全的
	cout << pmybuf.c_str() << endl; //指针在detach子线程时，绝对会有问题
	return;
}

class A {
public:
	int m_i;
	//类型转换构造函数，可以把一个int整型转成一个类A类型
	A(int a) : m_i(a) {
		cout << "[A::A(int a)构造函数执行]" << this <<endl;
	}
	A(const A &a) : m_i(a.m_i) {
		cout << "[A::A(const A &a)拷贝构造函数执行]" << this << endl;
	}
	~A() {
		cout << "[A::~A()析构函数执行]" << this << endl;
	}
};
class B {
public:
	int m_i;
	//类型转换构造函数，可以把一个int整型转成一个类A类型
	B(int a) : m_i(a) {
		cout << "[B::B(int a)构造函数执行]" << this << "threadid = " << std::this_thread::get_id() << endl;
	}
	B(const A &a) : m_i(a.m_i) {
		cout << "[B::B(const A &a)拷贝构造函数执行]" << this << "threadid = " << std::this_thread::get_id() << endl;
	}
	~B() {
		cout << "[B::~B()析构函数执行]" << this << "threadid = " << std::this_thread::get_id()<< endl;
	}

	void thread_work(int num) {
		cout << "子线程 thread_work执行了" << endl;
	}
};
void myprint1(const int i, const A &pmybuf) {
	cout << &pmybuf << endl;   //这里打印的是pmybuf的地址
	return;
}
void myprint2(B &pmybuf) {
	pmybuf.m_i = 199;  //我们修改该值不会影响main函数
	cout << "子线程myprint2的参数地址是：" << &pmybuf << "threadid = " << std::this_thread::get_id() << endl;
	
	return;
}

void myprint3(unique_ptr<int> pzn) {
	cout << "子线程myprint3的参数地址是：" << &pzn << "threadid = " << std::this_thread::get_id() << endl;

	return;
}


int main()
{
	//一、传递临时对象作为线程参数
	  //(1.1)要避免的陷阱(解释1)
#if 0
	int mvar = 1;
	int &mvary = mvar;
	char mybuf[] = "this is a test!";
	thread mytobj(myprint, mvar, mybuf);
	//mytobj.join();
	mytobj.detach();  //子线程和主线程分别指行
#endif
	  //(1.2)要避免的陷阱(解释2)
#if 0
	int mvar = 1;
	int &mvary = mvar;
	char mybuf[] = "this is a test!";
	//thread mytobj(myprint, mvar, mybuf);  //但是mybuf到底是在什么时候转换成string。
	                                      //事实上存在，mybuf都被回收了(main函数执行完了)，系统才用mybuf去转string的可能性
	thread mytobj(myprint, mvar, string(mybuf));  //我们这里直接将mybuf转换成string对象，这是 一个可以保证在线程中用肯定有效的对象
	//mytobj.join();
	mytobj.detach();  //子线程和主线程分别指行
#endif
	//为什么写成string(mybuf)就OK了
	//事实1：只要用临时构造的A类对象作为参数传递给线程，那么就一定能够在主线程执行完毕前把线程函数的第二个参数构造出来，
	      //从而确保即便detach()子线程也安全运行
	//(1.3)总结
	//(a)若传递int这种简单类型参数，建议都是值传递，不要用引用。防止节外生枝。
	//(b)如果传递类对象，避免隐式类型转换。全部都在创建线程这一行就构建出临时对象来，然后在函数参数里，用引用来接，否则系统会多构造一次对象。
	//终极结论:
	//c)建议不使用detach(),只使用join();这样就不存在局部变量失效导致线程对内存的非法引用
#if 0
	int mvar1 = 1;
	int mysecondpar = 12;
	thread mytobj1(myprint1, mvar1, A(mysecondpar));  //我们是希望mysecondpar转成A类型对象传递给myprint的第二个参数
	                                                  //在创建线程的同时构造临时对象的方法传递参数是可行的
	//mytobj1.join();
	mytobj1.detach();  //子线程和主线程分别指行
#endif

	//二、临时对象作为线程参数继续讲，老师常用测试大法。
	//(2.1)线程id概念：id是个数字，每个线程，(不管你是主线程还是子线程)实际上都对应着一个数字，而且每个线程对应的这个数字都不同，
	//也就是说，不同的线程，它的线程id(数字)必然不同；
	//线程id可以用c++标准库里的函数来获取。std::this_thread::get_id()来获取；
	//(2.2)临时对象构造时机抓捕
#if 0
	cout << "主线程ID是：" << std::this_thread::get_id() << endl;
	int mvar = 1;
	thread mytobj2(myprint2, B(mvar));
	//mytobj2.join();
	mytobj2.detach();
#endif

	//三、传递类对象、智能指针作为参数
#if 0
	B myobj(10);
	thread mytobj(myprint2, myobj);   //myobj将类对象作为线程参数
	mytobj.join();
#endif

	//std::ref函数
#if 0
	B myobj(10);
	thread mytobj(myprint2, std::ref(myobj));   //myobj将类对象作为线程参数
	mytobj.join();
#endif
	//智能指针参数
#if 0
	unique_ptr<int> myp(new int(100));
	thread mytobj(myprint3, std::move(myp));

	mytobj.join();
#endif

	//四、用成员函数指针做线程函数 
	B myobj(10);
	thread mytobj(&B::thread_work, myobj, 15);
	mytobj.join();






	cout << "I love china!" << endl;








	return 0;
}
