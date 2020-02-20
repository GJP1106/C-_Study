// 5-1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

void myfunc() {
	int i;
	i = 5;
	static int j; //局部静态对象
}

class A {
public:
	A() {
		cout << "A" << endl;
	}
};

int main()
{
	//一、直接内存管理(new/delete)
	myfunc();
	//A a; //编译器帮助我们创建a对象
	//二章四节 讲过 栈 堆概念
	//三章六节 new delete对象
	//new分配方式我们称为 动态分配(分配到堆上)：直接内存管理(new/delete)
	//如何初始化:
#if 0
	//int i;
	//int *point = new int;  //初值未定义
	int *point = new int(100);
	string *mystr = new string;  //空字符串，说明调用了string的默认构造函数
	string *mystr2 = new string(5, 'a');   //生成一个字符串，字符串内容是5个'a'
	vector<int> *pointv = new vector<int>{ 1, 2, 3, 4, 5 }; //一个容器对象，里边有5个对象。

	//概念“值初始化”:用()来初始化
	string *mystr3 = new string();  //也是空字符串，和mystr没啥区别；
	int *point2 = new int();  //值初始化的方式，发现point2的值被初始化了0

	A *pa = new A;
	A *pa2 = new A();   //是否是“值初始化”效果一样，都是调用A的构造函数。
	//new对象的时候，能够进行“值初始化”就进行一下为好，防止它的值没有被初始化；
#endif
#if 0
	//c++11中，auto可以和new配合使用
	string *mystr4 = new string(5, 'a');
	auto mystr5 = new auto(mystr4);   //mystr5 = string **
	delete mystr4;

	//const对象也可以动态分配
	const int *pointci = new const int(200);
#endif
	//new 和 delete说明:
	//a)成对使用，delete的作用是回收用new分配的内存(释放内存)；不是new出来的内存，是不能用delete来释放
	//b)delete一块内存，只能delete一次，不能delete多次。delete后，这块内存就不能使用了,空指针可以删除多次，但删除多次没有什么意义
	/*int i = 12;
	int *p = &i;
	delete p; */  //不是new出来的内存，不能delete。否则执行 会报异常

	//int *p = new int();
	//int *p2 = p;
	//delete p2;           //没有问题
	//delete p;            //异常，因为p和p2都指向同一段内存

	//注意事项的一个总结
	//(1)new 出来的千万不要忘记delete；否则内存泄漏，时间一长可能导致系统资源紧张，运行崩溃；
	//(2)delete后的内存不能再使用，否则异常
	int *pci = new int(300);
	*pci = 500;
	delete pci;
	//*pci = 600;
	pci = nullptr;   //这是个好习惯，表明该指针不指向任何对象了，老师提倡delete一个指针后，给该指针一个nullptr

	//3)同一块内存释放两次的问题；也会报异常
	//用new/delete直接进行内存管理，要很小心
	//c++11开始出现了“智能指针”，new，忘记了delete，智能指针能够帮助你delete

	//二、创建新工程，观察内存泄漏
	//MFC应用程序能够再一定程度上(程序退出的时候),能够帮助我们发现内存泄漏；



	return 0;
}

