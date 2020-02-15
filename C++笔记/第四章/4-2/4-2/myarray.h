#ifndef __MYARRAY__
#define __MYARRAY__

template<typename T, int size = 10>
class myarray {
private:
	T arr[size];

public:
	void myfunc();
};
template<typename T, int size>
void myarray<T,size>::myfunc()
{
	cout << size << endl;
	return;
}



#endif