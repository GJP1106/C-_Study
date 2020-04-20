// 9-4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <boost/type_index.hpp>
using namespace std;

template<typename T>
void myfunc(T&& tmprv) {   //万能引用
	cout << "----------------------begin---------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;  //显示T类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl;
	cout << "----------------------end---------------" << endl;
}

//模板函数：目的 要把收到的参数以及这些参数相对应得类型不变的转发给其他函数(转发给myfunc函数)，这就叫转发；
template<typename F,typename T1,typename T2>
//myFuncTmp()相当于通过这个来转发。
void myFuncTmp(F f, T1 &&t1, T2 &&t2) {   //F就是第三方我们要调用的函数,就是要转发到的目的函数
	f(std::forward<T1>(t1), std::forward<T2>(t2));
}

void myfunc1(int v1, int &v2) {
	++v2;
	cout << v1 + v2 << endl;
}

int main()
{
	//一、引用折叠 规则，以往掌握了 万能引用
	//int i = 18;  //i的类型是int型，i本身是个左值
	//myfunc(100);  // i是个右值，T = int, tmprv = int &&
	//myfunc(i);   //i是个左值，T = int &, tmprv = int &

	//void myfunc(int& &&tmprv) {}  //我们模拟编译器：认为这是编译器应该给我们实例化出来的myfunc的样子
	                                //int& 是一组  &&tmprv是一组
	//void myfunc(int &tmprv){}   //这个是编译器真正给我们实例化出来的myfunc模板函数的样子。

	//引用折叠:c++11新概念，是条规则(reference-collapsing rules),引用坍塌
	//c++中有明确含义的引用只有两种，一种是&左值引用(类型)，一种是带&&右值引用(类型)。

	//void myfunc(int& &&tmprv)  // 两组，第一组int& 左值引用  第二组 &&tmprv 实际是右值引用类型
	//分成两组的， 第一组：左值引用/右值引用   第二组：左值引用/右值引用
	//左值引用  ---  左值引用  &    &
	//左值引用  ---  右值引用  &    &&
	//右值引用  ---  左值引用  &&   &
	//右值引用  ---  右值引用  &&   &&
	//折叠规则：如果任意一个引用为左值引用，那么结果就为左值引用,否则就是右值引用
	//(1.1)引用的引用：void func(int & &&i) {}  // "i" :引用的引用非法
	//int b = 100;
	//int &by = b;  //by是b的引用
	//int & &byy = by;  //byy是by的引用，引用的引用非法
	//程序开发者不可以写引用的引用，编译器内部可以有，采用引用折叠来处理


	//二、转发、完美转发
	int i = 50;
	myfunc1(41, i);
	//int j = 70;
	//myFuncTmp(myfunc1, 20, j);

	//修改myfunctmp模板函数，让这个模板函数的参数 能够保持给定实参 的左值性(如果有const属性，也希望被传递)
	//万能引用就出场：T&& 实参的所有信息都回传递到万能引用当中去，从而让编译器推导出来函数模板最终的形参类型
	//T &,则实参中只有const属性能传递到函数模板，而实参中的左值和右值性质就无法传递到函数模板中去，所以我们必须用T&&


	//完美转发：让我们可以写接受任意类型实参的函数模板，并将其转发到目标函数，目标函数会接收到与转发函数所接受到的完全相同
	//三、std::forward要上场了
	//c++11新函数，专门为转发而存在。要么返回一个左值，要么返回一个右值：
	//发挥作用的条件：调用模板函数，模板函数参数是万能引用类型，模板函数负责转发。
	//std::forward的能力就是按照参数本来的类型转发
	//对std::forward函数的两种理解：
	//(1)实参如果原来是左值,到了形参中还是左值，forward是按照形参原来的类型处理，所以std::forward之后还是个左值。
	//(2)实参如果原来是个右值，到了形参中便成了左值，forward是按照形参原来的类型处理，所以
	//std::forward之后就是个右值。所以，这里看起来forward有强制把左值转成右值的能力，所以forward
	//其实只对原来是右值的情况有用。

	//forward的能力就是保持原始实参的类型(左值还是右值)

	//四、std::move和std::forward的区别
	//forward是强制把一个左值转成一个右值。但是如果你实参就是左值，那我forward啥也不干。
	//move:无条件强制类型转换。

	//五：再谈万能引用
	//万能引用并不是一种新的引用类型。
	//但是万能引用的概念是有意义的



	return 0;
}

