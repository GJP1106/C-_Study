

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_set>
#include <functional>
#include <queue>

using namespace std;
//
namespace _nmsp1
{
	//一：函数对象（function object）/仿函数（functors）回顾
	//函数对象 在stl中，一般都是和算法配合来使用,从而实现一些特定的功能；也就是说,这些函数对象主要用来服务于算法；
	//函数名(参数列表)
	//未归类知识点，第一，七，八；

	class A
	{
	public:
		bool operator()(int i, int j)
		{
			return i > j; //从大到小排序
		}
	};


	void func()
	{
		vector<int> myvector = { 50,15,80,30,46 };
		A mya;
		sort(myvector.begin(), myvector.end(), mya);

		for (auto iter = myvector.begin(); iter != myvector.end(); ++iter)
		{
			cout << *iter << endl;
		}


		return;
	}
}
namespace _nmsp2
{
	//二：标准库中定义的函数对象
	//标准库中也给我们提供了很多可以现成拿来使用的函数对象，使用它们之前，要包含一个头文件 functional
	//函数对象分类：
	//a)算术运算类 6
	//b)关系运算类 6
	//c)逻辑运算类 3
	//d)位运算类 3

	//三：标准库中定义的函数对象范例

	class A
	{
	public:
		bool operator()(int i, int j)
		{
			return i > j; //从大到小排序
		}
	};

	void func()
	{
		//plus<int>(); //加圆括号是生成一个临时对象 ，就是个可调用对象；
		//plus<int> myplus;

		vector<int> myvector = { 50,15,80,30,46 };
		//A mya;  //自定义的函数对象
		//sort(myvector.begin(), myvector.end(), mya); 
		//sort(myvector.begin(), myvector.end(), greater<int>()); // greater<int>()产生临时对象,称呼为系统定义的函数对象；
		sort(myvector.begin(), myvector.end(), less<int>());





		for (auto iter = myvector.begin(); iter != myvector.end(); ++iter)
		{
			cout << *iter << endl;
		}



	}
}

int main()
{
	//_nmsp1::func();			
	_nmsp2::func();

	return 1;
}


