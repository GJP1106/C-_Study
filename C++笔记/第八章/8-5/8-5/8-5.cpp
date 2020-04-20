// 8-5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <array>
using namespace std;

namespace _nmsp1 {

	//一、迭代器基本概念:二章九节
	//迭代器到底是个啥：迭代器是一个“可遍历stl容器全部或者部分元素”的对象（行为类似于指针的对象）
	   //迭代器用来表现容器中的某一个位置；迭代器紧密依赖于容器，迭代器是由容器来提供的，也就是说，一般来讲，是容器里边定义着迭代器的具体类型细节；
	   //大家理解成迭代器是和容器紧密相关(绑定)
	//int *p, p = ...  printf(*p); iter 指向容器的元素； *iter 打印迭代器所指向容器中的元素内容；

	void func() {
		vector<int> iv = { 100,200,300 };  //定义一个容器
		for (vector<int>::iterator iter = iv.begin(); iter != iv.end(); ++iter) {
			cout << *iter << endl;
		}

		return;
	}
}

namespace _nmsp2 {

	//二、迭代器的分类：迭代器是分种类的；
	//分类的依据:依据是 迭代器的移动特性以及这个迭代器上能够做的操作;
	//迭代器行为如指针，到处跳，表示一个位置，我们一般分类是依据他的跳跃能力，每个分类是一个对应的struct定义：
	//a)输出型迭代器：(OutPut iterator)
	//struct output_iterator_tag;
	//b)输入型迭代器：(Input iterator)
	//struct input_iterator_tag
	//c)前向迭代器(Forward iterator)
	//struct forward_iterator_tag;
	//d)双向迭代器(Bidirectional iterator)
	//struct bidirectional_iterator_tag;
	//e)随机访问迭代器(Random_access iterator)
	//struct random_access_iterator_tag;

	//这些分类(结构)都有继承关系的

	//vector<int>::iterator iter = ....
	//list<int>::iterator iter = ...
	//大多数容器里边都有一个::iterator迭代器类型；并不是所有容器里都有迭代器；比如stack,queue这种容器就不提供迭代器；

	//完善迭代器能力：
	//a)输出型迭代器 struct output_iterator_tag; 一步一步能往前走，并且能够通过这个种类的迭代器来改写容器中的数据；
	//b)输入型迭代器：struct input_iterator_tag; 一次一个以向前的方向来读取元素，按照这个顺序一个一个返回元素值；
	//c)前向迭代器：struct forward_iterator_tag;因为继承自从Input迭代器，因此它能以向前的方向来读取元素，并且读取时提供额外保证；
	//d)双向迭代器：struct bidirectional_iterator_tag：在前向迭代器基础之上增加了往回（反向）迭代，也就是迭代位置可以回退，新增加如下操作：
	//e)随机访问迭代器：struct random_access_iterator_tag：在双向迭代器基础上又增加了所谓的随机访问能力：也就是增减某个偏移量，能够计算距离，还支持一些关系运算等等；


    //验证迭代器所属种类的代码：
	//如下这些_display_category（）是重载函数；
	void _display_category(random_access_iterator_tag mytag)
	{
		cout << "random_access_iterator_tag" << endl;
	}

	void _display_category(bidirectional_iterator_tag mytag)
	{
		cout << "bidirectional_iterator_tag" << endl;
	}

	void _display_category(forward_iterator_tag mytag)
	{
		cout << "forward_iterator_tag" << endl;
	}

	void _display_category(output_iterator_tag mytag)
	{
		cout << "output_iterator_tag" << endl;
	}

	void _display_category(input_iterator_tag mytag)
	{
		cout << "input_iterator_tag" << endl;
	}

	template <typename T>
	void display_category(T ite) {   //T的类型编译器能推导出来
		cout << "---------------begin-------------------" << endl;

		//整个这个类型叫 过滤器（萃取机），用来获取T迭代器类型的种类；
		typename iterator_traits<T>::iterator_category cagy; //相当于获取迭代器种类；
		_display_category(cagy); //编译器会挑选一个最适合的参数的重载_display_category
		cout << "typeid(ite).name() = " << typeid(ite).name() << endl; //第三章10节讲rtti时

		cout << "---------------end-------------------" << endl;
	};


	void func() //主函数：
	{
		display_category(array<int, 100>::iterator());  //这种 类型()：代表产生 一个临时对象；
		display_category(vector<int>::iterator());
		display_category(list<int>::iterator());
		display_category(map<int, int>::iterator());
		display_category(set<int>::iterator());
	}
}

namespace _nmsp3
{
	void func()
	{
		vector<int> iv = { 100,200,300 };
		for (auto iter = iv.begin(); iter != iv.end(); ++iter)
		{
			cout << *iter << endl;
			*iter = 6;
		}
		int abc;
		abc = 0;

	}
}

int main()
{
	//_nmsp1::func();
	//_nmsp2::func();
	_nmsp3::func();

	return 0;
}