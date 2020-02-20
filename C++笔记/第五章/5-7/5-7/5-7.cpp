#include <iostream>
using namespace std;



unique_ptr<string> tuniqp() {
	unique_ptr<string> pr(new string("I love china"));
	return pr;  //从函数返回一个局部的unique_ptr对象。
	            //返回这种对象，导致系统给我们生成一个临时unique_ptr对象，调用unique_ptr的移动构造函数。
}
void mydelete(string *pdel) {
	delete pdel;
	pdel = nullptr;
}

int main() {

	//一、返回unique_ptr
	//虽然unique_ptr智能指针不能拷贝，但是，当这个unique_ptr将要被销毁，是可以拷贝的。最常见的用法就是从函数返回一个对象
#if 0
	unique_ptr<string> ps;
	ps = tuniqp();  //可以用ps来接，则临时对象直接构造在ps里，如果不接，则临时对象会被释放，同时会释放掉所指向的对象
#endif

	//二:指定删除器，delete：默认删除器
	//a)指定删除器
	//格式：unique_ptr<指向的对象类型，删除器> 智能指针变量名;
	//删除器，可调用对象，比如函数，类重载。
	//我们学习了shared_ptr删除器，比较简单shared_ptr<int> p(new int(),mydelete);
	//unique_ptr删除器相对复杂一点，多了一步，先要在类型模板参数中传递进去类型名，然后在参数中再给具体的删除器函数
#if 0
	typedef void(*fp)(string *);  //定义一个函数指针类型，类型名为fp；
	unique_ptr<string, fp> ps1(new string("I love china"), mydelete);

	using fp2 = void(*)(string *);  //用using定义一个函数指针类型，类型名为fp2
	unique_ptr<string, fp2> ps2(new string("I love china"), mydelete);

	typedef decltype(mydelete) * fp3;   //这里多了一个*，因为decltyoe返回的是函数类型void(string *)
	                                    //加*表示函数指针类型，现在fp3应该是 void *(string *)
	unique_ptr<string, fp3> ps3(new string("I love china"), mydelete);

	unique_ptr<string, decltype(mydelete)*> ps4(new string("I love china"), mydelete);
#endif
	//用lambda表达式  看看写法：lambda表达式可以理解成带有operator()类类型对象。
#if 0
	auto mydella = [](string *pdel) {  //把lambda表达式理解成一个class
		delete pdel;
		pdel = nullptr;
	};
	unique_ptr<string, decltype(mydella)> ps3(new string("I love china"), mydella);
#endif

	//b)指定删除器额外说明
	//shared_ptr:就算两个shared_ptr指定的删除器不相同，只要他们所指向的对象相同，那么这两个shared_ptr也属于同一个类型
	//但是unique_ptr不一样，指定unique_ptr中的删除器就会影响unique_ptr的类型，所以从灵活性来说，shared_ptr设计的更灵活
	//咱们在讲解shared_ptr的时候，删除器不同，但指向类型一样的shared_ptr，可以放到同一个容器里，vector<shared_ptr...>
	//unique_ptr如果 删除器不同，那么就等于整个unique_ptr类型不同。这种类型不同的unique_ptr智能指针是没有办法放到同一个容器里的

	//三、尺寸问题：通常情况下，unique_ptr尺寸跟裸指针一样；
#if 0
	string *p;
	int ilenp = sizeof(p); //4字节
	unique_ptr<string> ps1(new string("I love china"));
	int ilen = sizeof(ps1); //4字节

	//如果你增加了自己的删除器，则unique_ptr的尺寸可能增加，也可能不增加
	//a)如果lambda表达式这种删除器，尺寸就没变化
	auto mydella = [](string *pdel) {  //把lambda表达式理解成一个class
		delete pdel;
		pdel = nullptr;
	};
	unique_ptr<string, decltype(mydella)> ps3(new string("I love china"), mydella);
	int ilen1 = sizeof(ps3);  //4字节
	//b)定义一个函数作为删除器
	typedef void(*fp)(string *);
	unique_ptr<string, fp> psl(new string("I love china"),mydelete);
	int ilen2 = sizeof(psl);
#endif
	//增加字节对效率有影响，所以自定义删除器要慎用；
	//shared_ptr,不管你指定什么删除器，shared_ptr的尺寸都是裸指针的2倍

	//四、智能指针总结
	//(4.1)智能指针背后的设计思想
	//智能指针主要目的:帮助我们释放内存，以防止我们忘记释放内存时造成的内存泄漏
	//c++98 auto_ptr = unique_ptr
	//(4.2)auto_ptr为什么被废弃
	//auto_ptr:c++98时代的智能指针，具有unique_ptr的部分特性，unique_ptr shared_ptr weak_ptr
	//不能在容器中保存，也不能从函数中返回auto_ptr;
	auto_ptr<string> ps(new string("I love china"));
	auto_ptr<string> ps2 = ps;           //ps2指向字符串，ps变成空了，这可以防止ps和ps2析构一个string两次
	//用ps(你没有意识到ps已经空了),代码就会崩溃；
	//这个也是auto_ptr用法上的一个陷阱

	//虽然auto_ptr和unique_ptr都是独占式的，但unique_ptr这种情况，编译的时候就会报错；
	//而不会默默的把ps的所有权转移到ps2上，避免后续如果使用ps导致程序崩溃的问题；
	//当然如果你用移动语义，也能达到auto_ptr的效果
	unique_ptr<string> ps3(new string("I love china"));
	unique_ptr<string> ps4 = std::move(ps3);   //运用了移动语义

	//auto_ptr被废弃的主要原因是:设计的不太好，容易被误用引起潜在的程序崩溃问题。所以c++11启用了unique_ptr来取代auto_ptr
	//c++11表示不建议再使用auto_ptr，老师强烈建议大家，用unique_ptr取代；unique_ptr比auto_ptr更安全

	//(4.3)智能指针的选择
	//shared_ptr，unique_ptr;
	//a)如果程序要使用多个指向同一个对象的指针，应该选择shared_ptr;
	//b)如果程序不需要要使用多个指向同一个对象的指针，应该选择unique_ptr;
	









	return 0;
}