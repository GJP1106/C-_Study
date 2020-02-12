// 3-13.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "Human.h"
#include "Men.h"
#include "Women.h"
using namespace std;

class CTempValue {
public:
	int val1;
	int val2;
public:
	CTempValue(int v1 = 0, int v2 = 0);
	CTempValue(const CTempValue& t) :val1(t.val1), val2(t.val2) { //拷贝构造函数
		cout << "调用了拷贝构造函数" << endl;
	}

	//拷贝赋值运算符
	CTempValue & operator=(const CTempValue &tmpv) {
		val1 = tmpv.val1;
		val2 = tmpv.val2;
		cout << "调用了拷贝赋值运算符" << endl;
		return *this;
	}
	virtual ~CTempValue() //析构函数
	{
		cout << "调用了析构函数" << endl;
	}
public:
	int Add(CTempValue &tobj); //普通函数
	CTempValue Double(CTempValue &ts) {
		CTempValue tmp; //这个会消耗我们一个构造函数和一个析构函数的调用
		tmp.val1 = ts.val1 * 2;
		tmp.val2 = ts.val2 * 2;
		return tmp;
	}
};
CTempValue::CTempValue(int v1, int v2) :val1(v1), val2(v2) {
	cout << "调用了构造函数" << endl;
	cout << "val1 = " << val1 << endl;
	cout << "val2 = " << val2 << endl;
}
int CTempValue::Add(CTempValue &tobj) {
	int tmp = tobj.val1 + tobj.val2;
	tobj.val1 = 1000;  //这里修改值对外界没有影响
	return tmp;
}

//统计字符ch在字符串strsource里出现的次数，把次数返回去
int calc(const string &strsource, char ch) {  //strsource 这个形参就绑定到了string临时对象上
	const char *p = strsource.c_str();
	int icount = 0;
	//...具体的统计代码

	return icount;
}
//普通函数
CTempValue Double(CTempValue &ts) {
	CTempValue tmp; //这个会消耗我们一个构造函数和一个析构函数的调用
	tmp.val1 = ts.val1 * 2;
	tmp.val2 = ts.val2 * 2;
	return tmp;
}

class mynum {
public:
	mynum(int x = 0, int y = 0) :num1(x), num2(y){}
public:
	int num1;
	int num2;
};
mynum operator+(mynum &tmpnum1, mynum &tmpnum2) {
	/*mynum result;
	result.num1 = tmpnum1.num1 + tmpnum2.num1;
	result.num2 = tmpnum1.num2 + tmpnum2.num2;
	return result;*/
	//优化为
	return mynum(tmpnum1.num1 + tmpnum2.num1, tmpnum1.num2 + tmpnum2.num2);
}
int main()
{
	//一、临时对象的概念
	//i++,++i
#if 0
	int i = 1;
	int &&r1 = i++; // r1和i之间没有什么关系。
	r1 = 19;
	i = 80;
#endif

	//另外一些临时对象，是因为我们代码书写问题而产生的。统一称临时变量为临时对象。
	//new delete 栈

	//二、产生临时对象的情况和解决：三种情况和解决方案。
	//（2.1）以传值(不建议，传引用)的方式给函数传递参数CTempValue;
#if 0
	CTempValue tm(10, 20); //调用构造函数
	int Sum = tm.Add(tm); //这个会导致拷贝函数的执行
	cout << "Sum = " << Sum << endl;
	cout << "tm.val1 = " << tm.val1 << endl;
#endif
	//(2.2)类型转换生成临时对象/隐式类型转换以保证函数调用成功
#if 0
	CTempValue sum;
	sum = 1000; //这里产生了一个真正的临时对象
	//(1)用1000这个数字创建了一个类型为CTempValue的临时对象
	//(2)调用拷贝赋值运算符把这个临时对象里边的各个成员值赋给了sum对象
	//(3)销毁这个临时创建的CTempValue对象
#endif
	//优化
	//CTempValue sum = 1000; //把定义对象和给对象赋初值放在一行。就不会生成多余的临时对象
	                       //为sum对象预留了空间。用1000构造sum对象，而且是直接构造在sum对象预留空间里

	//隐式类型转换以保证函数调用成功
#if 0
	char mystr[100] = "I love china, oh, yeah!";
	int result = calc(mystr, 'o');  //char[] ,string
#endif 
	//c++语言只会为const引用(const string &strsource) 产生临时变量，而不会为非const引用(string &strsource)这种参数产生临时变量
#if 0
	string mystr = "I love china, oh, yeah!";
	int result = calc(mystr, 'o');
#endif

	//2.3)函数返回对象的时候
	CTempValue ts1(10, 20);
	//Double(ts1); //因为返回临时对象导致占用了一个拷贝构造函数和一个析构函数
	CTempValue ts2 = Double(ts1);
	CTempValue &&ts3 = Double(ts1); //临时对象是一种右值

	//Double() 函数引起的消耗
	//CTempValue tmp;会消耗一个构造函数和一个析构函数
	//return tmp; 产生临时对象，占用一个拷贝构造函数和析构函数

	//再举一个例子：介绍知识点：类外运算符重载
	mynum tm1;
	tm1.num1 = 10;
	tm1.num2 = 100;

	mynum tm2;
	tm2.num1 = 20;
	tm2.num2 = 200;
	mynum tmp = tm1 + tm2;

	//(1)代码优化
	//(2)锻炼眼神和经验



	return 0;
}

