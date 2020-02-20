#include <iostream>
using namespace std;

shared_ptr<int> create(int value) {
	return make_shared<int>(value);   //����һ��shared_ptr
}


//void myfunc(int value)
shared_ptr<int> myfunc(int value) {
	shared_ptr<int> ptmp = create(10);
	//return;  //�뿪�������ptmp�ᱻ�Զ��ͷţ�����ָ����ڴ�Ҳ�ᱻ�Զ��ͷ�
	return ptmp;
}
void proc(shared_ptr<int> ptr) {
	return;
}

class CT : public enable_shared_from_this<CT>{
public:
	shared_ptr<CT> getself() {
		//return shared_ptr<CT>(this);   //����ָ���ʼ���˶��shared_ptr�ĸо�
		return shared_from_this();  //�������enable_shared_from_this���еķ�����Ҫͨ���˷�����������ָ��
	}
};

class CB;
class CA {
public:
	shared_ptr<CB> m_pbs;
	~CA() {
		int test;
		test = 1;
	}
};
class CB {
public:
	//shared_ptr<CA> m_pas;
	weak_ptr<CA> m_pas;
	~CB() {
		int test;
		test = 1;
	}
};

int main() {

	//һ��std::shared_ptrʹ�ó���
#if 0
	myfunc(12);  //�����鲻��shared_ptr����������myfunc���صĽ������ô��myfunc���ص�shared_ptr�ͻᱻ����
	auto p11 = myfunc(12);  //��������һ����������myfunc�ķ���ֵ����ômyfunc���ص�shared_ptr�Ͳ��ᱻ���٣�����ָ��Ķ���Ҳ���ᱻ����
#endif

	//����std::shared_ptrʹ�����������һ���ô�Ҳ��������
	//(2.1)������ָ��
#if 0
	int *p = new int(100);   //��ָ��
	//proc(p); //�﷨��int *p����ת����shared_ptr<ptr>
	proc(shared_ptr<int>(p));  //�����Ǹ���ʱ��shared_ptr����һ����ָ����ʽ�Ĺ���
	//*p = 45; //Ǳ�ڵĲ���Ԥ�ϵ����⣬��Ϊpָ����ڴ��Ѿ����ͷ���
	//����д��OK
	shared_ptr<int> p2(p);
	proc(p2);
	*p2 = 5;
	//��һ����ͨ��ָ��󶨵���һ��shared_ptr֮�����ڴ��������ξͽ��������shared_ptr�ˣ����ʱ����Ͳ�Ӧ������
	  //��ָ��(����ָ��)������shared_ptr��ָ����ڴ��ˣ�

	//����Ҫ��ס����Ҫ����ָ���ʼ�����shared_ptr
#if 0   //�������д��
	int *p3 = new int(100);  //��ָ��
	shared_ptr<int> pi(p);
	shared_ptr<int> pi1(p);  //pi��pi1�޹�����(pi��pi1ÿ��ǿ���ü�����Ϊ1��)���ᵼ��pi��pi1��ָ����ڴ汻�ͷ����Σ������쳣
#endif

	shared_ptr<int> mp(new int);
	shared_ptr<int> mp1(mp);  //����д����OK�ģ�mp��mp1ָ��ͬһ���ڴ��ַ���������ǻ�ͨ(�õ���ͬһ�����ƿ�)
#endif

	//(2.2)����get()���ص�ָ��
	//��������ָ��ָ��Ķ�������Ӧ����ָ��(��Щ�����ӿڿ���ֻ��ʹ����ָ��)
#if 0
	//get���ص�ָ�벻��delete��������쳣
	shared_ptr<int> myp(new int(100));
	int *p = myp.get();
	//delete p;  //������ɾ�����ᵼ���쳣

	//���ܽ���������ָ���get���ص�ָ����
	shared_ptr<int> myp1(new int(100));
	int *p = myp1.get();   //���ָ��ǧ���������ͷţ�����myp��û�취���������ָ����
	{
		//shared_ptr<int> myp2(p);  //�ᱨ�������쳣������myp1��myp2���ü�����Ϊ1����һ�������������飻�ͱ�Ϊ0��
		shared_ptr<int> myp2(myp1);  //����дOK
	}
	//�뿪�ϱ����myp2�ķ�Χ������myp1ָ����ڴ汻�ͷ��ˣ�
	*myp1 = 65;   //���ڴ��Ѿ����ͷţ�������ֵ�ᵼ�²���Ԥ�ϵĺ��
	//���ۣ���Զ��Ҫ��get�õ���ָ������ʼ������һ������ָ����߸���һ������ָ�븳ֵ
#endif

	//(2.3)��Ҫ�������ָ��(this)��Ϊshared_ptr���أ�����enable_shared_from_this
#if 0
	shared_ptr<CT> pct(new CT);
	//shared_ptr<CT> pct1 = pct;  //��������ǿ����
	shared_ptr<CT> pct2 = pct->getself();  //�������
	//�õ�c++��׼����ߵ���ģ��:enable_shared_from_this
	//���ڣ������洴��CT���������ָ���Լ�ͨ��CT���󷵻ص�this����ָ�붼�ǰ�ȫ�ģ�
	//���enable_shared_from_this����һ����ָ��weak_ptr�������ָ���ܹ�����this��
	 //�����ǵ���shared_from_this()�������ʱ����������ڲ�ʵ�����ǵ��������weak_ptr��lock()������
	  //���֪��lock()��������shared_ptrָ�����+1��ͬʱ�������shared_ptr��������ǹ���ԭ��
#endif

	//(2.4)����ѭ������:�ܹ������ڴ�й©
	//MFC��ʾ�ڴ�й©
	//shared_ptr<CA> pca(new CA);
	//shared_ptr<CB> pcb(new CB);
	//pca->m_pbs = pcb;       //�ȼ���ָ��CB�Ķ���������ǿ����
	//pcb->m_pas = pca;       //�ȼ���ָ��CA�Ķ���������ǿ����
#if 0
	shared_ptr<CA> pca(new CA);
	shared_ptr<CB> pcb(new CB);
	pca->m_pbs = pcb;       //�ȼ���ָ��CB�Ķ���������ǿ����
	pcb->m_pas = pca;       //��Ϊm_pas�������ã���������ָ��CA�Ķ���ֻ��һ��ǿ���ã��뿪������֮��pca���ü�����1�ͱ��0���ͷ�CA����(CA������������ִ��)��
	                        //CA����������ִ����(��ʾ���󼴽����ͷ�)������CA�ڵ�m_pbs���ü������һ��Ҳ����ָ��CB��������ü�����һ
	                        //����pcb������ʱָ��CB�ļ���Ҳ��-1�����գ�����һ��ʱ�̣�ָ��CB�����ǿ���ü������1����0
#endif

	//��������˵��
	//shared_ptr�ĳߴ�����ָ���2���� weak_ptr�ߴ���ָ���2����
#if 0
	char *p;
	int ilenp = sizeof(p);  //4�ֽ�
	shared_ptr<string> p1;
	int ilenp = sizeof(p1); //8�ֽ� ����������ָ��

	//a)��һ����ָ��ָ������������ָ����ָ��Ķ���
	//b)�ڶ�����ָ��ָ�����һ���ܴ�����ݽṹ(���ƿ�)��������ƿ������ɶ��
	       //1)��ָ�����ǿ���ü���:shared_ptr
	       //2)��ָ����������ü���:weak_ptr
	       //3)�������ݣ�����ɾ����ָ�룬�ڴ������
	//������ƿ����ɵ�һ��ָ��ĳ�������shared_ptr��������
	//���ƿ鴴����ʱ��:
	//a)make_shared:���䲢��ʼ��һ�����󣬷���ָ��˶����shared_ptr,���ԣ����make_shared�������ܹ�����һ�����ƿ��
	shared_ptr<int> p2 = make_shared<int>(100);
	//b)����ָ��������һ��shared_ptr����ʱ��
	int *pi = new int();
	shared_ptr<int> p1(pi);
	//shared_ptr<int> p2(pi);  //��������������������ƿ飬Ҳ���Ƕ�����ü���(ÿ������1)������ʱ������Σ������쳣

	shared_ptr<int> p3(new int);//������ôʹ��
#endif
	//(3.2)�ƶ�����
	shared_ptr<int> p1(new int());
	shared_ptr<int> p2(std::move(p1));  //�ƶ����壬�ƶ�����һ���µ�����ָ�����p2
	                                    //p1�Ͳ�����ָ��ö���(��ɿ�)�����ü���������1��
	shared_ptr<int> p3;
	p3 = std::move(p2);  //�ƶ���ֵ��p2ָ��գ�p3ָ��ö��������������ü����Ծ�Ϊ1��

	//�ƶ��϶��ȸ��ƿ죬������Ҫ�������ü������ƶ�����Ҫ��
	//�ƶ����캯��������ƹ��캯�����ƶ���ֵ��������������ֵ�����

	//�ġ�����˵����ʹ�ý���
	//�����˾��󲿷�shared_ptr�÷���С����û�������Լ�����
	//������������ڴ�������⣻
	//shared_ptr<int> p(new int),mydeleter(),mymallocator<int>);

	//����ʹ�ã�������ʦû�������÷���

	//����ʹ��make_shared(),�����Լ������Լ���ɾ����
	shared_ptr<string> psl(new string("I love china"));  //���������ڴ�
	auto ps2 = make_shared<string>("I love china"); //����1���ڴ�














	return 0;
}  