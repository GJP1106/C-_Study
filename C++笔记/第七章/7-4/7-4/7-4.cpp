// 7-3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;


namespace _nmsp1 {
	//一、内存池的概念和实现原理概述
	//malloc:内存浪费，频繁分配小块内存，则浪费更加显得明显
	//“内存池”；要解决什么问题？
	  //(1)减少malloc的次数，减少malloc()调用次数就意味着减少对内存的浪费
	  //(2)减少malloc的调用次数，是否能够提高程序运行效率？会有一些速度和效率上的提升，但是提升不明显；
	//“内存池的实现原理”：
	  //(1)用malloc申请一大块内存，当你要分配的时候，我从这一大块内存中一点一点分配给你，当一大块内存分配的差不多的时候，我
		 //再用malloc再申请一大块内存，然后再一点一点的分配给你；

	//提高运行效率，减少内存浪费


	void func() {

	}
}
namespace _nmsp2 {
	//二、针对一个类的内存池实现演示代码
	//针对一个类的内存池 A
	//A *pa = new A(); delete pa;  //用内存池的手段实现new、delete一个对象；
//#define MYMEMPOOL 0
	class A {
	public:
		static void *operator new(size_t size);
		static void operator delete(void *phead);
		static int m_count;  //分配计数统计，每new一次，统计一次
		static int m_iMallocCount;  //每malloc一次，我统计一次
	private:
		A *next;
		static A* m_Freeposi;   //总是指向一块分配出去的内存的首地址
		static int m_sTrunkCount;  //一次分配多少倍的该类内存
	};

	int A::m_count = 0;
	int A::m_iMallocCount = 0;
	A *A::m_Freeposi = nullptr;
	int A::m_sTrunkCount = 50;  //一次分配5倍的该类内存作为内存池子的大小

	void *A::operator new(size_t size) {
#ifdef MYMEMPOOL
		A *ppoint = (A*)malloc(size);
		return ppoint;
#endif
		A *tmplink;
		if (m_Freeposi == nullptr) {
			//为空，我要申请内存，要申请一大块内存
			size_t realsize = m_sTrunkCount * size;   //申请m_sTruckCount这么多倍的内存
			m_Freeposi = reinterpret_cast<A*>(new char[realsize]);   //传统new，调用的系统底层的malloc
			tmplink = m_Freeposi;

			//把分配出来的这一大块内存(5小块),彼此要连起来，供后续使用
			for (; tmplink != &m_Freeposi[m_sTrunkCount - 1]; ++tmplink) {
				tmplink->next = tmplink + 1;
			}
			tmplink->next = nullptr;
			++m_iMallocCount;
		}
		tmplink = m_Freeposi;

		m_Freeposi = m_Freeposi->next;
		++m_count;

		return tmplink;
	}

	void A::operator delete(void *phead) {
#ifdef MYMEMPOOL
		free(phead);
		return;
#endif
		(static_cast<A*> (phead))->next = m_Freeposi;
		m_Freeposi = static_cast<A*>(phead);
	}




	void func() {
		clock_t start, end;
		start = clock();
		for (int i = 0; i < 15/*000000*/; i++) {
			A *pa = new A();
			printf("%p\n", pa);
		}
		end = clock();
		cout << "申请分配内存的次数为：" << A::m_count << "实际malloc的次数为:" << A::m_iMallocCount << "用时(毫秒):" << end - start << endl;
	}
}

namespace _nmsp3 {
	//一、嵌入式指针(embedded pointer)
	//(1.1)嵌入式指针概念
	//一般应用在内存池相关的代码中：
	//嵌入式指针工作原理：借用A对象所占用的内存空间中的前4个字节，这4个字节用来 链住这些空闲的内存块
	//但是，一旦某一块被分配出去，那么这个块的前4个字节 就不再需要，此时这4个字节就可以正常使用了

	//(1.2)嵌入式指针演示代码
	//sizeof()超过4字节的类就可以安全的使用嵌入式指针，因为，在当前vs2017环境下，指针的sizeof值是4

	class TestEP {
	public:
		int m_j;
		int m_i;
	public:
		struct obj {
			//成员，是个指针
			struct obj *next;   //这个next就是个嵌入式指针
			                    //自己是一个obj结构对象，那么把自己这个对象的next指向另外一个obj结构对象，最终，把多个自己串起来
		};
	};



	void func() {
		TestEP mytest;
		cout << sizeof(mytest) << endl;  //8
		TestEP::obj *ptemp;  //定义一个指针
		ptemp = (TestEP::obj *)&mytest;   //  把对象myte st首地址给了这个指针ptemp，这个指针ptemp指向对象mytest首地址；
		cout << sizeof(ptemp->next) << endl;  //4
		ptemp->next = nullptr;
	}
}

namespace _nmsp4 {
	//二、内存池代码的改进
	//单独的为内存池技术来写一个类

	//专门的内存池类
	class myallocator {  //必须保证应用本类的类不少于4字节，否则会崩溃或者报错
	public:
		//分配内存接口
		void *allocate(size_t size) {
			obj *tmplink;
			if (m_FreePosi == nullptr) {
				//为空，我要申请内存，要申请一大块内存
				size_t realsize = m_sTrunkCout * size;   //申请m_sTruckCount这么多倍的内存
				m_FreePosi = (obj *)malloc(realsize);   //malloc
				tmplink = m_FreePosi;

				//把分配出来的这一大块内存(5小块),彼此要连起来，供后续使用
				for (int i = 0; i < m_sTrunkCout - 1; ++i) {
					tmplink->next = (obj *)((char *)tmplink + size);
					tmplink = tmplink->next;
				}
				tmplink->next = nullptr;
			}
			tmplink = m_FreePosi;

			m_FreePosi = m_FreePosi->next;
			return tmplink;
		}
		//释放内存接口
		void deallocate(void *phead) {
			((obj *)phead)->next = m_FreePosi;
			m_FreePosi = (obj *)phead;

		}
	private:
		//卸载类内的结构，这样next就是个嵌入式指针
		struct obj {
			struct obj *next;   //这个就是嵌入式指针
		};
		int m_sTrunkCout = 5;
		obj* m_FreePosi = nullptr;
	};

#define DECLARE_POOL_ALLOC()\
public:\
	static myallocator myalloc;\
	static void *operator new(size_t size) {\
		return myalloc.allocate(size);\
	}\
	static void operator delete(void *phead) {\
		return myalloc.deallocate(phead);\
	}

#define IMPLEMENT_POOL_ALLOC(classname)\
myallocator A::myalloc;

	class A {
	public:
		int m_i;
		int m_j;  //为了保证sizeof凑够4个字节
#if 0
	public:
		static myallocator myalloc;  //静态成员变量
		static void *operator new(size_t size) {
			return myalloc.allocate(size);
		}
		static void operator delete(void *phead) {
			return myalloc.deallocate(phead);
		}
#endif
		DECLARE_POOL_ALLOC()
	};
	IMPLEMENT_POOL_ALLOC(A)

	void func() {
		A *mypa[100];
		for (int i = 0; i < 15; ++i) {
			mypa[i] = new A();
			printf("%p\n", mypa[i]);
		}
		for (int i = 0; i < 15; ++i) {
			delete mypa[i];
		}
	}

}

int main()
{
	//_nmsp1::func();
	//_nmsp2::func();
	//_nmsp3::func();
	_nmsp4::func();
	return 0;
}

