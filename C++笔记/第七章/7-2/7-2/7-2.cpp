// 7-2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;

class A {
public:
};


namespace _nmsp1 {
    //一、new内存分配细节探秘
	//我们注意到，一块内存的回收，影响范围很广，远远不是10个字节，而是一大片
	//分配内存这个事，绝不是简单的分配出去4个字节，而是再这4个字节周围，编译器做了很多处理，比如记录分配出去的字节数等等
	//分配内存时，为了记录和管理分配出去的内存，额外多分配了不少内存，造成了浪费；尤其是你频繁的申请小块内存时，造成的浪费更明显

	//new,delete(malloc,free)内存没看上区那么简单，他们的工作内容是很复杂的
	void func() {
		char *p = new char[10];
		memset(p, 0, 10);
		delete[] p;
	}
}

namespace _nmsp2 {
	//二、重载operator new和operator delete操作符
	/*void *temp = operator new(sizeof(A));
	A *pa = static_cast<A*>(temp);*/

	class A {
	public:
		static void *operator new(size_t size);
		static void operator delete(void *phead);
		A() {
			int abc;
			abc = 10;
		}
		~A() {
			int abc;
			abc = 10;
		}
	};
	void *A::operator new(size_t size) {
		A *ppoint = (A *)malloc(size);
		return ppoint;
	}
	void A::operator delete(void *phead) {
		free(phead);
	}

	void func() {
		
		/*A *pa = new A();
		delete pa;*/

		//不用自己重载的
 		A *pa1 = ::new A();
		::delete pa1;
	}
}

namespace _nmsp3 {
	//二、重载operator new[]和operator delete[]操作符

	class A {
	public:
		static void *operator new[](size_t size);
		static void operator delete[](void *phead);
		A() {
			int abc;
			abc = 10;
		}
		~A() {
			int abc;
			abc = 10;
		}
	};
	void *A::operator new[](size_t size) {
		A *ppoint = (A *)malloc(size);
		return ppoint;
	}
	void A::operator delete[](void *phead) {
		free(phead);
	}

	void func() {

		A *pa = new A[3]();  //构造函数和析构函数被调用3次，operator new[] 和operator delete[]调用了1次
		delete[] pa;

		//不用自己重载的
		/*A *pa1 = ::new A();
		::delete pa1;*/
	}
}

int main()
{
	//_nmsp1::func();
	_nmsp2::func();
	_nmsp3::func();
	return 0;
}
