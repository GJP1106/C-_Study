// 6-12.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <future>

#include <windows.h>
using namespace std;

//#define __WINDOWSJQ__
//本类用于自动释放window下的临界区，防止忘记LeaveCriticalSection导致死锁情况的发生，类似于c++11中的std::lock_guard<std::mutex>
class CWinLock {   //叫RAII类，（Resource Acquisition is initialization）中文“资源获取即初始化”
public:
	CWinLock(CRITICAL_SECTION *pCritmp) {
		m_pCritical = pCritmp;
		EnterCriticalSection(m_pCritical);
	}
	~CWinLock() {
		LeaveCriticalSection(m_pCritical);
	}

private:
	CRITICAL_SECTION *m_pCritical;
};
#ifdef  __WINDOWSJQ__
CRITICAL_SECTION mywinsec;   //windows中的临界区，非常类似于c++11中的mutex
#endif //  __WINDOWSJQ__
class A {
public:
	//把收到的消息(玩家命令)写到一个队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRecvQueue执行，插入一个元素" << i << endl;
#ifdef __WINDOWSJQ__
			//EnterCriticalSection(&mywinsec); //进入临界区
			//EnterCriticalSection(&mywinsec); //进入临界区
			CWinLock wlock(&mywinsec);
			msgRecvQueue.push_back(i);   //假设这个数字i就是我收到的命令，我直接弄到消息队列里边来；
			//LeaveCriticalSection(&mywinsec);  //离开临界区
			//LeaveCriticalSection(&mywinsec);  //离开临界区
#else
			my_mutex.lock();
			//my_mutex.lock();
			std::chrono::milliseconds timeout(100);  //100毫秒
			if (my_mutex.try_lock_for(timeout)) {   //等待100毫秒来尝试，获取锁
				msgRecvQueue.push_back(i);
				my_mutex.unlock();
			}
			else {
				std::chrono::milliseconds sleeptime(100);
				std::this_thread::sleep_for(sleeptime);
			}
			//msgRecvQueue.push_back(i);   //假设这个数字i就是我收到的命令，我直接弄到消息队列里边来；
			my_mutex.unlock();
			//my_mutex.unlock();
#endif // __WINDOWSJQ__
		}
		return;
	}
	bool outMsgLULProc(int &command) {
#ifdef __WINDOWSJQ__
		EnterCriticalSection(&mywinsec);
		if (!msgRecvQueue.empty()) {
			//消息不为空
			int command = msgRecvQueue.front();  //返回第一个元素，但不检查元素是否存在
			msgRecvQueue.pop_front();   //移除第一个元素，但不返回
			LeaveCriticalSection(&mywinsec);
			return true;
	    }
		LeaveCriticalSection(&mywinsec);
#else
		my_mutex.lock();
		if (!msgRecvQueue.empty()) {
			//消息不为空
			int command = msgRecvQueue.front();  //返回第一个元素，但不检查元素是否存在
			msgRecvQueue.pop_front();   //移除第一个元素，但不返回
			my_mutex.unlock();
			return true;
		}
		my_mutex.unlock();
#endif // __WINDOWSJQ__

		
		
		return false;
	}
	//把数据从消息队列中取出的线程
	void outMsgRecvQueue() {
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
	}
	A() {
#ifdef  __WINDOWSJQ__
		InitializeCriticalSection(&mywinsec);   //用临界区之前要先初始化
#endif //  __WINDOWSJQ__

	}
#if 0
	void testfunc1() {
		std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
		testfunc2();   //会崩溃 加了两次锁，只要lock超过1次就会报异常
	}

	void testfunc2() {
		std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
	}
#endif

private:
	std::list<int> msgRecvQueue;  //容器(消息队列)，专门用于代表玩家给咱们发送过来的命令。
	//std::mutex my_mutex; //创建了一个互斥量
	//std::recursive_mutex my_mutex;  //递归的独占互斥量
	std::timed_mutex my_mutex;
};


int main()
{
	//一、window临界区
	//二、多次进入临界区实验
	//在同一个线程中(不同线程就会卡住等待)中，window中的“相同临界区变量”代表的临界区的进入可以被多次进入
	//但是你调用了几次EnterCriticalSection就要有几次LeaveCriticalSection
	//而在c++11中不允许在同一个线程中lock同一个互斥量多次，否则会报异常

	//三、自动析构技术
	//std::lock_guard<std::mutex>

	//四、recursive_mutex递归的独占互斥量
	//std::mutex  独占互斥量，自己拿到锁时别人lock不了；
	//recursive_mutex：递归的独占互斥量：允许同一个线程，同一个互斥量多次被.lock()，效率上比mutex更低。
	    //recursive_mutex也有lock，也有unlock
	       //考虑代码是否有优化空间。
	   //递归次数据说有限制

	//五、带超时的互斥量std::timed_mutex和std::recursive_timed_mutex
	//std::timed_mutex:带超时功能的独占互斥量
	    //try_lock_for()   :等待一段时间，如果我拿到了锁或者等待超过时间未拿到锁，那么就走下来；
	      
	    //try_lock_unti() :参数是一个未来的时间点，在这个未来的时间没到的时间内，如果拿到了锁，那么就走下来
	                          //如果时间到了，没拿到锁，程序流程也走下来
	//std::recursive_timed_mutex:带超时功能的递归独占互斥量(允许同一个线程多次获取这个互斥量)

	A myobja;
	thread myoutnMsgObj(&A::outMsgRecvQueue, &myobja);   //第一个参数是 引用，才能保证线程里用的是同一个对象
	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myoutnMsgObj.join();
	myInMsgObj.join();

	return 0;
}

