// 5-4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

int main()
{
	//一、weak_ptr概述：weak_ptr辅助shared_ptr进行工作；
	//weak "弱" 反义词 “强”
	//强指的是shared_ptr, 弱指的是weak_ptr
	//weak_ptr:也是个类模板，也是个智能指针。这个智能指针指向一个由shared_ptr管理的对象，但是weak_ptr这种指针不控制所指向对象的生命周期
	//换句话说，将weak_ptr绑定到shared_ptr上并不会改变shared_ptr的引用计数(更确切的说，weak_ptr的构造和析构不会增加或者减少所指向对象的引用计数)
	//当shared_ptr需要释放所指定对象的时候照常释放，不管是否有weak_ptr指向该对象。weak 这个意思“弱”，能力弱。

	//这个弱引用的作用：大家可以理解成监视shared_ptr(强引用)的生命周期用的。是一种对shared_ptr的扩充。
	  //weak_ptr不是一种独立的智能指针，不能用来操作所指向的资源，所以它看起来像一个shared_ptr的助手
	//weak_ptr能够监视到它所指向的对象是否存在；

	//(1.1)weak_ptr的创建
#if 0
	//我们创建weak_ptr的时候，一般是用一个shared_ptr来初始化:
	auto pi = make_shared<int>(100);  //shared_ptr
	weak_ptr<int> piw(pi);  //piw弱共享pi，pi引用计数(强引用计数)不改变，但是弱引用计数会改变(弱引用计数会从0变成1)
	                       //强引用计数才能决定对象的生存期，弱引用计数对对象生存周期没有影响。
	weak_ptr<int> piw1;
	piw1 = pi;   //pi是一个shared_ptr，赋值给一个weak_ptr，两者指向同一个内存对象;
	weak_ptr<int> piw2;
	piw2 = piw1;  //把weak_ptr赋给另外一个weak_ptr，现在pi是一个强引用。piw、piw1和piw2是三个弱引用
	//lock()：功能就是检查weak_ptr所指向的对象是否存在，如果存在，那么这个lock他就能返回一个指向该对象的shared_ptr(指向对象的强引用计数就会+1)
	          //如果不存在，lock就会返回一个空的shared_ptr
	pi.reset();  //因为pi是唯一指向该对象的强引用智能指针，所以reset()会释放pi所指向的对象，同时将pi置空
	auto pi2 = piw.lock();  //pi2是一个shared_ptr
	if (pi2 != nullptr) {
		//所指向的对象存在
		*pi2 = 12;
	}
	else {
		cout << "lock失败" << endl;
	}
	//总结上边这段代码:weak_ptr能够判断所指向的对象是否存在，这种能力
#endif
	//二、weak_ptr常用操作
	//(2.1)use_count();获取与该弱指针共享对象的其他shared_ptr的数量，或者说获得当前所观测的强引用计数。
#if 0
	auto pi = make_shared<int>(100);
	auto pi2(pi);  //是一个shared_ptr
	weak_ptr<int> piw(pi);
	int isc = piw.use_count();
	cout << isc << endl;


	//(2.2)expired();是否过期的意思。若该指针的use_count()为0(表示该弱指针指向的对象已经不存在了)，则返回true，否则返回false
	//换句话说，这个函数用来判断 所观测的资源是否已经被释放；
#if 0
	pi.reset();
	pi2.reset();
	if (piw.expired()) {
		cout << "对象已过期" << endl;
	}
#endif

	//(2.3):将该弱引用指针设置为空，不影响指向该对象的强引用数量，但指向该对象的弱引用数量会减少1；
	piw.reset();
#endif
	//(2.4)lock()
#if 0
	auto p1 = make_shared<int>(42);
	weak_ptr<int> pw;
	pw = p1;
	if (!pw.expired()) {
		auto p2 = pw.lock();   //返回一个shared_ptr,并且 此时强引用计数为2
		if (p2 != nullptr) {
			int test;
			test = 1;
			//离开这个范围，强引用计数会恢复为1
		}
	}
	else {
		int test;
		test = 1;
	}
	//走到这里，强引用计数会恢复为1
#endif

	//三、尺寸问题
	//weak_ptr<int> pw;
	//weak_ptr的尺寸和shared_ptr尺寸一样大，是裸指针的2倍
	weak_ptr<int> pw;
	int *p;
	int ilen1 = sizeof(p); //4个字节 是个裸指针
	int ilen2 = sizeof(pw); //8个字节 两个裸指针
	//第一个裸指针 指向的是这个智能指针所指向的对象
	//第二个裸指针 指向的是一个很大的数据结构(控制块),这个控制块里有:
	               //1)所指对象的强引用计数
	               //2)所指对象的弱引用计数
	               //3)其他数据，比如自定义的删除器的指针等等


	//总结:基本具备能够读懂实战代码的能力。大家缺乏实战。









	return 0;
}
