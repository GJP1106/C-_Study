// 5-2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class A {
public:
	A() {
		cout << "A()构造函数被调用" << endl;
	}
	~A() {
		cout << "~A()析构函数被调用" << endl;
	}
};

shared_ptr<int> makes(int value)
{
	//return new int(value);  //不可以，无法把new得到的int* 转换成shared_ptr<int>
	return shared_ptr<int>(new int(value)); //可以，显示的用int *创建
}


int main()
{
	//一、new/delete探秘
	//(1.1)new，delete是什么?
	//sizeof(关键字/运算符)，不是个函数。
	//new,delete(关键字/运算符)，不是个函数。
	//malloc/free(主要用于c语言编程中)，而new/delete用于c++编程:这两对都用于动态的在堆中分配/释放内存
	//new/delete比malloc/free干的事情更多；

	//A *pa = new A();   //构造函数被调用
	//delete pa;
	//new/delete具备对 堆上所分配内存进行初始化/释放(反初始化)的能力，而这些能力是malloc/free所不具备的

    //(1.2) operator new() 和 operator delete()
	int *pi = new int;
	delete pi;
	//operator new() 和 operator delete() 函数
	//(1.2.1)new干了两个事情:a)分配内存(通过operator new()来分配内存)，b)调用构造函数来初始化内存。
	//void *myorgpoint = operator new(100);  //分配100字节，一般没人这么干；
	//(1.2.2)delete 也干了两个事:a)调用析构函数  b)释放内存(调用operator delete()来释放内存)。


	//(1.3)基本new如何记录分配的内存大小供delete使用
	//不同的编译器new内存有不同的实现方式；
#if 0
	int *p = new int; //4字节
	delete p;   //删除的时候，编译器怎么知道要回收的是4字节；new内部有记录机制，记录了分配出去多少内存
#endif

	//(1.4)申请和释放一个数组
	//见5-1-MFC工程
	//int i;
	//i = 4;
	//string *ppts = new string("I love China!"); //没有delete必然会导致内存泄漏
	//delete ppts;

	//int *p = new int(100);   //分配4字节，给int = 100
	//int *p = new int[2];   //int数组，有两个元素

	/*A a;
	int ilen = sizeof(a);*/   //类对象肯定有地址，你就得至少占1个字节的地方
	/*A *pA = new A();   //泄漏1字节
	A *pA1 = new A[2]();  //这里泄漏6个字节，而不是2字节，多出4字节；这四个自己用来干嘛的？
	int *p = new int[2]; */ //int数组，有两个元素，泄漏8字节，没有多出4字节来呢？
	//疑问：为什么动态给类型A分配内存对象时多出来4个字节，而给内置类型int动态分配内存对象数组时并没有多出来4字节？

	//new[] 应该用delete[]释放
#if 0
	int *p = new int[3];  //int内置类型
	//delete p; //没有用[]，似乎也可以直接释放p这个int数组，没有发生内存泄漏；
	delete[] p;  //这种释放方法才是规范的，绝对没有问题的。
#endif
#if 0
	A *pA = new A[2]();  //泄漏6字节，2个字节代表类对象数组占用的，额外4字节我们纳闷这4字节从哪里来
	//delete pA;  //系统报告异常，为什么报异常呢？
	delete[] pA;
#endif
	//(1.5)为什么 new/delete, new[] / delete[] 要配对使用？
	//内置类型，比如int不需要调用析构函数。所以new[] 的时候系统并没有多 分配出4字节；
	//对于int类型，new [],delete p 或者 delete[] p,效果一样；
	//结论：如果一个对象(内置对象比如int,float,包括类对象A)，使用new[]来分配内存，却用单独的delete(而不是delete[])来释放内存，那么这个对象需要满足的条件是:
	//对象的类型要么是内置类型或者 无自定义的析构函数的类类型。

	//A *pA = new A[2]();  //如果没析构函数，这里就分配了2个字节。
	//delete pA;           //此时就可以使用不带[]的delete
	//为什么自己一提供析构函数，不用delete[]来释放new[]出来的内存就报异常呢?
	//a)调用一次A的析构函数而不是2次，至少是表示有内存泄漏；
	//b)operator delete(pA);释放内存。
	//结论：new/delete, new[]/delete[]要配对使用；否则程序出错，自食恶果

	//(2)智能指针总述
	int *p = new int();
	int *q = p;
	int *r = q;  //只有p,q,r都不再使用了的时候，才能释放掉这段内存。
	//new /delete 的写法要非常小心，防止早早的释放，也防止忘记释放，总之:用好并不容易
	//p裸指针:直接用new返回的指针，这种指针：强大，灵活，但是开发者全程负责维护，一个不小心，就容易用错；一旦用错，造成的问题会极大
    //智能指针:解决裸指针可能代码的各种问题；
	//智能指针:就理解成对“裸指针”进行了包装，给裸指针外边包了一层；包装后为我们带来的优点:
	   //最突出的优点:智能指针能够“自动释放所指向的对象内存”，大家再也不用担心自己new出来的内容忘记释放了；
	  //建议优先选择智能指针。使用智能指针的程序更容易编写和调试；

	//c++标准库有四种智能指针:std::
	//a)auto_ptr(c++98); unique_prt(c++11); shared_ptr(c++11); weak_ptr(c++11);
	//帮助我们进行动态分配对象(new出来的对象)的生命周期的管理。能够有效防止内存泄漏；
	//目前auto_ptr已经完全被unique_ptr取代，所以大家不要再使用auto_ptr;c++11标准中反对使用auto_ptr(弃用);
	//这三种智能指针都是类模板，我们可以将new获得的地址赋给他们；
	//shared_ptr:共享式指针。多个指针指向同一个对象，最后一个指针被销毁时，这个对象会被释放
	   //weak_ptr是辅助shared_ptr工作的；
	//b)unique_ptr:独占式指针，同一时间内，只有一个指针能够指向该对象。
	    //当然，该对象的所有权还是可以移交出去的；
	//你忘记delete的时候，智能指针帮助你delete，或者说，你压根就不再需要自己delete，智能指针的本份(帮助你delete)；

	//三、shared_ptr基础
	//共享所有权，不是被一个shared_ptr拥有，而是被多个shared_ptr之间相互协作；shared_ptr有额外开销；
	//工作原理:引用计数，每个shared_ptr的拷贝都指向相同的内存。所以，只有最后一个指向该内存(对象)的shared_ptr指针不需要再指向该对象时；
	//那么这个shared_ptr才会去析构所指向的对象，最后一个指向该内存对象的shared_ptr在什么情况下会释放该对象(shared_ptr所指向的对象)呢？
	 //a)这个shared_ptr被析构的时候；
	 //b)这个shared_ptr指向其他的对象时；
	//垃圾回收机制，我们从此不用担心对象何时被delete
	//类模板：用到<>,<>里，就是指针可以指向的类型，后边再跟智能指针名；
	//格式：shared_ptr<指向的类型> 智能指针名；
	//(3.1)常规初始化(shared_ptr和new配合)
	//shared_ptr<int> pi;  //指向int的智能指针，名字pi，但目前指向为空，空指针，nullptr；


	//shared_ptr<int> pi(new int(100));  //pi指向一个值为100的int型数据
	//shared_ptr<int> pi2 = new int(200);  //不行，智能指针是explicit，不可以进行隐式类型转换。必须用直接初始化形式；

	//shared_ptr<int> pi3 = makes(130);
	//裸指针可以初始化shared_ptr，但不推荐。智能指针和裸指针不要穿插用；
	/*int *pi = new int;
	shared_ptr<int> p1<pi>;*/  //不推荐

	//shared_ptr<int> p1(new int);

	//(3.2)make_shared函数:标准库里的函数模板。安全，高效的分配和使用shared_ptr;
	//它能够在动态内存(堆)中分配并初始化一个对象，然后返回指向此对象的shared_ptr;
	shared_ptr<int> p2 = make_shared<int>(100);  //这个shared_ptr指向一个值为100的整型内存，有点类似int *pi = new int(100);
	shared_ptr<string> p3 = make_shared<string>(5, 'a');  //5个字符a生成的字符串。
	            //类似于string mystr(5,'a');
	shared_ptr<int> p4 = make_shared<int>(); //p4指向以恶int，int里保存的值是0(值初始化)
	p4 = make_shared<int>(400);  //p4指向一个新int，int里保存的是400；p4首先释放刚才指向的值为0的内存，然后指向这个新内存

	auto p5 = make_shared<string>(5, 'a');  //用auto比较简单









	return 0;
}

