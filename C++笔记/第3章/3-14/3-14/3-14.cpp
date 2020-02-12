// 3-14.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Human.h"
#include "Men.h"
#include "Women.h"
#include <vector>
using namespace std;


int main()
{
	//一、对象移动的概念
	//对象拷贝，c++11“对象移动”

	//二、移动构造函数和移动赋值运算符概念
	//c++11 std::move 解决效率问题
	//移动构造函数：c++11 进一步提高程序效率
	//vector:
	//说明：
	//（1）A移动给B，那么A对象我们就不能再使用了。
	//(2)移动：并不是把内存中的数据从一个地址 倒腾到另外一个地址。知识所有者变更。



	return 0;
}

