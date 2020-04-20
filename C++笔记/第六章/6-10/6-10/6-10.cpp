// 6-9.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <list>
#include <mutex>
#include <future>
using namespace std;

int mythread() {
    cout << "mythread() start " << "threadid = " << std::this_thread::get_id() << endl;
    std::chrono::milliseconds dura(5000);  //定义一个5秒的时间
    std::this_thread::sleep_for(dura);  //休息了一定时长
    cout << "mythread() end " << "threadid = " << std::this_thread::get_id() << endl;
    return 5;

}
int mythread1(int mypar) {
	cout << "mythread1() start " << "threadid = " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(5000);  //定义一个5秒的时间
	std::this_thread::sleep_for(dura);  //休息了一定时长
	cout << "mythread1() end " << "threadid = " << std::this_thread::get_id() << endl;
	return 5;
}
void mythread2(std::shared_future<int> &tmpf) {
	cout << "mythread2() start " << "threadid = " << std::this_thread::get_id() << endl;
	auto result = tmpf.get();
	//result = tmpf.get();  //为什么第二次get这个future我们会得到一个异常，主要是因为get函数的设计，是一个移动语义
	cout << "mythread2() end " << "result = " << result << endl;
	return;
}

std::atomic<int> g_c = 0;
//int g_mycount = 0;  //定义一个全局量
std::atomic<int> g_mycount = 0;  //我们封装了一个类型为int的对象(值)；
std::atomic<bool> g_ifend = false; //线程退出标记，这里是原子操作，防止读和写乱套
std::mutex g_my_mutex;

void mythread3() {
	for (int i = 0; i < 1000000; i++) {
		//g_my_mutex.lock();
		g_mycount++;  
		//g_my_mutex.unlock();
	}
	return;
}
void mythread4() {
	std::chrono::milliseconds dura(1000);
	while (g_ifend == false) {
		//系统没要求线程退出
		cout << "threadId = " << std::this_thread::get_id() << endl;
		std::this_thread::sleep_for(dura);
	}
	cout << "threadId = " << std::this_thread::get_id() << "运行结束" << endl;
}

int main()
{

	//一、std::future的其他成员函数
#if 0
	cout << "main" << "threadId = " << std::this_thread::get_id() << endl;
	std::future<int> result = std::async(std::launch::deferred, mythread);    //创建一个线程并开始执行，绑定关系,流程并不卡在这里
	cout << "continue..........!" << endl;
	//cout << result.get() << endl;   //卡在这里等待mythread()执行完毕，拿到结果

	//枚举类型
	std::future_status status = result.wait_for(std::chrono::seconds(6));  //等待
	if (status == std::future_status::timeout) { //超时：我等你1秒，你没有返回
		//超时:表示线程还没执行完；
		cout << "超时，线程还没有执行完毕" << endl;
	}
	else if (status == std::future_status::ready) {
		//表示线程成功返回
		cout << " 表示线程成功返回" << endl;
		cout << result.get() << endl;
	}
	else if (status == std::future_status::deferred) {
		//表示线程延迟 前提是创建线程的时候第一个参数加上std::launch::deferred
		cout << "表示线程延迟" << endl;
		cout << result.get() << endl;
	}
#endif
	//二、std::shared_future
#if 0
	cout << "main" << "threadId = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt(mythread1);  //我们把函数mythread1通过packaged_task包装起来
	std::thread t1(std::ref(mypt), 1);   //线程直接开始执行，第二个参数作为线程入口函数的参数。
	t1.join();  //等待线程执行完毕

	std::future<int> result = mypt.get_future();
	std::shared_future<int> result_s(result.share());    //std::future对象里包含有线程入口函数的返回结果，这里result保存mythread返回的结果
	std::shared_future<int> result_s1(mypt.get_future());  //通过get_future返回值直接构造了一个shared_future对象
	std::thread t2(mythread2, std::ref(result_s));
	t2.join();
	cout << result_s.get() << endl;
#endif

	//三、原子操作std::atomic
	//(3.1)原子操作概念引出范例
	//互斥量:多线程编程中，保护共享数据； 锁、操作共享数据、开锁
	//有两个线程，对一个变量进行操作，这个线程读变量值，另外一个线程往这个变量中写值。
	//int atomvalue = 5;
	//读线程A
	//int tmpvalue = atomvalue; //这里这个atomvalue代表的是多个线程间共享的变量
	//写线程B
	//atomvalue = 6;
	//大家可以把原子操作理解成一种：不需要用到互斥量加锁技术的多线程并发编程方式
	//原子操作：是在多线程中 不会被打断的 程序执行片段，原子操作 比 互斥量效率上更胜一筹
	//互斥量的加锁一般是针对一个代码段，而原子操作针对的一般都是一个变量，而不是一个代码段
	//原子操作：一般都是指“不可分割的操作”；也就是说这种操作状态要么是完成的，要么是没完成的，不可能出现半完成状态
	//std::atomic来代表原子操作，std::atomic是个类模板。其实std::atomic这个东西是用来封装某个类型的值的

	//(3.2)基本的std::atomic用法范例
#if 0
	thread mytobj(mythread3);
	thread mytobj1(mythread3);

	mytobj.join();
	mytobj1.join();

	cout << g_mycount << endl;
#endif

	thread mytobj(mythread4);
	thread mytobj1(mythread4);
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	g_ifend = true;
	mytobj.join();
	mytobj1.join();

	//(3.3)总结









	cout << "I love china!" << endl;


	return 0;
}

