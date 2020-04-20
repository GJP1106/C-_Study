// 6-8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <list>
using namespace std;

class A {
public:
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

			//wait()用来等一个东西
			//如果第二个参数lambda表达式返回值是true,那么wait()直接返回；
			//如果第二个参数lambda表达式返回值是false，那么wait()将解锁互斥量，并堵塞到本行
			     //那堵塞到什么为止呢？堵到其他某个线程调用notify_one()成员函数为止；
			//如果没有第二个参数：m_condition.wait(sbguard)：那么就跟第二个参数lambda表达式返回false效果一样
			     //wait()将解锁互斥量，并堵塞到本行。
			//当其他线程用notify_one()将本wait(原来是睡着或者堵塞)的状态唤醒后，wait就开始恢复干活了，恢复后wait干什么活?
			   //a)wait()不断的尝试重新获取互斥量锁，如果获取不到，那么流程就卡在wait这里等着获取，获取到了锁，那么wait就继续执行b
			   //b)上锁(实际上获取到锁就等于上了锁)
			       //b.1)如果wait有第二个参数(lambda)，就判断这个lambda表达式，如果表达式为false，那么wait又对这个互斥量解锁，然后又休眠在这里，等待再次被notify_one唤醒
			       //b.2)如果表达式为true，则wait返回，流程继续走下来(此时互斥锁被锁着)
			       //b.3)如果wait没有第二个参数，则wait返回，流程走下来
			m_condition.wait(sbguard, [this] {  //一个lambda就是一个可调用对象(函数)
				if (!msgRecvQueue.empty()) {
					return true;
				}
				return false;
			});
			//流程只要走到这里来，这个互斥锁一定是锁着的，同时msgRecvQueue至少是由一个元素的
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			cout << "outMsgRecvQueue()执行结束，取出一个元素" << command << "thread Id:" << std::this_thread::get_id() <<endl;
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
	//一、条件变量std::condition_varible、wait()、nofify_one() 只能通知一个线程
	//线程A:等待一个条件满足
	//线程B:专门往消息队列中扔消息(数据)
	//std::condition_varible实际上是一个类，是一个和条件相关的一个类，说白了就是等待一个条件达成。
	//这个类是需要和互斥量来配合工作，用的时候我们要生成这个类的对象;
#if 0
	A myobja;
	thread myoutnMsgObj(&A::outMsgRecvQueue, &myobja);   //第一个参数是 引用，才能保证线程里用的是同一个对象
	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myoutnMsgObj.join();
	myInMsgObj.join();
#endif

	//二、上述代码深入思考

	//三、notify_all()
	A myobja;
	thread myoutnMsgObj(&A::outMsgRecvQueue, &myobja);   //第一个参数是 引用，才能保证线程里用的是同一个对象
	thread myoutnMsgObj1(&A::outMsgRecvQueue, &myobja);
	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myInMsgObj.join();
	myoutnMsgObj.join();
	myoutnMsgObj1.join();
	

	return 0;
}
