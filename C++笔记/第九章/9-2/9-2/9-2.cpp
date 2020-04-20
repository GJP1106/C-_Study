// 9-2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

//void func(const int &abc) {  //abc的类型：const int & 
template<typename T>
void func(const T &abc) {

}

//void myfunc(int &&tmprv) //参数tmprv右值引用类型
//修改为函数模板后，我们看到的事实
//(1)tmprv既能接受左值，又能接受右值
//(2)tmprv的类型是T&&;
//从编译没报错来看，T被推断出来的应该不仅仅是int型(int &&tmprv,导致tmprv只能接受右值)；
template <typename T>  //函数模板
void myfunc(T&& tmprv)   //&&是属于tmprv类型的一部分，&&和T类型 没有关系
{ 
	                         //T&&或者说tmprv才是万能引用，而单纯的T不是万能引用。
	                         //如果我传递进来的一个整型的左值进来，tmprv他就应该被推断成int&类型
	                         //如果我传递进来一个整型的右值，tmprv它就应该被推断成int&&类型。
	cout << tmprv << endl;
	return;
}
//类模板
template<typename T>
class mytestc {
public:
	void testfunc(T&& x){}  //这个x是个右值引用，而不是万能引用。
	template<typename T1>
	void testfunc2(T1&& x) {}  //是万能引用
};

int main()
{
	//一、类型区别基本概念
	//func(10);   //T是什么类型，abc是什么类型。T的类型和abc类型往往不同
	            //T的类型是int， abc:const int &
	             //(1)调用函数模板时给的参数10会对T的类型产生影响.
	             //(2)abc的类型会对T的类型产生影响。
	//二、universal reference/万能引用/未定义引用 基本认识
	//&&表示右值引用。
#if 0
	int &&rv = 100;
	myfunc(10);
	int i = 10;
	myfunc(i);  //myfunc()为普通函数时错，右值引用不能接(绑)左值
	             //myfunc()为函数模板时对
#endif
	//万能引用语境:
	//a)必须是函数模板
	//b)必须是发生了模板类型推断并且函数模板形参的样子是:T&& ;auto也存在万能引用的概念。
	//T&&：就是万能引用。

	//万能引用和右值引用解释起来的区别:
	//a)右值 引用得传递右值，否则编译器报错
	//b)万能引用作函数形参时，我们可以传递给它左值，也可以传递给它右值
	   //如果我们传递进去了左值，那么这个万能引用就变成了左值引用
	   //如果我们传递进去了右值，那么这个万能引用就变成了右值引用
	//T&&  就是一个万能引用类型
	//判断题
	//(1)void func(int &&param); 右值引用。因为不是模板
	//(2)template<typename T> void func(T&& tmpvalue);  //万能引用
	//(3)
	    //template<typename T>
	    //void funcpd(std::vector<T>&& param) {} //右值引用，T没有和&&在一块

	//三、万能引用资格的剥夺和辨认
    //(1)剥夺：const修饰词会剥夺一个引用成为万能引用的资格，会被打回原型成为右值引用。
	//(2)辨认:
	mytestc<int> mc;
	int i = 100;
	//mc.testfunc(i);
	mc.testfunc(std::move(i));
	mc.testfunc2(i);

	return 0;
}
