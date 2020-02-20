#include <iostream>
using namespace std;


class A {
public:
	A() {

	}
	~A() {

	}
};



auto myfunc() {
	return unique_ptr<string>(new string("I lova china"));  //右值
}





int main() {

	//一、unique_ptr概述
	//独占式的概念(专属所有权):同一个时刻，只能有一个unique_ptr指针指向这个对象(这块内存);
	//当这个unique_ptr被销毁的时候，它所指向的对象也被销毁；
	//格式:
	//unique_ptr<指向的对象类型> 智能指针变量名;
	//(1.1)常规初始化(unique_ptr和new配合)
#if 0
	unique_ptr<int> pi;   //可以指向int对象的一个空智能指针
	if (pi == nullptr) {
		cout << "pi目前还是空指针" << endl;
	}
	unique_ptr<int> pi2(new int(105));  //此时pi2指向一个值为105的int对象
#endif

	//(1.2)make_unique函数
	//c++11中没有，c++14才有的make_unique;不支持指定的删除器语法，如果不用删除器，建议优先选择使用，更高的性能。
	unique_ptr<int> p1 = make_unique<int>(100);
	auto p2 = make_unique<int>(200);
	unique_ptr<int> pi2(new int(105));  //前边不能简写为auto

	//二、unique_ptr常用操作
	//(2.1)unique_ptr不支持的操作(独占式)
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	//unique_ptr<string> ps2(ps1);  //该智能指针不支持拷贝动作(定义时初始化)
	//unique_ptr<string> ps3 = ps1);  //该智能指针不支持拷贝动作(定义时初始化)
	//unique_ptr<string> ps4;  
	//ps4 = ps1;                       //该智能指针不支持拷贝动作(定义时初始化)
#endif

	//(2.2)移动语义
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	unique_ptr<string> ps2 = std::move(ps1);   //移动完成后，ps1为空，ps2指向原来ps1的对象
#endif

	//(2.3)release();  放弃对指针的控制权(切断了智能指针和其所指向的对象之间的联系)。
	       //返回裸指针，将该智能指针置空。返回的这个裸指针我们可以手工delete来释放，也可以用来初始化另外一个智能指针，或者给另外一个智能指针赋值；
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	unique_ptr<string> ps2(ps1.release());
	if (ps1 == nullptr) {
		cout << "ps1被置空" << endl;
	}
	ps2.release();  //会造成内存泄漏，需要delete
	//正确操作
	string *tempp = ps2.release();
	delete tempp;
#endif
	//(2.4)reset()
	//reset()不带参数情况:释放 智能指针所指向的对象，并将智能指针置空
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	ps1.reset();
	if (ps1 == nullptr) {
		cout << "ps1被置空" << endl;
	}
#endif
	//reset()带参数的情况:释放 智能指针所指向的对象，并让该智能指针指向新对象
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	unique_ptr<string> ps2(new string("I love china"));
	ps1.reset(ps2.release());  //reset释放ps1指向的对象内存，让ps1指向ps2所指向的内存，同时ps2被置空
	ps1.reset(new string("I love"));
#endif

	//(2.5) = nullptr:释放智能指针所指向的对象，并将智能指针置空
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	ps1 = nullptr;
#endif

	//(2.6)指向一个数组
#if 0
	unique_ptr<int[]> ptrarray(new int[10]);   //注意，数组这里要跟上[]
	ptrarray[0] = 12;
	ptrarray[1] = 15;

	//这里不要忘记A[],否则如果有自己的析构函数，会报异常
	unique_ptr<A[]> pA(new A[10]);
#endif
	//(2.7)get();  返回智能指针中保存的裸指针
	//考虑到有些函数参数需要的是内置裸指针(第三方代码库，咱们更改不了代码)，所以引入该函数
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	string *ps = ps1.get();
	*ps = "This is a test!";
	//delete ps; //不要这么干，否则产生不可预料的后果
#endif

	//(2.8) *解引用 ：获取该智能指针指向的对象，可以直接操作
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	*ps1 = "This is a test~";
	unique_ptr<int> pt1(new int(100));
	*pt1 = 200;

	unique_ptr<int[]> pt2(new int[10]); //对于定义的内容是数组，是没有*解引用运算符的
	//*pt2[0] = 100;
#endif

	//(2.9) swap():交换两个智能指针所指向的对象；
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	unique_ptr<string> ps2(new string("I love china2"));
	std::swap(ps1, ps2);
	ps1.swap(ps2);
#endif
	//(2.10)智能指针名字作为判断条件
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	if (ps1) {
		//若ps1指向一个对象，那么这个就成立
		cout << "ps1不为空" << endl;
	}
	ps1.reset();
	if (ps1) {
		cout << "ps1不为空" << endl;
	}
	else {
		cout << "ps1为空" << endl;
	}
#endif

	//(2.11)转换成shared_ptr类型：如果unique_ptr为右值，就可以将它赋值给shared_ptr
	//因为shared_ptr包含一个显示构造函数，可用于将右值unique_ptr转换为shared_ptr,shared_ptr将接管原来归unique_ptr所拥有的对象
#if 0
	shared_ptr<string> pss1 = myfunc();   //这里会创建控制块

	unique_ptr<string> ps(new string("I Love china"));
	shared_ptr<string> pss2 = std::move(ps);   //左值转右值，执行后ps为空，pss2就是shared_ptr
#endif












	return 0;
}