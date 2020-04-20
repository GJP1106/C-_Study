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
	//一：适配器基本概念：转接头
	//把一个既有的东西 进行适当的改造，比如增加点东西，或者减少点东西，就构成了一个适配器；
	//三种适配器：容器适配器，算法适配器，迭代器适配器。。。。

	//二：容器适配器（类模板）：本章三节学过双端队列deque;
	//（2.1）stack：堆栈，是属于阉割版的deque；
	//（2.2）queue：队列，是属于阉割版的deque；
	//。。。。。。

	//三：算法适配器（函数适配器） ：最典型的就是绑定器(binder)
	//（3.1）绑定器
	//老版本 bind1st,bind2nd；c++11，名字被修改为bind：未归类知识点第七节
	//https://en.cppreference.com/w/
	//http://www.cplusplus.com/

	class A
	{
	public:
		bool operator()(int i)
		{
			//return i > 40; //希望大于40的元素被统计
			return 40 < i;  //希望大于40的元素被统计
		}
	};

	void func()
	{
		vector<int> myvector = { 50,15,80,30,46,80 };
		//统计某个值出现的次数
		int cishu = count(myvector.begin(), myvector.end(), 80); //算法
		cout << cishu << endl;

		//A myobja;
		//cishu = count_if(myvector.begin(), myvector.end(), myobja);
		//cout << cishu << endl;

		//bind(less<int>(), 40, placeholders::_1);
									//less<int>的operator()的第一个参数绑定为40，那这样当调用less<int>()这个可调用对象时，
									 //第二个参数，就用这里的 placeholders::_1表示，在调用这个函数时，被传入的第一个参数所取代；
		//auto bf = bind(less<int>(), 40, placeholders::_1);
		//bf(19);

		cishu = count_if(myvector.begin(), myvector.end(), bind(
			less<int>(),  //临时对象
			40,
			placeholders::_1
		)
		);
		//a)bind:函数适配器中的绑定器；
		//b)less<int>()：是个函数对象（仿函数），这里是个临时对象
		//c)count_if：是个算法；
		cout << cishu << endl;

		return;
	}
}
namespace _nmsp2
{
	//四：迭代器适配器
	//（4.1）reverse_iterator：二章九节讲解过：反向迭代器；

	//五：总结


	void func()
	{
		vector<int> iv = { 100,200,300 };
		for (vector<int>::reverse_iterator riter = iv.rbegin(); riter != iv.rend(); ++riter)
		{
			cout << *riter << endl;
		}

	}
}

int main()
{
	//_nmsp1::func();
	_nmsp2::func();
	return 1;
}


