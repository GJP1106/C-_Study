// 6-12.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <future>
#include <atomic>

#include <windows.h>
using namespace std;

class A {

public:
	atomic<int> atm;
	A() {
		atm = 0;
		//auto atm2 = atm;  //这种定义时初始化操作不允许，显示“尝试引用已经删除的函数”编译器内部肯定把拷贝构造函数给干掉了用
		//atomic<int> atm3 = atm;  //不允许
		//load();  以原子方式读atomic对象的值
		//读
		//atomic<int> atm2(atm.load());  //允许
		//写
		atomic<int> atm2(atm.load());
		atm2.store(12);
		atm2 = 12;

	}
	
	std::unique_lock<std::mutex> rtn_unique_lock() {
		std::unique_lock<std::mutex> tmpguard(my_mutex);
		return tmpguard;   //从函数返回一个局部的unique_lock对象是可以的。三章14节讲解过移动构造函数
						   //返回这种局部对象tmpguard会导致系统生成临时unique_lock对象，并调用unique_lock的移动构造函数
	}
	//把收到的消息(玩家命令)写到一个队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRecvQueue执行，插入一个元素" << i << endl;

			std::unique_lock<std::mutex> sdguard(my_mutex);
			msgRecvQueue.push_back(i);   //假设这个数字i就是我收到的命令，我直接弄到消息队列里边来；

			//假如outMsgRecvQueue()正在处理一个事务，需要一段时间，而不是正卡在wait()那里等待你唤醒，那么此时这个notify_one这个调用也许就没效果。
			//m_condition.notify_one();  //我们尝试把wait()的线程唤醒，执行完这行，那么outMsgRecvQueue的wait将会被唤醒
										 //唤醒之后的事情后续研究
			//两个线程用notify_all
			m_condition.notify_all();

		}
		return;
	}
	bool outMsgLULProc(int &command) {
#if 0
		//双重锁定，双重检查
		if (!msgRecvQueue.empty()) {
			std::unique_lock<std::mutex> uniqueLock(my_mutex);
			//std::chrono::milliseconds dura(2000);  //1秒 = 1000毫秒
			//std::this_thread::sleep_for(dura);   //休息2秒

			if (!msgRecvQueue.empty()) {
				//消息不为空
				command = msgRecvQueue.front();  //返回第一个元素，但不检查元素是否存在
				msgRecvQueue.pop_front();   //移除第一个元素，但不返回
				return true;
			}
}
		return false;
#endif


	}
	//把数据从消息队列中取出的线程
	void outMsgRecvQueue() {
#if 0
		int command = 0;
		for (int i = 0; i < 100000; ++i) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				cout << "outMsgRecvQueue()执行,取出一个元素" << command << endl;
			}
			else {
				//消息队列为空
				cout << "outMsgRecvQueue()执行，但目前消息队列为空" << i << endl;
			}
			cout << "inMsgRecvQueue执行结束" << endl;
		}
#endif

		int command = 0;
		while (true) {
			std::unique_lock<std::mutex> sbguard(my_mutex);
			m_condition.wait(sbguard, [this] {  //一个lambda就是一个可调用对象(函数)
				if (!msgRecvQueue.empty()) {
					return true;
				}
				return false;
			});
			//流程只要走到这里来，这个互斥锁一定是锁着的，同时msgRecvQueue至少是由一个元素的
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			cout << "outMsgRecvQueue()执行结束，取出一个元素" << command << "thread Id:" << std::this_thread::get_id() << endl;
			sbguard.unlock();   //因为unique_lock的灵活性，所以我们可以随时的unlock解锁，以免锁住太长时间

		}
			}
private:
	std::list<int> msgRecvQueue;  //容器(消息队列)，专门用于代表玩家给咱们发送过来的命令。
	std::mutex my_mutex; //创建了一个互斥量
	std::mutex my_mutex2;
	std::condition_variable m_condition;  //生成一个条件对象
};


int main()
{
	//一、补充一些知识
	//(1.1)虚假唤醒:wait中要有第二参数(lambda)并且这个lambda中要正确判断要处理的公共数据是否存在
	//wait(),notify_one(),notify_all()
	//(1.2)atomic

	//二、浅谈线程池
	//(2.1)场景设想
	//服务器程序，-->客户端 ， 每来 一个客户端，就创建一个新线程为该客户提供服务。
	//a)网络游戏，2万玩家不可能给每个玩家创建个新线程，此程序写法在这种场景下不通。
	//b)程序稳定性问题：编写的代码中，偶尔创建一个线程这种代码，这种写法，就让人感到不安；
	//线程池：把一堆线程弄到一起，统一管理。这种统一管理调度，循环利用线程的方式，就叫线程池。
	//(2.2)实现方式
	//在程序启动时，我一次性的创建好一定数量的线程。10、8、100-200个等等，更让人放心，觉得程序代码更稳定；


	//三、线程创建数量谈
	//(3.1)线程开的数量极限问题，2000个线程基本就是极限，再创建线程就崩溃
	//(3.2)线程创建数量建议
	//a)采用某些技术开发程序；api接口提供商建议你
	//b)创建多线程完成业务：一个线程等于一条执行通路；

	//四、c++11多线程总结
	//window，linux
	  
	A myobja;
	thread myoutnMsgObj(&A::outMsgRecvQueue, &myobja);   //第一个参数是 引用，才能保证线程里用的是同一个对象
	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myoutnMsgObj.join();
	myInMsgObj.join();

	return 0;
}

