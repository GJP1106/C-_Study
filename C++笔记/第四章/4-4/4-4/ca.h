#ifndef _CA_H__
#define __CA_H__

template <typename C>
class A {  //普通类
public:
	template <typename T2>
	A(T2 v1, T2 v2);
	//A(T2 v1, T2 v2) {  //构造函数我们也引入自己的模板，和整个类的模板C没有关系

	//}

	template <typename T>
	void myft(T tmpt) {   //成员函数模板
		cout << tmpt << endl;
	}
	void myftpt() {}
	C m_ic;
};

template <typename C>  //先跟类的模板参数列表
template <typename T2> //再跟构造函数自己的模板参数列表
A<C>::A(T2 v1, T2 v2) {
	cout << v1 << v2 << endl;
}

template <typename T>
void myfunc123(T v1, T v2) {
	cout << v1 + v2 << endl;
}


#endif