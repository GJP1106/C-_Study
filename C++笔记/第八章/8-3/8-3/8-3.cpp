#include <iostream>
#include <queue>
#include <forward_list>
#include <map>
#include <unordered_set>
using namespace std;

namespace _nmsp1
{
	//一：deque和stack：顺序容器
	//deque：双端队列dobule-ended queue（双向开口）。相当于动态数组；头部和尾部插入与删除数据都很快；
	   //如果往中间插入元素，那么可能会涉及到移动其他元素，效率上会比较低；
	   //分段连续内存；
	// stack（堆栈/栈）：后进先出 ,只有一个开口，只要把deque左边开口封死，我们就可以认为变成了一个stack;
	 //和vector的区别：vector支持从中间插入中间删除，虽然效率不算高；
	 //stack只支持从栈顶放入元素以及从栈顶取出（删除）元素，这种特性是stack容器设计初衷；
	//deque实际上是包含着stack功能；

	//二：queue：队列，这是个普通队列：先进先出,比较基本的数据结构；
	  //deque也包含着queue功能的；

	//三：list
	//双向链表，不需要各个元素之间的内存连在一起；查找效率不突出，在任意位置插入和删除元素非常迅速；
	//面试中，vector和list的区别：
	//a)vector类似于数组，他的内存空间是连续的，list双向链表，内存空间并不连续(至少不要求内存空间是连续的)；
	//b)vector从中间或者开头插入元素效率比较低；但是list插入元素效率非常高；
	//c)vector当内存不够时，会重新找一块内存，对原来内存对象做析构，在新找的内存中重新构建对象；
	//d)vector能够高效的随机存取，而list做不到这一点；比如我要访问第5个元素；
	 //vector内存连续，他一下就能定位到第五个元素；
	  //list，如何找第5个元素；我要沿着一个链一直找下去，直到找到第五个元素。所有说vector随机存取比较快，而list随机存取比较慢；


	class A
	{
	public:
		int m_i;
		A(int tmpv) :m_i(tmpv) //构造函数
		{
			cout << "A::A()构造函数执行" << endl;
		}
		A(const A& tmpA)
		{
			m_i = tmpA.m_i;
			cout << "A::A()拷贝构造函数执行" << endl;
		}
		~A()
		{
			cout << "A::~A()析构函数执行" << endl;
		}
	};
	void func()
	{
		deque<A> mydeque;
		for (int i = 0; i < 5; ++i)
		{
			cout << "--------------begin----------------" << endl;
			mydeque.push_front(A(i));
			cout << "--------------end----------------" << endl;
		}
		for (int i = 0; i < 5; ++i)
		{
			cout << "--------------begin2----------------" << endl;
			mydeque.push_back(A(i));
			cout << "--------------end2----------------" << endl;
		}
		for (int i = 0; i < mydeque.size(); ++i)
		{
			cout << "下标为" << i << "的元素的m_i值为: " << mydeque[i].m_i << endl;
			printf("对象mydeque[%d]的地址为%p \n", i, &mydeque[i]);
		}


		return;
	}
}
namespace _nmsp2
{
	//四：其他
	//（4.1）forward_list:c++11新增加的：单向链表（受限list）,但节省了内存，尤其是元素多的时候，节省的内存非常可观；

	class A
	{
	public:
		int m_i;
		A(int tmpv) :m_i(tmpv) //构造函数
		{
			cout << "A::A()构造函数执行" << endl;
		}
		A(const A& tmpA)
		{
			m_i = tmpA.m_i;
			cout << "A::A()拷贝构造函数执行" << endl;
		}
		~A()
		{
			cout << "A::~A()析构函数执行" << endl;
		}
	};

	void func()
	{
		forward_list<A> myforlist;
		myforlist.push_front(A(1));


	}
}
namespace _nmsp3
{
	//四：其他
	//（4.2）set / map:关联容器；内部实现的数据结构多为红黑树；
	  //我们往这种容器中保存数据时，不需要我们指定数据位置，这种容器会自动的给你加入的元素根据一个算法安排一个位置；
	//map：每个元素有两项，是个键/值（key/value)；一般都是通过key找value；(查找特别迅速，插入的速度可能略慢)
	//通过key找value特别快；不允许key相同，如果你非要让key相同，你要采用multimap

	//set不存在键值对的说法；每个元素就是一个value；元素值不能重复，如果想重复，那么可以采用multiset

	//总结：
	//a)插入时，因为容器要给你找一个适当的插入位置，所以插入的速度可能会慢一点；
	//b)查找的速度特别快；
	//如果大家需要快速找到某个元素的时候，我们重点就要考虑使用map,set,multimap,multiset;



	void func()
	{
		map<int, string> mymap; //保存键值对的容器
		mymap.insert(std::make_pair(1, "老王"));
		mymap.insert(std::make_pair(2, "老李"));
		mymap.insert(pair<int, string>(3, "老赵"));
		mymap.insert(pair<int, string>(3, "老白"));
		auto iter = mymap.find(3);
		if (iter != mymap.end())
		{
			//找到了
			printf("编号为%d，名字为%s\n", iter->first, iter->second.c_str());
		}





	}
}
namespace _nmsp4
{
	//（4.3）unordered_set，unordered_multiset等unordered_map,unordered_multimap
	//以往hash_set,hash_map,hash_multiset,hash_multimap老版本容器，不推荐使用了；用unordered开头的容器取代了；
	//增加篮子（桶子）数量的目的就是为了防止某个篮子后边挂的元素太多，从而影响查找速度；
	//自动指定元素位置，不需要使用者手工干预
	//蓝色数量不少于元素数量

	void func()
	{
		unordered_set<int> myset;
		cout << "bucket_count() = " << myset.bucket_count() << endl; //8
		for (int i = 0; i < 8; ++i) //0..7
		{
			myset.insert(i);
		}
		cout << "bucket_count() = " << myset.bucket_count() << endl; //8
		myset.insert(8);
		cout << "bucket_count() = " << myset.bucket_count() << endl; //扩容到64
		cout << "max_bucket_count() = " << myset.max_bucket_count() << endl; //536870911

		printf("所有篮子（本容器）里有的元素数量为%d\n", myset.size());
		for (int i = 0; i < myset.bucket_count(); ++i)
		{
			printf("第%d个篮子里有的元素数量为%d\n", i, myset.bucket_size(i)); //从0开始
		}
		auto pmyfind = myset.find(5); //查找比较费时，如果容器里有find，尽量用容器里的，因为有全局find；如果容器本身没有自己的find才考虑用全局的find();
		if (pmyfind != myset.end())
		{
			cout << "元素5存在于容器中" << endl;
		}
		if (find(myset.begin(), myset.end(), 5) != myset.end()) //全局的find
		{
			cout << "元素5存在于容器中" << endl;
		}

		unsigned char * src = (unsigned char *)malloc(10);
		memset(src, 1, 10);
		for (int i = 0; i < 10; i++) {
			*src = i;
			src++;
		}
		for (int i = 0; i < 10; i++) {
			printf("%d\n", *src);
			src += 1;
		}

	}
}
int main()
{
	//_nmsp1::func();	
	//_nmsp2::func();
	//_nmsp3::func();
	_nmsp4::func();
	return 1;
}



