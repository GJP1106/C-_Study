
//#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_set>

using namespace std;

namespace _nmsp1
{
	//一：算法概述：理解为函数模板(全局函数/全局函数模板)；
	//比如：查找，排序等等；数十甚至上百个算法；数量不断上涨；
	//算法的前两个形参的类型，一般都是迭代器类型，用来表示容器中的元素的一个区间；



	void func()
	{
		list<int> mylist = { 100,200,300 };
		list<int>::iterator iterbg = mylist.begin();
		list<int>::iterator itered = mylist.end(); //最后一个元素的下一个位置；
		//算法名(iterbg,itered) ，传递进去的应该是 一个前闭后开的区间[ begin()  ,end() )；
		//前闭后开的区间的好处一般认为有两条：
		//a)算法只要判断迭代器只要等于后边这个开区间，那么就表示迭代结束；
		//b)如果第一个形参等于第二个形参，也就是itergb == itered，那么就表示是个空区间；
		//算法：是一种搭配迭代器来使用的全局函数；算法跟具体容器没关联，只跟迭代器有关联；只需要根据迭代器来开发算法，不需要理会具体容器，从而增加了算法代码开发的弹性；
		//算法这种泛型编程方式，增加灵活性，但是缺失了直观性；某些数据结构(某些容器的迭代器)和算法之间的兼容性也不是那么的好；
		//stl中到底有哪些算法：《c++标准库 第二版》 11.2.2 “算法分门别类”；建议大家了解，做概览；



		return;
	}
}
namespace _nmsp2
{
	//二：算法内部一些处理
	//算法会根据传递进来的迭代器来分析出迭代器种类（五种之一），不同的种类的迭代器，算法会有不同的处理，要编写不同的代码来 应对；
	//这种编写不同的代码来处理不同种类的迭代器，能够直接影响到算法的执行效率；（效率是一个很重要的指标）
	//这也就是stl内部为什么要给这些迭代器做一个分类的目的：
	void func()
	{

	}
}
namespace _nmsp3
{
	//三：一些典型算法使用范例
	//算法头文件要包含进来：#include <algorithm>
	//（3.1）for_each：未归类知识点8节
	//template<class InputIterator,class Function>
	//Function for_each(InputIterator first, InputIterator last, Function f)
	//{
	//	for (; first != last; ++first) //10,20,30,40,50
	//	{
	//		f(*first);
	//	}
	//	return f;
	//}
	//这段代码表明2个问题：
	//a)算法区分迭代器种类，这个种类决定着某些算法的效率；InputIterator
	//b)f(*first); 这是个可调用对象； 未归类知识点1节，7,8节


	//distance()

	void myfunc(int i) //参数类型是容器中的元素类型
	{
		cout << i << endl;
	}

	void func()
	{
		vector<int> myvector = { 10,20,30,40,50 };
		//for_each工作原理：不断的迭代给进来的两个迭代器之间的元素，然后拿到这个元素，以这个元素为实参来调用myfunc(元素);
		for_each(myvector.begin(), myvector.end(), myfunc); //myfunc是可调用对象：未归类知识点7节


	}
}
namespace _nmsp4
{
	//三：一些典型算法使用范例
	//当有成员函数和全局函数（算法）同时存在时，优先考虑使用同名的成员函数，如果没有同名的成员函数，才考虑使用这些算法；
	//（3.2）find
	//（3.3）find_if：未归类知识点8节，讲过
	void func()
	{
		vector<int> myvector = { 10,20,30,40,50 };
		vector<int>::iterator finditer = find(myvector.begin(), myvector.end(), 400);
		if (finditer != myvector.end()) //判断是否等于find的第二个参数，等于就没找到，不等于就找到了
		{
			//找到了
		}
		else
		{
			//没找到
		}

		map<int, string> mymap;
		mymap.insert(std::make_pair(1, "老王"));
		mymap.insert(std::make_pair(2, "老李"));
		auto iter = mymap.find(2);  //优先使用自己的成员函数
		if (iter != mymap.end())
		{
			//找到
			printf("编号为%d，名字为%s\n", iter->first, iter->second.c_str());
		}
		//find_if演示
		auto result = find_if(myvector.begin(), myvector.end(), [](int val) //lambda表达式也是可调用对象
		{
			if (val > 15)
				return true;  //停止遍历
			return false;
		});
		if (result == myvector.end())
		{
			cout << "没找到" << endl;
		}
		else
		{
			cout << "找到了，结果为：" << *result << endl;
		}
	}
}
namespace _nmsp5
{
	//三：一些典型算法使用范例
	//（3.4）sort
	bool myfunc(int i, int j)
	{
		//return i < j;  //从小到大排序
		return i > j; //从大到小排序
	}
	class A
	{
	public:
		bool operator()(int i, int j)
		{
			return i > j;
		}
	};

	void func()
	{
		vector<int> myvector = { 50,15,80,30,46 };
		//sort(myvector.begin(), myvector.end()); //缺省按照从小到的顺序排列的，15,30,46,50,80
		//sort(myvector.begin(), myvector.begin() + 3);//只有前三个元素参与排序：15,50,80， 30,46
		//若要从大到小排序，我们可以写自定义的比较函数，这个函数是返回bool；
		//sort(myvector.begin(), myvector.end(), myfunc);
		/*A mya;
		sort(myvector.begin(), myvector.end(), mya);
		for (auto iter = myvector.begin(); iter != myvector.end() ;++iter)
		{
			cout << *iter << endl;
		}*/

		//试试list
		list<int> mylist = { 50,15,80,30,46 };
		//sort(mylist.begin(), mylist.end(), myfunc); //list不支持sort算法
		mylist.sort(myfunc);
		for (auto iter = mylist.begin(); iter != mylist.end(); ++iter)
		{
			cout << *iter << endl;
		}

		map<int, string> mymap;
		mymap.insert(std::make_pair(50, "老王"));
		mymap.insert(std::make_pair(15, "老李"));
		mymap.insert(std::make_pair(80, "老赵"));
		//sort(mymap.begin(), mymap.end()); //不让排序编译报错；

		unordered_set<int> myset = { 50,15,80,30,46 };
		//sort(myset.begin(), myset.end());//不让排序编译报错


	}

}
int main()
{
	//_nmsp1::func();		
	//_nmsp2::func();	
	//_nmsp3::func();
	//_nmsp4::func();
	_nmsp5::func();
	return 1;
}



