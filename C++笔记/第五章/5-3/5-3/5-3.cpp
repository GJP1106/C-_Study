// 5-3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;


shared_ptr<int> myfunc(shared_ptr<int> &ptmp)  //如果参数为引用，则智能指针的引用计数不会增加
{
	return ptmp;
}
void myfunc1(shared_ptr<int> ptmp) {
	return;
}

void myDelete(int *p) {  //自己的删除器。删除整型指针用的，当智能指针引用计数为0，就会自动调用该删除器来删除对象
	//写一些日志等等
	delete p;  //既然你自己提供了删除器来取代智能指针的缺省删除器，你就有义务自己来删除所指向的对象(引用计数为0时)
}

class A {
public:
	A() {}
	~A() {}
};

//写个函数模板来封装shared_ptr数组
template<typename T>
shared_ptr<T> make_shared_array(size_t size) {
	return shared_ptr<T>(new T[size], default_delete<T[]>());
}

int main()
{
	//一、shared_ptr引用计数的增加和减少
	 //共享式，引用计数，每一个shared_ptr的拷贝都指向相同的内存(对象)，只有最后一个指向该对象
	 //的shared_ptr指针不需要再指向该对象的时候，这个shared_ptr才会去析构所指向的对象。
	 //(1.1)引用计数的增加
#if 0
	 //每个shared_ptr都会记录有多少个其他的shared_ptr指向相同的对象；
	auto p6 = make_shared<int>(100); //目前p6所指向的对象只有p6一个引用者；
	auto p7(p6);//智能指针定义时的初始化，p7和p6指向了相同的对象，此对象目前有两个引用者；

	//在如下情况下，所有指向这个对象的shared_ptr引用计数都会增加
	//a)像上边这样，我们用p6来初始化p7这个智能指针；
   //b)把智能指针当做实参往函数里传递
	myfunc(p7);
	//c)作为函数返回值
	auto p8 = myfunc(p7);  //引用计数会变成3，这是因为有p8来接这个临时的智能指针。
	//myfunc(p7);  //没有变量来接这个临时的智能指针，则临时智能指针生命周期到了，引用计数从3恢复到2；

	//(1.2)引用计数的减少
	//a)给shared_ptr赋予新值，让该shared_ptr指向一个新对象；
	p8 = make_shared<int>(200);   //p8指向新对象，计数为1，p6、p7计数恢复为2；
	p7 = make_shared<int>(200);   //p7指向新对象，计数为1，p6计数恢复为1；
	p6 = make_shared<int>(200);   //p6指向新对象，计数为1，p6所指向的原内存被释放；
#endif
	//b)局部的shared_ptr离开其作用域
#if 0
	auto p6 = make_shared<int>(100); //目前p6所指向的对象只有p6一个引用者；
	auto p7(p6);//p7和p6指向了相同的对象，引用计数为2；
	myfunc1(p7);  //进入函数体myfunc1中是3个引用计数，从myfunc1中退出时引用计数恢复为2个
#endif

	//c)当一个shared_ptr引用计数从1变成0，则它会自动释放自己所管理(指向)的对象；
#if 0
	auto p9 = make_shared<int>(100);  //只有p9指向该对象
	auto p10 = make_shared<int>(100);
	p9 = p10; //给p9赋值会让p9指向p10所指向的对象，该对象引用计数变成2，而原来p9所指向的对象引用计数会从1变成0，从而导致被释放
#endif

	//二、shared_ptr指针常用操作
	//(2.1)use_count();返回多少个智能指针指向某个对象，主要用于调式目的；
#if 0
 	shared_ptr<int> myp(new int(100));
	int icout = myp.use_count(); //1
	shared_ptr<int> myp2(myp);
	icout = myp.use_count();
	shared_ptr<int> myp3;
	myp3 = myp2;
	icout = myp3.use_count();
	icout = myp.use_count();
#endif

	//(2.2)unique();是否该智能指针独占某个指向的对象，也就是若只有一个智能指针指向某个对象，则unique()返回true
#if 0
	shared_ptr<int> myp(new int(100));
	if (myp.unique()) {
		cout << "unique OK" << endl;
	}
	shared_ptr<int> myp2(myp);
	if (myp.unique()) {
		cout << "unique NO" << endl;
	}
#endif

	//(2.3)reset();  恢复(复位/重置)的意思
	//a)reset()不带参数时；
	  //若pi是唯一指向该对象的指针，那么释放pi所指向的对象，并将pi置空
#if 0  
	shared_ptr<int> pi(new int(100));
	pi.reset();
	if (pi == nullptr) {
		cout << "pi被置空" << endl;
	}
#endif
	//若pi不是唯一指向该对象的指针，那么不释放pi所指向的对象，但指向该对象的引用计数会减一，同时将pi置空
#if 0
	shared_ptr<int> pi(new int(100));
	auto pi2(pi);
	pi.reset();
#endif

	//b)reset()带参数(一般是一个new出来的指针)时
	   //若pi是唯一指向该对象的指针，则释放pi所指向的对象，让pi指向新对象
#if 0
	shared_ptr<int> pi(new int(100));
	pi.reset(new int(1));   //释放原来的内存，指向新的内存
#endif
	   //若pi不是唯一指向该对象的指针，那么不释放pi所指向的对象，但指向该对象的引用计数会减一，同时将pi指向新对象
#if 0
	shared_ptr<int> pi(new int(100));
	auto pi2(pi);
	pi.reset(new int(1));   //释放原来的内存，指向新的内存
#endif

	//c)空指针也可以通过reset来重新初始化
#if 0
	shared_ptr<int> p;
	p.reset(new int(1)); //释放p所指向的对象，让p指向新对象，因为原来p为空的，所以就等于啥也没释放，直接指向新对象
#endif

	//(2.4)*解引用：获得p指向的对象
#if 0
	shared_ptr<int> p(new int(123456));
	cout << *p << endl;
#endif
	//(2.5)get(); 考虑到有些函数(第三方函数)的参数需要的是一个内置裸指针而不是智能指针
	//p.get();返回p中保存的指针(裸指针)，小心使用，如果智能指针释放了所指向的对象，那么这个返回的裸指针也就变得无效了
	shared_ptr<int> myp(new int(100));
	int *p = myp.get();
	*p = 45;
	//delete p;  //千万不要这么干，不然系统会报告异常，产生不可预知的结果；

	//(2.6)swap();交换两个智能指针所指向的对象
#if 0
	shared_ptr<string> ps(new string("I love china1"));
	shared_ptr<string> ps1(new string("I love china2"));
	std::swap(ps, ps1);
#endif

	//(2.7) = nullptr
	//a)将所指向的对象 引用计数减一，若引用计数为0，则释放智能指针所指向的对象；
	//b)将智能指针置空
#if 0
	shared_ptr<string> psl(new string("I love China!"));
	psl = nullptr;
#endif
	//(2.8)智能指针名字作为判断条件
#if 0
	shared_ptr<string> psl(new string("I love China!"));
	if (psl) {
		cout << "psl指向一个对象" << endl;
	}
	psl = nullptr;
	if (!psl) {
		cout << "psl为空" << endl;
	}
#endif

	//(2.9)指定删除器以及数组问题
	//a)指定删除器
	 //一定时机帮我们删除所指向的对象；delete：将delete运算符号作为默认的资源析构方式。
	 //我们可以指定自己的删除器取代系统提供的默认删除器，当智能指针需要删除所指向的对象时，编译器就会调用我们自己的删除器
	//shared_ptr指定删除器方法比较简单,一般只需要在参数中添加具体的删除器函数名即可
#if 0
	shared_ptr<int> p1(new int(123456),myDelete);
	shared_ptr<int> p2(p1);  //两个引用计数
	p2.reset();   //剩1个引用计数，p2为nullptr
	p1.reset();   //因为此时只有1个引用计数，所以要释放指向的对象，调用我们的删除器myDelete，同时p置空

	//删除器可以是一个lambda表达式：
	shared_ptr<int> p3(new int(123), [](int *p) {
		delete p;
	});
	//有些情况，默认删除器处理不了(用shared_ptr管理动态数组)，需要我们提供自己指定的删除器
	shared_ptr<int> p4(new int[10], [](int *p) {
		delete[]p;
	});

	//shared_ptr<A> pA(new A[10]);  //异常是因为系统释放pA是delete pA所指向的裸指针，而不是delete []pA,这种情况下需要写我们自己的删除器
	shared_ptr<A> pA(new A[10], [](A *p) {
		delete[]p;
	});

	//可用default_delete来做删除器，default_delete是标准库里的模板类。
	shared_ptr<A> pA1(new A[10], std::default_delete<A[]>());

	//定义数组的时候我们在尖括号中加[]
	shared_ptr<A[]> pA2(new A[10]);  //在<>中加个[]就可以了

	//使用模板删除器
	shared_ptr<int> pintArr = make_shared_array<int>(5);
	shared_ptr<A> pAArr = make_shared_array<A>(15);
#endif
	//b)指定删除器额外说明：
	//就算是两个shared_ptr指定了不同的删除器，只要他们所指向的对象类型相同，那么这两个shared_ptr也属于同一个类型
	auto lambda1 = [](int *p) {
		delete p;
	};
	auto lambda2 = [](int *p) {
		delete p;
	};
	shared_ptr<int> p1(new int(100), lambda1);
	shared_ptr<int> p2(new int(100), lambda2);
	p2 = p1; //p2会先调用lambda2把自己所指向的对象释放，然后指向p1所指的对象，p1指向的对象引用计数为2；
	         //整个main执行完毕后，还会调用lambda1来释放p1，p2共同指向的对象；

	//类型相同，就代表可以放到元素类型为该对象类型的容器里来；
	vector<shared_ptr<int>> pvec{ p1,p2 };
	//make_shared是提倡的生成 shared_ptr的方法，但是make_shared这种方法让我们没有办法指定自己的删除器了



	



	return 0;
}

