#ifndef __MYVECTOR__
#define __MYVECTOR__

//������ģ��
template<typename T>  //����ΪT��ģ�������������ʾmyvector��������������Ԫ������
class myvector
{
public:
	typedef T* myiterator; //��������vector iterator

public:
	myvector();  //���캯��
	myvector& operator=(const myvector&);  //��ֵ��������ء�����ģ���ڲ�ʹ��ģ����������Ҫ�ṩģ�������
	//myvector<T>& operator=(const myvector<T>&);
public:
	myiterator mybegin();  //����������ʼλ��
	myiterator myend();  //�����������һ��Ԫ�ص��¸�λ��

public:
	//void myfunc() { //�ѳ�Ա�����ĺ�����(��������ʵ��)������ģ��Ķ����С�

	//}
	void myfunc();
};
//��ͨ����
template<typename T>
void myvector<T>::myfunc() {
	return;
}

//���캯��
template<typename T>
myvector<T>::myvector() {
	//return;
}

template<typename T>
myvector<T>& myvector<T>::operator=(const myvector&)   //<T>��ʾ���ص���һ��ʵ�����˵�myvector
{
	return *this;
}

template<typename T>
//typename�ı�����
//(a)::�ڶ����÷����������ͳ�Աmyiterator (typedef)��
//typename�����Ŀ��(�ô�)���Ǹ��߱�����myitorator��һ������
typename myvector<T>::myiterator myvector<T>::mybegin()
{

}







#endif