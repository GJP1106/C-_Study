// 7-1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;
namespace  _nmsp1 {
	class A {
	public:
		int m_i;
		A() {

		}
	};
	void func() {
		//一、总述与回顾：二章四节，五章二节
		//二、从new说起
		//(2.1)new类对象时加不加括号的差别
		    //(2.1.1)如果是个空类，那么如下两种写法没有区别，现实中，你不可能光写一个空类
		
		    //(2.1.2)类A中有成员变量则：
		       //带括号的初始化会把一些和成员变量有关的内存清0，但是不是整个对象的内存全部清0；
		    //(2.1.3)当类A有构造函数，下面两种写法得到的结果一样了。
		    //(2.1.4)不同的看上去的感觉
#if 0
		A *pa = new A();   // 函数调用
		A *pa1 = new A;

		int *p3 = new int;  //初值随机
		int *p4 = new int(); //初值为0
		int *p5 = new int(100);  //初值100
#endif
		//(2.2)new干了啥 :一个是调用了operator new(malloc)，一个是调用了类A的构造函数
		//delete干了啥：一个是调用了类A的析构函数，一个是调用了operator delete(free)
		A *pa = new A();   // 函数调用
#if 0
		A *pa = new A();  //操作符
		    operator new()  //函数
			    malloc(); //c语言中的malloc
		    A::A();  //有构造函数就调用
#endif
		delete pa; 
#if 0
		delete pa;
		    A::~A();  //析构函数
			operator delete()
				free()  //c语言中的free函数
#endif

		//(2.3)malloc干了啥：
		//(2.4)总结

		A *pa1 = new A;

		int *p3 = new int;  //初值随机
		int *p4 = new int(); //初值为0
		int *p5 = new int(100);  //初值100

	}
}



int main()
{
	_nmsp1::func();
	return 0;
}

