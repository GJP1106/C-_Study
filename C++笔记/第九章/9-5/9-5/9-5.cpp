
#include <iostream>
#include <map>
#include <boost/type_index.hpp>
using namespace std;

template<typename T>
void myfunc(T& tmprv) {
	cout << "----------------------begin---------------" << endl;
	using boost::typeindex::type_id_with_cvr;
	cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;  //显示T类型
	cout << "tmprv=" << type_id_with_cvr<decltype(tmprv)>().pretty_name() << endl;
	cout << "----------------------end---------------" << endl;
}

class CT {
public:
	//auto m_i = 12; //普通成员变量不能是auto类型
	static const auto m_si = 12;  //static const 静态成员可以用auto，使用auto后，其值必须在类内初始化
	                              //static const，和普通静态成员不一样，普通静态成员是在这里声明，然后在.cpp文件中定义和初始化
	                               //static const 静态成员就在这里定义和初始化了。
};

int main()
{

	//一、std::forward用法补充
#if 0
	int ix = 12; //ix左值
	int &&def = std::move(ix);
	int &&def1 = std::forward<int>(ix); //forward在这里能把左值成功的转换成右值
#endif

	//二、auto类型推断
	int i = 18;        //int
	const int j = i;   //const int
	const int &k = i;  //const int &
	myfunc(i);         //T = int  tmprv = int &
	myfunc(j);         //T = const int, tmprv = const int &
	myfunc(k);         //T = const int, tmprv = const int &

	//auto c++11时代，auto用于变量的自动类型推断:在声明变量的时候根据变量初始值的类型自动为此变量
	  //选择匹配的类型，而不需要我们显式指定类型。
	//特点:
	//(1)auto自动类型推断发生在编译期，所以不会 影响执行期间的性能；
	//(2)auto定义变量必须立即初始化，这样编译器才能推断它的实际类型。
	    //那么编译的时候才能确定auto的类型和整个变量的类型，然后在编译期就可以用真正的类型替换掉auto这个类型的占位符
	//(3)auto的使用灵活，和指针 和引用 和const等限定符结合使用

	//auto类型推断，和上边这个函数模板推断非常类似。
	//auto推导出来后代表一个具体类型。auto实际上是一个类型，那么这里的auto实际上相当于咱们上边
	  //函数模板推导里边的这个类型模板参数T，所以auto这个东西也是类型声名的一部分。【理解成类型占位符】

	//auto x = 27; //x = int,auto = int
	//形参tmprv分三类：a)指针或者引用类型但不是万能引用 b)万能引用类型。c)传值方式(非指针，非引用)
	//a)传值方式(非指针，非引用)：传值方式的auto会抛弃引用，const等限定符
	auto x = 27;  //x = int, auto = int
	const auto x2 = x; //x2 = const int ,auto = int

	//b)指针或者引用类型但不是万能引用,"不会抛弃const等限定符，但是会丢掉引用"
	const auto &xy = x;  //xy = const int &,auto = int
	auto xy2 = xy;  //xy2 = int, auto = int  传值方式：引用类型会被抛弃，const属性也会被抛弃，对方看成新副本；
	auto &xy3 = xy;  //const int &, auto = const int, 引用会被丢弃，但const属性会被保留
	auto y = new auto(100);  //y = int *, auto = int *; auto可以用于new操作符。
	const auto *xp = &x; //xp = const int *,auto = int
	auto *xp2 = &x;   //xp2 = int *, auto = int
	auto xp3 = &x;     //xp3 = int *,auto = int *;  xp3没有声明指针，但auto也把它推导成了指针类型。

	//c)万能引用类型：T&&
	auto&& wnyy1 = x;   //x是左值，auto = int &，wnyy1 = int &
	auto&& wnyy2 = x2; //x2是左值， auto int &,wnyy2 是const int &;

	auto&& wnyy3 = 100; //100是右值， auto = int, wnyy3 = int && (右值引用类型)

	//三、auto类型针对数组和函数的推断
	const char mystr[] = "I love China";   //mystr = const char[13]

	//五、auto不适用的场景举例
	//(1)auto不能用于函数参数，比如void myfu(auto x,int y){}
	//(2)普通成员变量不可以是auto类型，static const auto m_si = 12;被允许

	//六、auto适用场合举例
	std::map<string, int> mymap;
	mymap.insert({ "a",1 });
	mymap.insert({ "b",2 });
	mymap.insert({ "c",3 });
	mymap.insert({ "d",4 });
	/*std::map<string, int>::iterator iter;
	for (iter = mymap.begin(); iter != mymap.end(); ++iter) {*/
	for(auto iter = mymap.begin(); iter != mymap.end(); ++iter) {
		cout << iter->first << "=" << iter->second << endl;
	}


	return 0;
}
