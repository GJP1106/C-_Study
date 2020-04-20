// 6-11.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <atomic>
#include <future>

using namespace std;
std::atomic<int> g_mycount = 0;
void mythread() {
	for (int i = 0; i < 1000000; i++) {
		//g_mycount++;
		g_mycount = g_mycount + 1;  //结果有误
	}
}
void mythread1() {
	for (int i = 0; i < 1000000; i++) {
		g_mycount--;
	}
}
int thread1() {
	cout << "thread() start  threadId = :" << std::this_thread::get_id() << endl;
	return 1;
}

int main()
{
	//一、原子操作std::atomic
	//一般atomic原子操作，针对++，--，+=，&=，|=，*=是支持的，其他的可能不支持
#if 0

	thread mytobj1(mythread);
	thread mytobj2(mythread);

	mytobj1.join();
	mytobj2.join();
	cout << g_mycount << endl;
#endif

	//二:std::async深入谈
	//(2.1)std::async参数详述,async用来创建一个异步任务
	cout << "main() start  threadId = :" << std::this_thread::get_id() << endl;
	std::future<int> result = std::async(std::launch::deferred, thread1);  
	cout << result.get() << endl;

	//std::launch::deferred【延迟调用】，以及std::launch::async【强制创建一个线程】
	//std::thread() 如果系统资源紧张，那么可能创建线程就会失败，那么执行std::thread()时整个程序可能崩溃
	//std::async()我们一般不叫创建线程(解释async能够创建线程)，我们一般叫它创建一个异步任务。
	//std::async和std::thread最明显的不同，就是async有时候并不创建新线程
	  //a)如果你用std::launch::deferred来调用async会怎么样？
		 //deferred延迟调用，并且不创建新线程，延迟到future对象调用.get()或者.wait()的时候才执行thread1()
	     //如果没有调用get()或者wait(),就不会创建新线程
	  //b)std::launch::async:强制这个异步任务在新线程上执行，这 意味着，系统必须要给我创建出新线程来运行mythread()
	  //c)std::launch::async | std::launch::deferred
	      //这里这个 | ：意味着调用async的行为可能是“创建新线程并立即执行” 或者
	             //没有创建新线程并且延迟到调用result.get()才开始执行任务入口函数， 两者居其一
	  //d)我们不带额外参数；只给async函数一个 入口函数名；
	     //第九节课有个小错误，其实默认值应该是std::launch::async | std::launch::deferred  和c)效果完全一致，
	     //换句话说：系统会自行决定是异步(创建新线程)还是同步(不创建新线程)方式运行；

	//自行决定是什么意思？系统如何决定是异步(创建新线程)还是同步(不创建新线程)方式运行
	//(2.2)std::async和std::thread的区别
	//std::thread创建线程，如果系统资源紧张，那么可能创建线程就会失败，那么执行std::thread()时整个程序可能崩溃
	   //std::thread创建线程的方式，如果想拿到线程返回值不太容易
	//std::async创建异步任务，可能创建也可能不创建线程。并且async调用方式很容易拿到线程入口函数的返回值；

	//由于系统资源限制：
	//(1)如果用std::thread创建的线程太多，则可能创建失败，系统报告异常，崩溃。
	//(2)如果用std::async,一般就不会异常不会崩溃，因为，系统资源紧张导致无法创建新线程的时候，std::async这种不加额外参数的调用
	  //就不会创建新线程。而是后续谁调用了result.get()来请求结果，那么这个异步任务thread1就运行在执行这条get()语句所在的线程上。
	//如果你强制std::async 一定要创建新线程，那么就必须使用 std::launch::async。承受的代价就是系统资源紧张时，程序崩溃
	//3)经验：一个程序里，线程数量不宜超过100-200。
	
	//(2.3)std::async不确定性问题的解决
	//不加额外参数的std::async调用，让系统自行决定是否创建新线程。
	//问题焦点在于 std::future<int> result = std::async(thead1);  写法
	//这个异步任务到底有没有别推迟执行，(std::launch::async还是std::launch::deferred)
	//std::future对象的wait_for函数，第10节讲过
	   










	return 0;
}

