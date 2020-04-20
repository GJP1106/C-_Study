﻿// 6-9.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <list>
#include <mutex>
#include <future>

using namespace std;
class A {
public:
	int mythread(int mypar) {
		cout << "mythread() start " << "threadid = " << std::this_thread::get_id() << endl;
		std::chrono::milliseconds dura(5000);  //定义一个5秒的时间
		std::this_thread::sleep_for(dura);  //休息了一定时长
		cout << "mythread() end " << "threadid = " << std::this_thread::get_id() << endl;
		return 5;

	}
};

int mythread1(int mypar) {
	cout << "mythread() start " << "threadid = " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(5000);  //定义一个5秒的时间
	std::this_thread::sleep_for(dura);  //休息了一定时长
	cout << "mythread() end " << "threadid = " << std::this_thread::get_id() << endl;
	return mypar;

}

void mythead2(std::promise<int> &tmpp, int calc) {  //大家注意第一个参数
	calc++;
	calc *= 10;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	int result = calc;
	tmpp.set_value(result);   //结果我保存到了tmpp这个对象中；
}
void mythread3(std::future<int> &tmpf) {
	auto result = tmpf.get();
	cout << "mythread3 result" << result << endl;
	return;
}
vector <std::packaged_task<int(int)>> mytask;

int main()
{
	//一、std::async、std::future创建后台任务并返回值
	//希望线程返回一个结果
	//std::async 是个函数模板，用来启动一个异步任务，启动起来一个异步任务之后，它返回一个std::future对象，std::future是个类模板
	//什么叫“启动一个异步任务”，就是自动创建一个线程并开始执行对应的线程入口函数，它返回一个std::future对象
	   //这个std::future对象里边就含有线程入口函数所返回的结果(线程返回的结果)，我们可以通过调用future对象的成员函数get()来获取结；
	   //"future"：将来的意思，有人也称呼std::future提供了一种访问异步操作结果的机制，就是说这个结果你可能不能马上拿到
	   //在线程执行完毕的时候，你就能够拿到结果了，所以大家这么理解:这个future(对象)里会保存一个值，在将来的某个时刻能够拿到

	//下面程序通过std::future对象的get()成员函数等待线程执行结束并返回结果；
	//这个get()函数很牛，不拿到将来的返回值 誓不罢休，不拿到值我就卡在这里等待拿值
	//我们通过额外向std::async()传递一个参数，该参数类型是std::launch类型(枚举类型)，来达到一些特殊的目的；
	//a)std::launch::deferred : 表示线程入口函数调用被延迟到std::future的wait()或者get()函数调用时才执行;
	   //那如果wait()或者get()没有被调用，那么线程 会执行吗?  没执行，实际上 线程根本就没创建
	//std::launch::deferred：延迟调用，并且没有创建新线程，是在主线程中调用的 线程入口函数
	//b)std::launch::async , 在调用async函数的时候就开始创建新线程
	   //async()函数，默认用的就是std::launch::async标记
	

#if 0
	cout << "main" << "threadId = " << std::this_thread::get_id() << endl;
	std::future<int> result = std::async(mythread);    //创建一个线程并开始执行，绑定关系,流程并不卡在这里
	cout << "continue..........!" << endl;
	int def;
	def = 0;
	cout << result.get() << endl;   //卡在这里等待mythread()执行完毕，拿到结果
	//result.wait(); //等待线程返回，本身并不返回结果
	cout << "I love china!" << endl;
#endif

	//用成员函数作为线程入口函数
#if 0
	A a;
	int tmppar = 12;
	cout << "main" << "threadId = " << std::this_thread::get_id() << endl;
	//std::future<int> result = std::async(&A::mythread, &a, tmppar);
	//std::future<int> result = std::async(std::launch::deferred,&A::mythread, &a, tmppar);  //第二个参数是对象引用，才能保证线程里边是同一个对象
	//std::future<int> result = std::async(std::launch::async, &A::mythread, &a, tmppar);


	cout << "continue..........!" << endl;
	int def;
	def = 0;
	//cout << result.get() << endl;   //卡在这里等待mythread()执行完毕，拿到结果
	//result.wait(); //等待线程返回，本身并不返回结果
	cout << "I love china!" << endl;
#endif

	//二、std::packaged_task : 打包任务，把任务包装起来
	//是个类模板，它的模板参数是 各种可调用对象；通过std::packaged_task 来把各种可调用对象包装起来，方便将来作为线程入口函数来调用
	//packaged_task包装起来的可调用对象还可以直接调用，所以从这个角度来讲，packaged_task对象，也是一个可调用对象；



#if 0  //写法1
	cout << "main" << "threadId = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt(mythread1);  //我们把函数mythread1通过packaged_task包装起来
	std::thread t1(std::ref(mypt), 1);   //线程直接开始执行，第二个参数作为线程入口函数的参数。
	t1.join();  //等待线程执行完毕

	std::future<int> result = mypt.get_future();    //std::future对象里包含有线程入口函数的返回结果，这里result保存mythread返回的结果
	cout << result.get() << endl;
	cout << "I love china!" << endl;
#endif

#if 0  //使用lambad表达式
	std::packaged_task<int(int)> mypt([](int mypar) {
		cout << "mythread() start " << "threadid = " << std::this_thread::get_id() << endl;
		std::chrono::milliseconds dura(5000);  //定义一个5秒的时间
		std::this_thread::sleep_for(dura);  //休息了一定时长
		cout << "mythread() end " << "threadid = " << std::this_thread::get_id() << endl;
		return mypar;
	});

	std::thread t1(std::ref(mypt), 1);   //线程直接开始执行，第二个参数作为线程入口函数的参数。
	t1.join();  //等待线程执行完毕

	std::future<int> result = mypt.get_future();    //std::future对象里包含有线程入口函数的返回结果，这里result保存mythread返回的结果
	cout << result.get() << endl;
	cout << "I love china!" << endl;
	//mypt(120);  //直接调用，相当于函数调用；
	//std::future<int> result1 = mypt.get_future();
	//cout << result1.get() << endl;
#endif
#if 0
	std::packaged_task<int(int)> mypt([](int mypar) {
		cout << "mythread() start " << "threadid = " << std::this_thread::get_id() << endl;
		std::chrono::milliseconds dura(5000);  //定义一个5秒的时间
		std::this_thread::sleep_for(dura);  //休息了一定时长
		cout << "mythread() end " << "threadid = " << std::this_thread::get_id() << endl;
		return mypar;
	});
	mytask.push_back(std::move(mypt));   //容器，这里用了移动语义，入进去之后mypt就为空
	std::packaged_task<int(int)> mypt1;
	auto iter = mytask.begin();
	mypt1 = std::move(*iter);   //移动语义
	mytask.erase(iter);   //删除第一个元素，迭代已经失效了，所以后续代码不可以再使用iter
	mypt1(120);  //直接调用，相当于函数调用；
	std::future<int> result1 = mypt1.get_future();
	cout << result1.get() << endl;
#endif

	//三、std::promise 类模板
	//我们能够在某个线程中给它赋值，然后我们可以在其他线程中，把这个值取出来用；
	//总结：通过promise保存一个值，在将来某个时刻我们通过把一个future绑定到这个promise上来得到这个绑定的值；
	std::promise<int> myprom;  //声明一个std::promis对象myprom，保存的值类型为int；
	std::thread t1(mythead2, std::ref(myprom), 180);

	t1.join();

	//获取结果值
	cout << "等待结果" << endl;
	/*std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);*/
	std::future<int> ful = myprom.get_future();   //promise和future绑定，用于获取线程返回值
	//auto result = ful.get();    //get只能调用一次，不能调用多次
	//cout << "result = " << result << endl;
	std::thread t2(mythread3, std::ref(ful));
	t2.join();  //等待mythread3线程执行完毕
	cout << "I love china!" << endl;

	//四、小结
	//到底怎么用，什么时候用；
	//我们学习这些东西的目的并不是要把他们都用在咱们自己的实际开发中；
	//相反，如果我们能够用最少的东西能够写一个稳定，高效的多线程程序，更值得赞赏；
	//我们为了成长，必须要阅读一些高手写的代码，从而快速实现自己代码的积累，我们的技术就会有一个大幅度的提升；
	//老师更愿意将学习这些内容的理由理解为：为我们将来能够读懂高手甚至大师写的代码而铺路。








	return 0;
}

