// 4-5.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <map>

using namespace std;

//C++98�ķ���
//ϣ������һ�����ͣ�ǰ���ⲿ�̶ֹ����䣬��std::map<std::string, �����Լ�ָ��>
template <typename st>
struct map_s {  //������һ���ṹ/�ֻ࣬�ǽṹ�ĳ�Աȱʡ����public
	typedef std::map<std::string, st> type;  //������һ������
};

//c++11�ķ���
template<typename T>
using str_map_t = std::map<std::string, T>;  //str_map_t �����ͱ���
                                             //using������һ��������ģ�塱������(����)�õ�
template <typename T>
using myfunc_M = int(*)(T, T);   //��������ģ�壬 �Ǹ�����ָ��ģ��

int RealFunc(int i, int j) {
	return 1;
}

template <typename T1,typename T2,typename T3>
T1 sum(T2 i, T3 j)
{
	T1 result = i + j;
	return result;
}

int main()
{
	//һ��using����ģ�����
#if 0
	//typedef ��һ�������������ͱ���
	typedef unsigned int uint_t;  //�൱�ڸ�unsigned int��������Ҫ������uint_t
	uint_t abc;
	//std::map<std::string, int>
	typedef std::map<std::string, int> map_s_i;
	map_s_i mymap;
	mymap.insert({ "first", 1 });

	typedef std::map<std::string, std::string> map_s_s;
	map_s_s mymap2;
	mymap2.insert({"first","first"});
#endif

#if 0
	//ϣ������һ�����ͣ�ǰ���ⲿ�̶ֹ����䣬��std::map<std::string, �����Լ�ָ��>
	template <typename st>
	struct map_s {  //������һ���ṹ/�ֻ࣬�ǽṹ�ĳ�Աȱʡ����public
		typedef std::map<std::string, st> type;  //������һ������
	};
#endif
#if 0
	map_s<int>::type map1;   //�ȼ���std::map<std::string, int>
	map1.insert({ "first", 1 });
	//����Ϊ��ʵ�����ֱȽ�ͨ�õ���string����Ϊkey������������Ϊvalue(ֵ)��map���������ǲ��ò��Լ�дһ�������ﵽ���Ŀ�ģ�ʵ��
	//�ֶαȽ������

	str_map_t<int> map2;
	map2.insert({ "first", 1 });
#endif
	//using�����ڶ�������(��������ģ��)��ʱ���ǰ�����typedef�����й��ܵġ�
	/*typedef unsigned int uint_t;
	using uint_t = unsigned int;

	typedef std::map<std::string, int> map_s_i;    //typedef�������͵ķ����о��� ����һ������:������ ������
	using map_s_i = std::map<std::string, int>;*/

	//typedef int(*FuncType)(int, int); //��typedef�����庯��ָ��
	//using FuncType = int(*)(int, int); //using�������͵ķ����о���ֵ
#if 0
	myfunc_M<int> pointFunc;   //myfunc_M<int> ��һ������ָ�����ͣ���һ��������
	                           //pointFunc��һ������ָ��
	pointFunc = RealFunc;   //�Ѻ�����ַ��������ָ�����
	cout << pointFunc(1, 6) << endl;
#endif

	//�ܽ᣺
	//using��ʹ������ģ�壬�Ȳ�����ģ�壬Ҳ���Ǻ���ģ�壬���ǿ��Կ�����һ���µ�ģ������:����ģ��(ģ����)

	//������ʾָ��ģ�����
	auto result = sum<double,double,double>(2000000000, 2000000000);  //�ֹ�ָ������������
	cout << result << endl;

	return 0;
}

