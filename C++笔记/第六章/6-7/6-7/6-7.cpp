// 6-7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <mutex>

using namespace std;
std::mutex resource_mutex;
std::once_flag g_flag;   //这是个系统定义的标记
class MyCAS {
public:
	static void CreateInstance() {
		m_instance = new MyCAS();
		static ClearCAS cc;
	}
public:
	static MyCAS *GetInstace() {
#if 0
		//提高效率
		//a)如果if(m_instance != NULL) 条件成立，则肯定表示m_instance已经被new过了
		//b)如果if(m_instance == NULL) 不代表m_instance一定没被new过

		if (m_instance == NULL) {  //双重锁定(双重检查)
			std::unique_lock<std::mutex> mymutex(resource_mutex);
			if (m_instance == NULL) {
				m_instance = new MyCAS();
				static ClearCAS cc;
			}
		}
#endif
		std::call_once(g_flag, CreateInstance);  //两个线程同时执行到这里，其中一个线程要等另外一个线程执行完毕CreateInstance()
		return m_instance;
	}
	class ClearCAS {
	public:
		ClearCAS() {
			if (MyCAS::m_instance) {
				delete MyCAS::m_instance;
				MyCAS::m_instance = NULL;
			}
		}
	};
	void func() {
		cout << "test" << endl;
	}
private:
	MyCAS() {

	}
private:
	static MyCAS *m_instance; //静态成员变量
	
};

//类静态变量初始化
MyCAS *MyCAS::m_instance = NULL;
void mythread() {
	MyCAS *p_a = MyCAS::GetInstace();
	p_a->func();
}

int main()
{
	//一、设计模式大概谈
	//“设计模式”:代码的一些写法(这些写法跟常规写法不怎么一样)：程序灵活，维护起来可能方便，但是别人接管，阅读代码非常痛苦
	//用“设计模式”理念写出来的代码很晦涩的；

	//二、单例设计模式
	//单例设计模式使用的频率比较 高；
	//单例：整个项目中，有某个或者某些特殊的类，属于该类的对象，我只能创建1个。
	//单例类：
#if 0
	MyCAS *p_a = MyCAS::GetInstace();   //创建一个对象，返回该类(MyCAS)对象的指针
	p_a->func();
	MyCAS::GetInstace()->func();
#endif

	//三、单例设计模式共享数据问题分析、解决
	//面临的问题：需要在我们自己创建的线程(而不是主线程)中来创建MyCAS这个单例类的对象，这种线程可能不止(最少2个)。
	//我们可能会面临GetInstance()这种成员函数要互斥；
	//虽然这两个线程是同一个入口函数，但大家千万要记住，这是两个线程，所以这里会有两个流程同时开始执行mythread线程入口函数
#if 0
	std::thread mytobj1(mythread);
	std::thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();
#endif

	//四、std::call_once();   c++11引入的函数 ，该函数的第二个参数 是一个函数名a();
	//call_once()的功能是能够保证函数a()只被调用一次。
	//call_once具备互斥量这种能力，而且效率上，比互斥量消耗的资源更少；
	//call_once()需要与一个标记结合使用，这个标记std::once_flag;其实once_flag是一个结构;
	//call_once()就是通过这个标记来决定对应的函数a()是否执行，调用call_once()成功后，call_once()就把这个标记设置为一种已调用状态；
	//后续再次调用call_once(),只要once_flag被设置为了“已调用”状态，那么对应的函数a()就不会再被执行了;

	std::thread mytobj1(mythread);
	std::thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();











	return 0;
}