// 6-4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <list>
using namespace std;

vector<int> g_v = { 1,2,3 };  //共享数据，只读

//线程入口函数
void myprint(int num) {
	//cout << "myprint线程开始执行了，线程编号:" << num << endl;
	cout << "id为" << std::this_thread::get_id() << "的线程 打印g_v值" << g_v[0] << g_v[1] << g_v[2] << endl;
	return;
}

class A {
public:
	//把收到的消息(玩家命令)写到一个队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRecvQueue执行，插入一个元素" << i << endl;
			msgRecvQueue.push_back(i);   //假设这个数字i就是我收到的命令，我直接弄到消息队列里边来；
		}
	}
	//把数据从消息队列中取出的线程
	void outMsgRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			if (!msgRecvQueue.empty()) {
				//消息不为空
				int command = msgRecvQueue.front();  //返回第一个元素，但不检查元素是否存在
				msgRecvQueue.pop_front();   //移除第一个元素，但不返回
				//这里就考虑处理数据
			}
			else {
				//消息队列为空
				cout << "outMsgRecvQueue()执行，但目前消息队列为空" << i << endl;
			}
			cout << "inMsgRecvQueue执行结束" << i << endl;
		}
	}
private:
	std::list<int> msgRecvQueue;  //容器(消息队列)，专门用于代表玩家给咱们发送过来的命令。
};


int main()
{
	//一、创建和等待多个线程
#if 0
	vector<thread> mythreads;
	//创建10个线程，线程入口函数统一使用myprint
	//a)多个线程执行顺序是乱的，跟操作系统内部对线程的运行调度机制有关；
	//b)主线程等待所有子线程运行结束，最后主线程结束，老师推荐这种join的写法，更容易写出稳定的程序；
	//c)咱们把thread对象放入到容器里管理，看起来像个thread对象数组，这对我们一次创建大量的线程并对大量线程进行管理很方便
	for (int i = 0; i < 10; i++) {
		mythreads.push_back(thread(myprint, i));   //创建10个线程，同时这10个线程已经开始执行
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter) {
		iter->join();
	}
#endif

	//二、数据共享问题分析
	//(2.1)只读的数据：是安全稳定的，不需要特别什么处理手段。直接读就可以；
	//(2,2)有读有写：2个线程写，8个线程读，如果代码没有特别的处理，那程序肯定崩溃
	//最简单的不崩溃处理，读的时候不能写，写的时候不能读。2个线程不能同时写，8个线程不能同时读；
	//假如写的动作分10小步；由于任务切换，导致各种诡异事情发生(最可能的诡异事情还是崩溃)；
	//(2.3)其他案例
	//数据共享；订火车票

	//三、共享案例的保护案例代码
	//网络游戏服务器。两个自己创建的线程，一个线程收集玩家命令(用一个数字代表玩家发来的命令)，并把命令数据写到一个队列中。
	                                    //另外一个线程 从队列中取出玩家发送来的命令，解析，然后执行玩家需要的动作；

	//vector, list, list跟vector. list:频繁的按顺序插入和删除数据时效率高。vector容器随机的插入和删除数据效率高。
	
	//准备用成员函数作为线程函数的方法来写线程；
	//代码化解决问题：老师 引入一个C++解决多线程保护共享数据问题的第一个概念"互斥量"，往脑袋里记这个词；
	A myobja;
	thread myoutnMsgObj(&A::outMsgRecvQueue, &myobja);   //第一个参数是 引用，才能保证线程里用的是同一个对象
	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);  

	myoutnMsgObj.join();
	myInMsgObj.join();

	cout << "I love china" << endl;

	return 0;
}

