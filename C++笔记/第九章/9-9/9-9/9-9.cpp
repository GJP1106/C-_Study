// 9-9.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <ctime>
using namespace std;

std::vector<std::function<bool(int)>> gv;  //全局变量，每个元素都是个function，每个function给进去的int，返回值是bool

void myfunc() {
	srand((unsigned)time(NULL));
	//int tmpvalue = rand() % 6;  //产生一个0-5之间的随机数
	static int tmpvalue = 4;
	gv.push_back(
		//[&](int tv) {  //按引用会出问题
		[](int tv) {
		cout << tmpvalue << endl;
		if (tv % tmpvalue == 0)  //如果tv是tmpvale的倍数
		{
			return true;
		}
		return false;
	}
	);
	tmpvalue++;
}

class AT
{
public:
	int m_tmpvalue = 7;
#if 0
	void addItem() {
		gv.push_back(
			//我们会认为这个[=]是按值捕获，使用我们能够访问成员变量m_tmpvalue
			//所以我们顺理成章的认为，这里这个lambda表达式是所使用的m_tmpvalue是按值捕获的
			[=](auto tv) {     //按值捕获 =等价于有this
			cout << m_tmpvalue << endl;
			if (tv % m_tmpvalue == 0)  //如果tv是tmpvale的倍数
			{
				return true;
			}
			return false;
		}
		);
	}
#endif
#if 0
	void addItem() {
		auto tmpcopvalue = m_tmpvalue;
		gv.push_back(
			//我们会认为这个[=]是按值捕获，使用我们能够访问成员变量m_tmpvalue
			//所以我们顺理成章的认为，这里这个lambda表达式是所使用的m_tmpvalue是按值捕获的
			[tmpcopvalue](auto tv) {     //按值捕获 =等价于有this
			cout << tmpcopvalue << endl;
			if (tv % tmpcopvalue == 0)  //如果tv是tmpvale的倍数
			{
				return true;
			}
			return false;
		}
		);
	}
#endif

	void addItem() {
		gv.push_back(
			//我们会认为这个[=]是按值捕获，使用我们能够访问成员变量m_tmpvalue
			//所以我们顺理成章的认为，这里这个lambda表达式是所使用的m_tmpvalue是按值捕获的
			[abc = m_tmpvalue](auto tv) {     //按值捕获 =等价于有this
			cout << abc << endl;
			if (tv % abc == 0)  //如果tv是tmpvale的倍数
			{
				return true;
			}
			return false;
		}
		);
	}
};

int main()
{
	//一、捕获列表中的&：捕获外部作用域中所有变量，并作为引用在lambda表达式中使用。
	//按照引用这种捕获方式，会导致lambda表达式包含绑定到局部变量的引用。
#if 0
	myfunc();
	cout << gv[0](10) << endl;  //非法调用，会出现不可预料的问题，lambda按值捕获就可以
#endif
	//二、形参列表可以使用auto
	//c++14允许在lambda表达式的形参列表中使用auto
	//引用捕获方式超出范围的情形也叫做"引用悬空"；

	//三、成员变量的捕获问题
#if 0

	AT *pat = new AT();
	pat->addItem();
	cout << gv[0](10) << endl; 
	//结论：lambda表达式的执行正确与否，取决于pat对象是否存在，只有pat对象存在，这个lambda表达式执行才是正确；
	delete pat;
#endif

	//我们要明确一点，捕获这个概念，只针对于在创建lambda表达式的作用域内可见的 非静态 局部变量（包括形参）
	//m_tmpvalue并不是非静态局部变量。m_tmpvalue是AT类的成员变量，成员变量是不能被捕获到的。
	//this：指向对象本身;所以这里你用[=]捕获的是this指针值；

	//四、广义lambda捕获：c++14

	//五、静态局部变量：捕获这种事，是不包括静态局部变量的，也就是说，静态局部变量是不可能被捕获的；
	//但是可以在lambda中使用；另外，静态局部变量是保存在静态存储区，它的有效期一直到程序结束。
	//但是这种对static变量的使用有点类似于按 引用 捕获这种效果
	//myfunc();
	//gv[0](10);  //5
	//myfunc();
	//gv[0](10); //6
	//gv[1](10);  //6
	myfunc();
	myfunc();
	gv[0](10);
	gv[0](10);

	//总结：


	return 0;
}

