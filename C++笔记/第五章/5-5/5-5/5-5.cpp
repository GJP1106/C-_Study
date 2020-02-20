#include <iostream>
using namespace std;

shared_ptr<int> create(int value) {
	return make_shared<int>(value);   //返回一个shared_ptr
}


//void myfunc(int value)
shared_ptr<int> myfunc(int value) {
	shared_ptr<int> ptmp = create(10);
	//return;  //离开作用域后，ptmp会被自动释放，它所指向的内存也会被自动释放
	return ptmp;
}
void proc(shared_ptr<int> ptr) {
	return;
}

class CT : public enable_shared_from_this<CT>{
public:
	shared_ptr<CT> getself() {
		//return shared_ptr<CT>(this);   //用裸指针初始化了多个shared_ptr的感觉
		return shared_from_this();  //这个就是enable_shared_from_this类中的方法，要通过此方法返回智能指针
	}
};

class CB;
class CA {
public:
	shared_ptr<CB> m_pbs;
	~CA() {
		int test;
		test = 1;
	}
};
class CB {
public:
	//shared_ptr<CA> m_pas;
	weak_ptr<CA> m_pas;
	~CB() {
		int test;
		test = 1;
	}
};

int main() {

	//一、std::shared_ptr使用场景
#if 0
	myfunc(12);  //如果这块不用shared_ptr变量来接收myfunc返回的结果，那么从myfunc返回的shared_ptr就会被销毁
	auto p11 = myfunc(12);  //我们用了一个变量来接myfunc的返回值，那么myfunc返回的shared_ptr就不会被销毁，它所指向的对象也不会被销毁
#endif

	//二、std::shared_ptr使用陷阱分析：一旦用错，也是致命的
	//(2.1)慎用裸指针
#if 0
	int *p = new int(100);   //裸指针
	//proc(p); //语法错，int *p不能转换成shared_ptr<ptr>
	proc(shared_ptr<int>(p));  //参数是个临时的shared_ptr，用一个裸指针显式的构造
	//*p = 45; //潜在的不可预料的问题，因为p指向的内存已经被释放了
	//以下写法OK
	shared_ptr<int> p2(p);
	proc(p2);
	*p2 = 5;
	//把一个普通裸指针绑定到了一个shared_ptr之后，那内存管理的责任就交给了这个shared_ptr了，这个时候你就不应该再用
	  //裸指针(内置指针)来访问shared_ptr所指向的内存了；

	//绝对要记住，不要用裸指针初始化多个shared_ptr
#if 0   //有问题的写法
	int *p3 = new int(100);  //裸指针
	shared_ptr<int> pi(p);
	shared_ptr<int> pi1(p);  //pi和pi1无关联了(pi和pi1每个强引用计数都为1了)，会导致pi和pi1所指向的内存被释放两次，产生异常
#endif

	shared_ptr<int> mp(new int);
	shared_ptr<int> mp1(mp);  //这种写法是OK的，mp和mp1指向同一个内存地址并且两者是互通(用的是同一个控制块)
#endif

	//(2.2)慎用get()返回的指针
	//返回智能指针指向的对象所对应的裸指针(有些函数接口可能只能使用裸指针)
#if 0
	//get返回的指针不能delete，否则会异常
	shared_ptr<int> myp(new int(100));
	int *p = myp.get();
	//delete p;  //不可以删除，会导致异常

	//不能将其他智能指针绑到get返回的指针上
	shared_ptr<int> myp1(new int(100));
	int *p = myp1.get();   //这个指针千万不能随意释放，否则myp就没办法正常管理该指针了
	{
		//shared_ptr<int> myp2(p);  //会报错，出现异常，现在myp1和myp2引用计数都为1，但一旦跳出这个程序块；就变为0了
		shared_ptr<int> myp2(myp1);  //这样写OK
	}
	//离开上边这个myp2的范围，导致myp1指向的内存被释放了；
	*myp1 = 65;   //该内存已经被释放，这样赋值会导致不可预料的后果
	//结论：永远不要用get得到的指针来初始化另外一个智能指针或者给另一个智能指针赋值
#endif

	//(2.3)不要把类对象指针(this)作为shared_ptr返回，改用enable_shared_from_this
#if 0
	shared_ptr<CT> pct(new CT);
	//shared_ptr<CT> pct1 = pct;  //这是两个强引用
	shared_ptr<CT> pct2 = pct->getself();  //问题出现
	//用到c++标准库里边的类模板:enable_shared_from_this
	//现在，在外面创建CT对象的智能指针以及通过CT对象返回的this智能指针都是安全的；
	//这个enable_shared_from_this中有一个弱指针weak_ptr，这个弱指针能够监视this，
	 //在我们调用shared_from_this()这个方法时，这个方法内部实际上是调用了这个weak_ptr的lock()方法；
	  //大家知道lock()方法会让shared_ptr指针计数+1，同时返回这个shared_ptr，这个就是工作原理
#endif

	//(2.4)避免循环引用:能够导致内存泄漏
	//MFC演示内存泄漏
	//shared_ptr<CA> pca(new CA);
	//shared_ptr<CB> pcb(new CB);
	//pca->m_pbs = pcb;       //等价于指向CB的对象有两个强引用
	//pcb->m_pas = pca;       //等价于指向CA的对象有两个强引用
#if 0
	shared_ptr<CA> pca(new CA);
	shared_ptr<CB> pcb(new CB);
	pca->m_pbs = pcb;       //等价于指向CB的对象有两个强引用
	pcb->m_pas = pca;       //因为m_pas是弱引用，所以这里指向CA的对象只有一个强引用；离开作用域之后，pca引用计数从1就变成0会释放CA对象(CA的析构函数被执行)；
	                        //CA的析构函数执行了(表示对象即将被释放)，导致CA内的m_pbs引用计数会减一，也就是指向CB对象的引用计数减一
	                        //超出pcb作用域时指向CB的计数也会-1，最终，会有一个时刻，指向CB对象的强引用计数会从1减到0
#endif

	//三、性能说明
	//shared_ptr的尺寸是裸指针的2倍； weak_ptr尺寸裸指针的2倍；
#if 0
	char *p;
	int ilenp = sizeof(p);  //4字节
	shared_ptr<string> p1;
	int ilenp = sizeof(p1); //8字节 包含两个裸指针

	//a)第一个裸指针指向的是这个智能指针所指向的对象
	//b)第二个裸指针指向的是一个很大的数据结构(控制块)，这个控制块里边有啥？
	       //1)所指对象的强引用计数:shared_ptr
	       //2)所指对象的弱引用计数:weak_ptr
	       //3)其他数据，比如删除器指针，内存分配器
	//这个控制块是由第一个指向某个对象的shared_ptr来创建的
	//控制块创建的时机:
	//a)make_shared:分配并初始化一个对象，返回指向此对象的shared_ptr,所以，这个make_shared它总是能够创建一个控制块的
	shared_ptr<int> p2 = make_shared<int>(100);
	//b)用裸指针来创建一个shared_ptr对象时；
	int *pi = new int();
	shared_ptr<int> p1(pi);
	//shared_ptr<int> p2(pi);  //不允许，否则会产生多个控制块，也就是多个引用计数(每个都是1)；析构时析构多次，导致异常

	shared_ptr<int> p3(new int);//建议这么使用
#endif
	//(3.2)移动语义
	shared_ptr<int> p1(new int());
	shared_ptr<int> p2(std::move(p1));  //移动语义，移动构造一个新的智能指针对象p2
	                                    //p1就不能再指向该对象(变成空)，引用计数依旧是1；
	shared_ptr<int> p3;
	p3 = std::move(p2);  //移动赋值，p2指向空，p3指向该对象，整个对象引用计数仍旧为1；

	//移动肯定比复制快，复制你要增加引用计数，移动不需要；
	//移动构造函数快过复制构造函数，移动赋值运算符快过拷贝赋值运算符

	//四、补充说明和使用建议
	//掌握了绝大部分shared_ptr用法；小部分没讲，靠自己摸索
	//分配器，解决内存分配问题；
	//shared_ptr<int> p(new int),mydeleter(),mymallocator<int>);

	//谨慎使用，凡是老师没讲过的用法；

	//优先使用make_shared(),不能自己定义自己的删除器
	shared_ptr<string> psl(new string("I love china"));  //分配两次内存
	auto ps2 = make_shared<string>("I love china"); //分配1次内存














	return 0;
}  