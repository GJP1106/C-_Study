#include <iostream>
using namespace std;


class A {
public:
	A() {

	}
	~A() {

	}
};



auto myfunc() {
	return unique_ptr<string>(new string("I lova china"));  //��ֵ
}





int main() {

	//һ��unique_ptr����
	//��ռʽ�ĸ���(ר������Ȩ):ͬһ��ʱ�̣�ֻ����һ��unique_ptrָ��ָ���������(����ڴ�);
	//�����unique_ptr�����ٵ�ʱ������ָ��Ķ���Ҳ�����٣�
	//��ʽ:
	//unique_ptr<ָ��Ķ�������> ����ָ�������;
	//(1.1)�����ʼ��(unique_ptr��new���)
#if 0
	unique_ptr<int> pi;   //����ָ��int�����һ��������ָ��
	if (pi == nullptr) {
		cout << "piĿǰ���ǿ�ָ��" << endl;
	}
	unique_ptr<int> pi2(new int(105));  //��ʱpi2ָ��һ��ֵΪ105��int����
#endif

	//(1.2)make_unique����
	//c++11��û�У�c++14���е�make_unique;��֧��ָ����ɾ�����﷨���������ɾ��������������ѡ��ʹ�ã����ߵ����ܡ�
	unique_ptr<int> p1 = make_unique<int>(100);
	auto p2 = make_unique<int>(200);
	unique_ptr<int> pi2(new int(105));  //ǰ�߲��ܼ�дΪauto

	//����unique_ptr���ò���
	//(2.1)unique_ptr��֧�ֵĲ���(��ռʽ)
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	//unique_ptr<string> ps2(ps1);  //������ָ�벻֧�ֿ�������(����ʱ��ʼ��)
	//unique_ptr<string> ps3 = ps1);  //������ָ�벻֧�ֿ�������(����ʱ��ʼ��)
	//unique_ptr<string> ps4;  
	//ps4 = ps1;                       //������ָ�벻֧�ֿ�������(����ʱ��ʼ��)
#endif

	//(2.2)�ƶ�����
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	unique_ptr<string> ps2 = std::move(ps1);   //�ƶ���ɺ�ps1Ϊ�գ�ps2ָ��ԭ��ps1�Ķ���
#endif

	//(2.3)release();  ������ָ��Ŀ���Ȩ(�ж�������ָ�������ָ��Ķ���֮�����ϵ)��
	       //������ָ�룬��������ָ���ÿա����ص������ָ�����ǿ����ֹ�delete���ͷţ�Ҳ����������ʼ������һ������ָ�룬���߸�����һ������ָ�븳ֵ��
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	unique_ptr<string> ps2(ps1.release());
	if (ps1 == nullptr) {
		cout << "ps1���ÿ�" << endl;
	}
	ps2.release();  //������ڴ�й©����Ҫdelete
	//��ȷ����
	string *tempp = ps2.release();
	delete tempp;
#endif
	//(2.4)reset()
	//reset()�����������:�ͷ� ����ָ����ָ��Ķ��󣬲�������ָ���ÿ�
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	ps1.reset();
	if (ps1 == nullptr) {
		cout << "ps1���ÿ�" << endl;
	}
#endif
	//reset()�����������:�ͷ� ����ָ����ָ��Ķ��󣬲��ø�����ָ��ָ���¶���
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	unique_ptr<string> ps2(new string("I love china"));
	ps1.reset(ps2.release());  //reset�ͷ�ps1ָ��Ķ����ڴ棬��ps1ָ��ps2��ָ����ڴ棬ͬʱps2���ÿ�
	ps1.reset(new string("I love"));
#endif

	//(2.5) = nullptr:�ͷ�����ָ����ָ��Ķ��󣬲�������ָ���ÿ�
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	ps1 = nullptr;
#endif

	//(2.6)ָ��һ������
#if 0
	unique_ptr<int[]> ptrarray(new int[10]);   //ע�⣬��������Ҫ����[]
	ptrarray[0] = 12;
	ptrarray[1] = 15;

	//���ﲻҪ����A[],����������Լ��������������ᱨ�쳣
	unique_ptr<A[]> pA(new A[10]);
#endif
	//(2.7)get();  ��������ָ���б������ָ��
	//���ǵ���Щ����������Ҫ����������ָ��(����������⣬���Ǹ��Ĳ��˴���)����������ú���
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	string *ps = ps1.get();
	*ps = "This is a test!";
	//delete ps; //��Ҫ��ô�ɣ������������Ԥ�ϵĺ��
#endif

	//(2.8) *������ ����ȡ������ָ��ָ��Ķ��󣬿���ֱ�Ӳ���
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	*ps1 = "This is a test~";
	unique_ptr<int> pt1(new int(100));
	*pt1 = 200;

	unique_ptr<int[]> pt2(new int[10]); //���ڶ�������������飬��û��*�������������
	//*pt2[0] = 100;
#endif

	//(2.9) swap():������������ָ����ָ��Ķ���
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	unique_ptr<string> ps2(new string("I love china2"));
	std::swap(ps1, ps2);
	ps1.swap(ps2);
#endif
	//(2.10)����ָ��������Ϊ�ж�����
#if 0
	unique_ptr<string> ps1(new string("I love china"));
	if (ps1) {
		//��ps1ָ��һ��������ô����ͳ���
		cout << "ps1��Ϊ��" << endl;
	}
	ps1.reset();
	if (ps1) {
		cout << "ps1��Ϊ��" << endl;
	}
	else {
		cout << "ps1Ϊ��" << endl;
	}
#endif

	//(2.11)ת����shared_ptr���ͣ����unique_ptrΪ��ֵ���Ϳ��Խ�����ֵ��shared_ptr
	//��Ϊshared_ptr����һ����ʾ���캯���������ڽ���ֵunique_ptrת��Ϊshared_ptr,shared_ptr���ӹ�ԭ����unique_ptr��ӵ�еĶ���
#if 0
	shared_ptr<string> pss1 = myfunc();   //����ᴴ�����ƿ�

	unique_ptr<string> ps(new string("I Love china"));
	shared_ptr<string> pss2 = std::move(ps);   //��ֵת��ֵ��ִ�к�psΪ�գ�pss2����shared_ptr
#endif












	return 0;
}