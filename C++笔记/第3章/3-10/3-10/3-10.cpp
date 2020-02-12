// 3-10.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "human.h"
#include "men.h"
#include "women.h"

int main()
{
	//一、RTTI是什么(Run Time Identification)运行时类型识别；
	//通过运行时类型识别，程序能够使用基类的指针或者引用来检查这些指针或者引用所指的对象的实际派生类型。
	//Human *phuman = new Men;
	//Human &q = *phuman; //*phuman表示指针phuman所指向的对象
	//RTTI我们可以把这个称呼看成是一种系统提供给我们的一种能力，或者一种功能。这种功能或者能力是通过2个运算符来体现：
	//(1)dynamic_cast运算符:能够将基类的指针或者引用安全的转换为派生类的指针或者引用。
	//(2)typeid运算符:返回指针或者引用所指对象的实际类型。
	//补充：要想让RTTI的两个运算符能够正常工作，那么基类中必须至少要有一个虚函数，不然这两个运算符工作的结果就可能跟我们预期不一样了
	//因为只有虚函数的存在，这两个运算符才会使用指针或者引用所绑定的对象的动态类型(你new的类型)
	//phuman->eat();
	//phuman->menfunc();

	//二、dynamic_cast运算符：如果该运算符能够转换成功，说明这个指针实际上是要转换到的那个类型。这个运算符能够帮咱们做安全检查
	//Human *phuman = new Men;
	//Men *p = (Men *)(phuman);  //用c语言风格的强制类型转换，硬把指针转换成Men *;
	//p->testfunc();  //能够正常的调用Men类的成员函数testfunc()

	//Women *p1 = (Women *)(phuman);//也能转，但是会有发生问题的可能

	//Men *pmen = dynamic_cast<Men *>(phuman);
	//if (pmen != nullptr) {
		//std::cout << "phuman实际是一个Men类型" << std::endl;
		//在这里操作类Men里边的成员函数，成员变量都能够操作并且安全的操作
		//pmen->testfunc();
	//}
	//else {
		//转换失败
		//std::cout << "phuman实际不是是一个Men类型" << std::endl;
	//}

	//对于引用，如果用dynamic_cast转换失败，则系统会抛出一个std::bad_cast异常。try()...catch(){}
	//Human *phuman = new Men;
	//Human &q = *phuman;  //这就是引用
	//try {
	//	Men &menbm = dynamic_cast<Men &>(q); //转换不成功，则流程直接进入到catch里边去，如果转换成功，流程继续往下走。
	//	std::cout << "phuman实际上是一个Men类型" << std::endl;
	//	//在这里调用类Men的成员函数都是安全的
	//	menbm.testfunc();
	//}
	//catch(std::bad_cast){
	//	std::cout << "phuman实际上不是一个Men类型" << std::endl;
	//}


	//三、typeid运算符
	//typeid(类型); 也可能typeid(表达式);
	//那倒对象类型信息；typeid就会返回一个 常量对象的引用，这个常量对象 是一个标准库类型，type_info(类/类型)
	//Human *phuman = new Men;
	//Human &q = *phuman;
	//std::cout << typeid(*phuman).name() << std::endl;  //class Men
	//std::cout << typeid(q).name() << std::endl; //class Men
	//char a[10] = { 5, 1 };
	//int b = 120;
	//std::cout << typeid(a).name() << std::endl;  //char [10]
	//std::cout << typeid(b).name() << std::endl;  //int

	//typeid主要是为了比较两个指针是否指向同一种类型的对象
	//(1)两个指针定义的类型相同(Human);不管他们new的是啥，typeid都相等
	//该例不太符合我们的期盼和要求
	/*Human *phuman1 = new Men;
	Human *phuman2 = new Men;
	if (typeid(phuman1) == typeid(phuman2)) {
		std::cout << "phuman1和phuman2是同一种类型[看指针定义]" << std::endl;
	}*/
	//比较对象时，看的是new出来的是哪个对象或者该指针指向的是哪个对象，和定义该指针时定义的类型没关系。
	//Human *phuman = new Men;
	//Men *phuman2 = new Men;
	//Human *phuman3 = phuman2;
	//if (typeid(*phuman) == typeid(*phuman2)) {  //千万不要把*忘了
	//	std::cout << "phuman和phuman2是同一种类型" << std::endl;
	//}
	//if (typeid(*phuman2) == typeid(*phuman3)) {
	//	std::cout << "phuman2和phuman3是同一种类型" << std::endl;
	//}

	//Human *phuman = new Men;
	//if (typeid(*phuman) == typeid(Men)) {
	//	std::cout << "Phuman指向Men" << std::endl;
	//}
	//else if (typeid(*phuman) == typeid(Human)) {  //如果没有虚函数，此if成立
	//	std::cout << "Phuman指向humen" << std::endl;
	//}
    //基类必须要有虚函数，否则上边的条件不成立。
	//切记：只有当基类有虚函数时，编译器才会对typeid()中的表达式求值，否则如果某个类型不含有虚函数，
	//则typeid()返回的式表达式的静态类型(定义时的类型),既然是定义的类型，编译器就不需要对表达式求值也能知道表达式的静态类型

	//四、type_info类
	//typeid就会返回一个 常量对象的引用，这个常量对象 是一个标准库类型，type_info(类/类型)
#if 0
	//a)name: 名字
	Human *phuman = new Men;
	const type_info &tp = typeid(*phuman);
	std::cout << tp.name() << std::endl;  //class Men

	//b) == 、!= 
	Human *phuman1 = new Men;
	const type_info &tp1 = typeid(*phuman1);
	if (tp == tp1) {
		std::cout << "tp==tp1类型相同" << std::endl;
	}
	Human *phuman3 = new Women;
	const type_info &tp2 = typeid(*phuman3);
	if (tp == tp2) {
		std::cout << "tp==tp2类型相同" << std::endl;
	}
#endif
	//四、RTTI与虚函数表
	//c++中，如果类里面含有虚函数，编译器就会对该类产生一个虚函数表。
	//虚函数表里有很多项，每一项都是 一个指针。每个指针指向的是这个类里的各个虚函数的入口地址。
	//虚函数表项里，第一个表项很特殊，它指向的不是虚函数的入口地址，它指向的实际上是咱们这个类所关联的type_info对象。
	Human *phuman = new Men;
	const type_info &ty = typeid(*phuman);

	//phuman对象里有一个我们看不见的指针，这个指针指向谁？指向的是这个对象所在的类Men里的虚函数表。



	return 0;
}

