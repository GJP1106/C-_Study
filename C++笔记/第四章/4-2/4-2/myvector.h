#ifndef __MYVECTOR__
#define __MYVECTOR__

//定义类模板
template<typename T>  //名字为T的模板参数，用来表示myvector这个容器所保存的元素类型
class myvector
{
public:
	typedef T* myiterator; //迭代器，vector iterator

public:
	myvector();  //构造函数
	myvector& operator=(const myvector&);  //赋值运算符重载。在类模板内部使用模板名并不需要提供模板参数。
	//myvector<T>& operator=(const myvector<T>&);
public:
	myiterator mybegin();  //迭代器的起始位置
	myiterator myend();  //迭代器的最后一个元素的下个位置

public:
	//void myfunc() { //把成员函数的函数体(函数具体实现)放在类模板的定义中。

	//}
	void myfunc();
};
//普通函数
template<typename T>
void myvector<T>::myfunc() {
	return;
}

//构造函数
template<typename T>
myvector<T>::myvector() {
	//return;
}

template<typename T>
myvector<T>& myvector<T>::operator=(const myvector&)   //<T>表示返回的是一个实例化了的myvector
{
	return *this;
}







#endif