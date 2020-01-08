#include <iostream>
#include <vector>
#include <string>
using namespace std;

//迭代器运算符小节e使用
struct student {
	int num;
};
//第七灾难程序演示
struct conf {
	char itemname[40];
	char itemcontent[100];
};

char *getInfo(vector<conf *>&conflist, char *pitem) {
	for (auto pos = conflist.begin(); pos != conflist.end(); ++pos) {
		if (_stricmp((*pos)->itemname, pitem) == 0) {
			return (*pos)->itemcontent;
		}
	}
	return nullptr;
}
int main() {
    //一：迭代器简介
	//vector
	//迭代器是一种遍历容器内元素的数据类型，这种数据类型感觉有点像指针，我们理解的时候就理解为迭代器用来指向容器中的某个元素。
	//string，vector，[], 很少用[], 更常用的访问方式就是用迭代器(更通用)。
	//通过迭代器，我们就可以读取容器中的元素值，读string中的每个字符，还可以修改某个迭代器所指向的元素值。
	//++，--
	//list，map，尽量学会用迭代器来访问容器中的元素。
	//二、容器的迭代器类型
#if 0
	vector<int> iv = { 100, 200, 300 };
	vector<int>::iterator iter;        //定义迭代器，也必须是vector<int>

	//大家在理解的时候，就把整个的vector<int>::iterator 理解成一个类型，这种类型就专门应用于迭代器。
	//当我们用这个类型定义一个变量的时候，这个变量，就是个迭代器，这里iter这个变量就是迭代器。



	//三、迭代器begin() / end()操作，反向迭代器rbegin() / rend()操作
	//begin() / end()用来 返回 迭代类型。rbegin() / rend()用来 返回 迭代类型。
	//a)begin()返回一个迭代器类型(大家就理解为返回一个迭代器);

	iter = iv.begin(); //如果容器中有元素，则begin返回的迭代器，指向的是容器中的第一个元素。
    //相当于iter指向了iv[0];

	//b)end() :返回一个迭代器类型(大家就理解成返回一个迭代器);
	iter = iv.end(); //end返回的迭代器指向的并不是末端元素，而是末端元素的后边，哪这个后边怎么理解？
	//我们就理解成end()指向的是一个不存在的元素。
#endif
	//c)如果一个容器为空，那么begin()和end()返回的迭代器就相同。
#if 0
	vector<int> iv2;
	vector<int>::iterator iterbegin = iv2.begin();
	vector<int>::iterator iterend = iv2.end();
	if (iterbegin == iterend)
	{
		cout << "容器iv2为空" << endl;
	}
#endif
	//d)
#if 0
	vector<int> iv = { 100, 200, 300 };   //定义一个容器
	for (vector<int>::iterator iter = iv.begin(); iter != iv.end(); iter++) {
		cout << *iter << endl; //100 200 300
	}

	//反向迭代器：大家想从后往前遍历一个容器，那么反向迭代器就比较方便。
	//方向迭代器(逆向迭代器)，用的rbegin(), rend();
	//rbegin():返回一个反向迭代器，指向反向迭代器的第一个元素；
	//rend():返回一个反向迭代器，指向反向迭代器的最后元素的下一个位置。
	//注意使用反向迭代器和正向迭代器的区别:
	//反向迭代器定义使用 vector<int>::reverse_iterator
	for (vector<int>::reverse_iterator riter = iv.rbegin(); riter != iv.rend(); riter++) {
		cout << *riter << endl; //100 200 300
	}
#endif

	//四：迭代器运算符
#if 0
	//a) *iter: 返回迭代器iter所指向元素的引用。必须保证这个迭代器指向的是有效的容器元素，
	//不能指向end()，因为end()是末端元素的后边，也就是end()指向的是一个不存在的元素。
	vector<int> iv = { 100, 200, 300 };
#if 0 //这种写法会使程序运行时崩掉
	vector<int>::iterator iter = iv.end();
	cout << *iter << endl;
#endif
#if 0  //这种写法OK
	vector<int>::iterator iter = iv.begin();
	cout << *iter << endl;
#endif


	//b)++iter; iter++;  让迭代器指向容器中的下一个元素；已经指向end()的时候你不能再++;
#if 0 //这样会使程序直接崩了
	vector<int>::iterator iter = iv.end();
	iter++;
#endif
	vector<int>::iterator iter = iv.begin();
	iter++;
	cout << *iter << endl; //OK 输出结果为200

#endif
	
	//c)--iter和iter--; 让迭代器指向容器中的上一个元素。指向开头元素，就不能再--
#if 0
	vector<int> iv = { 100, 200, 300 };
#if 0 //程序会崩掉
	vector<int>::iterator iter = iv.begin();
	iter--;
#endif
	vector<int>::iterator iter = iv.end();
	iter--;
	cout << *iter << endl;  //300
#endif


	//d)iter1 == iter2, iter1 != iter2 判断两个迭代器是否想等。
	//如果两个迭代器指向的是同一个元素，就相等，否则就不等。

	//e)
#if 0 //此处需要用到开头处定义的结构体
	vector<student> sv;
	student mystu;
	mystu.num = 100;
	sv.push_back(mystu);  //把对象mystu赋值到了sv容器中；

	vector<student>::iterator iter;
	iter = sv.begin();  //指向第一个元素
	cout << (*iter).num << endl;
	cout << iter->num << endl;  //两种输出方式均可
#endif

	//五:const_iterator迭代器，const:常量
	//const_iterator迭代器，表示值不能改变的意思，这里的值不能改变表示这个迭代器指向的元素不能改变，
	//而不是表示这个迭代器本身不能改变，也就是说，迭代器本身是可以不断指向下一个元素；
	//只能从容器中读元素，不能通过这个迭代器改写容器中的元素。感觉起来更像常量指针。
	//iterator是能读能写；
#if 0
	vector<int> iv = { 100, 200, 300 };
	vector<int>::const_iterator iter;
	for (iter = iv.begin(); iter != iv.end(); ++iter) {
		//*iter = 4;  //直接报错
		cout << *iter << endl; //可以正常读
	}
#endif

#if 0
	//如果定义一个常量容器，不使用const_iterator就会报错
	const vector<int> iv = {100, 200, 300 };
	//vector<int>::iterator iter;  //不使用const_iterator就会报错
	vector<int>::const_iterator iter;  //OK
	for (iter = iv.begin(); iter != iv.end(); ++iter) {
		//*iter = 4;  //直接报错
		cout << *iter << endl; //可以正常读
	}
#endif

#if 0
	//(5.1)cbegin()和cend()操作
	//c++11引入的两个新函数cbegin(), cend(),跟begin, end类似。cbegin, cend，返回的都是常量迭代器；
	vector<int> iv = { 100, 200, 300 };
	for (auto iter = iv.cbegin(); iter != iv.cend(); ++iter) {
		//*iter = 4; //报错，不能给常量赋值。这说明cbegin返回的是常量迭代器。
		cout << *iter << endl;
	}
#endif

	//六:迭代器失效
	vector<int> vecvalue{ 1, 2, 3, 4, 5 };
#if 0
	//正常输出
	for (auto vecitem : vecvalue) {
		cout << vecitem << endl;
	}
	//不能正常输出
	for (auto vecitem : vecvalue) {
		vecvalue.push_back(1);   //程序崩溃或数据混乱
		cout << vecitem << endl;
	}
#endif

#if 0
	//迭代器 正常输出
	for (auto beg = vecvalue.begin(), end = vecvalue.end(); beg != end; ++beg) {
		cout << *beg << endl;
	}
	//非正常输出
	for (auto beg = vecvalue.begin(), end = vecvalue.end(); beg != end; ++beg) {
		vecvalue.push_back(1);   //程序崩溃或数据混乱
		cout << *beg << endl;
	}
#endif

	//在操作迭代器的过程中(使用了迭代器这种循环体)，千万不要改变vector容器的容量，也就是不要增加或者删除vector容器中的元素。
	//往容器中增加或者从容器中删除元素，这些操作可能会使指向容器元素的指针、引用、迭代器失效。
	//失效就表示不能在代表任何容器中的元素，一旦使用失效的东西，就等于犯了严重的程序错误，很多情况下，程序会直接崩溃。
#if 0
	//vector,list,map
	for (auto beg = vecvalue.begin(), end = vecvalue.end(); beg != end; ++beg) {
		vecvalue.push_back(1);   //push完之后要立即退出，不要做其他操作，可避免出现问题。
		break;
	}
	for (auto beg = vecvalue.begin(), end = vecvalue.end(); beg != end; ++beg) {
		cout << *beg << endl;
	}
#endif

	//(6.1)灾难程序演示1
#if 0  //方法一
	auto beg = vecvalue.begin();
	auto end = vecvalue.end();
	while (beg != end) {
		cout << *beg << endl;
		//假如我们想往begin这个位置插入新值，可以用insert
		vecvalue.insert(beg, 80);   //插入新值，第一个参数为插入位置，第二个参数为插入元素。
		                            //咱们这一插入，肯定会导致迭代器失效。比如begin, end失效。
		                            //具体哪个迭代器失效，取决于这个容器vector内部的实现原理，我们可以查资料详细研究。
		                            //现在我们不太明确哪个迭代器失效了，最明智的做法，就是我们只要一插入数据，插入完毕就break出循环体。
		break;   //最明智的防止迭代器失效的方法。否则程序可能崩溃
		++beg; //不要忘记，并且要放在循环末尾
	}

	beg = vecvalue.begin();
	end = vecvalue.end();
	while (beg != end) {
		cout << *beg << endl;
		++beg; //不要忘记，并且要放在循环末尾
	}

#endif
#if 0   //方法二
	auto beg = vecvalue.begin();
	int icount = 0;
	while (beg != vecvalue.end()) {   //每次更新end防止end失效
		beg = vecvalue.insert(beg, icount + 80);  //insert的返回结果我就要接着
		icount++;
		if (icount > 10)
			break;
		++beg;
	}
	beg = vecvalue.begin();
	auto end = vecvalue.end();
	while (beg != end) {
		cout << *beg << endl;
		++beg;  //不要忘记，并且要放在循环末尾
	}
#endif

	//(6.2)灾难程序演示2

	vector<int> iv = { 100, 200, 300 };
#if 0 //程序会崩掉
	for (auto iter = iv.begin(); iter != iv.end(); ++iter) {
		iv.erase(iter);   //erase函数,移除iter位置上的元素，返回下一个元素位置。
	}
#endif
#if 0 //删除的正确方法1
	vector<int>::iterator iter = iv.begin();
	vector<int>::iterator iterend = iv.end();
	while (iter != iv.end()) {
		iter = iv.erase(iter);
	}
#endif
#if 0 //简单有效的删除方法2
	while (!iv.empty()) {
		auto iter = iv.begin();  //因为不为空，所以返回begin()时没问题。
		iv.erase(iter);  //删除该位置上的元素
	}
#endif

	//七：范例演示
	//7.1) 用迭代器遍历一下string类型的数据
#if 0
	string str("I Love China!");
	for (auto iter = str.begin(); iter != str.end(); ++iter) {
		*iter = toupper(*iter);
	}
	cout << str << endl;
#endif
	//7.2)vector容器常用操作与内存释放
	//实践程序:
	conf *pconf1 = new conf;
	strcpy_s(pconf1->itemname, sizeof(pconf1->itemname), "ServerName");
	strcpy_s(pconf1->itemcontent, sizeof(pconf1->itemcontent), "1区");

	conf *pconf2 = new conf;
	strcpy_s(pconf2->itemname, sizeof(pconf2->itemname), "ServerID");
	strcpy_s(pconf2->itemcontent, sizeof(pconf2->itemcontent), "100000");

	vector<conf *> conflist;
	conflist.push_back(pconf1);
	conflist.push_back(pconf2);

	char *p_tmp = getInfo(conflist, "ServerName");
	if (p_tmp != nullptr) {
		cout << p_tmp << endl;
	}

	//我们要释放内存，自己new的就要自己释放，否则会造成内存泄漏
	std::vector<conf *>::iterator pos;
	for (pos = conflist.begin(); pos != conflist.end(); ++pos) {
		delete (*pos);   //*pos才是那个指针
	}

	conflist.clear();   //这个要不要都行 

}