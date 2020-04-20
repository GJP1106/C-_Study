// 8-4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <queue>
#include <forward_list>
#include <map>
#include <unordered_set>
using namespace std;

namespace _nmsp1 {

	//一、分配器概述：和容器紧密关联，一起使用
	//确切的说：内存分配器,扮演内存池的角色，通过大量减少对malloc()的调用，来节省内存，甚至还有一定的分配效率的提升；
	//经过测试：allocator这个c++标准库提供的缺省的内存分配器压根就没有采用内存池的工作机制。估计底层原封不动的调用了malloc()


	void func() {
		//vector<int,>
		//list<int> mylist;
		//list<int, std::allocator<int>> mylist1;

		list<int> mylist;  //双向链表，内存不要求挨着；
		mylist.push_back(10);
		mylist.push_back(20);
		mylist.push_back(30);
		for (auto iter = mylist.begin(); iter != mylist.end(); ++iter) {
			cout << *iter << endl;
			int *p = &(*iter);
			printf("%p\n", p);
		}
		mylist.pop_back();   //干掉30

	}
}

namespace _nmsp2 {

	//二、分配器的使用
	//allocator分配器，是个类模板，我们写代码时极少会去直接用到这个allocator这种容器的分配器；
	//但从语法上来讲，allocator分配器是能够被直接编码使用的
	void func() {
		allocator<int> aalloc; //定义一个aalloc对象，为类型为int的对象分配内存
		int *p = aalloc.allocate(3);  //allocate()是分配器中的重要函数，用来分配一段原始的未构造的内存。
		                              //这段内存能保存3个类型为int的对象(12字节)
		int *q = p;
		*q = 1; q++;
		*q = 2; q++;
		*q = 3;
		aalloc.deallocate(p, 3);  //deallocate()也是愤难平器中的重要函数。用于解释内容，你需要记住分配了几个对象，释放时要释放正确数量的对象
	}
}

namespace _nmsp3 {
	//三:其他的分配器及原理说

	//四、自定义分配器(自己写分配器)，代码繁琐，并不好写；


	void func() {
		list <int, allocator<int>> mylist;
		list <double, allocator<double>> mylist2;
	}
}

int main()
{
	//_nmsp1::func();
	//_nmsp2::func();
	_nmsp3::func();
	return 0;
}
