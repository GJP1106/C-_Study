#ifndef _CA_H__
#define __CA_H__

template <typename C>
class A {  //��ͨ��
public:
	template <typename T2>
	A(T2 v1, T2 v2);
	//A(T2 v1, T2 v2) {  //���캯������Ҳ�����Լ���ģ�壬���������ģ��Cû�й�ϵ

	//}

	template <typename T>
	void myft(T tmpt) {   //��Ա����ģ��
		cout << tmpt << endl;
	}
	void myftpt() {}
	C m_ic;
};

template <typename C>  //�ȸ����ģ������б�
template <typename T2> //�ٸ����캯���Լ���ģ������б�
A<C>::A(T2 v1, T2 v2) {
	cout << v1 << v2 << endl;
}

template <typename T>
void myfunc123(T v1, T v2) {
	cout << v1 + v2 << endl;
}


#endif