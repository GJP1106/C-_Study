#include <iostream>
using namespace std;



unique_ptr<string> tuniqp() {
	unique_ptr<string> pr(new string("I love china"));
	return pr;  //�Ӻ�������һ���ֲ���unique_ptr����
	            //�������ֶ��󣬵���ϵͳ����������һ����ʱunique_ptr���󣬵���unique_ptr���ƶ����캯����
}
void mydelete(string *pdel) {
	delete pdel;
	pdel = nullptr;
}

int main() {

	//һ������unique_ptr
	//��Ȼunique_ptr����ָ�벻�ܿ��������ǣ������unique_ptr��Ҫ�����٣��ǿ��Կ����ġ�������÷����ǴӺ�������һ������
#if 0
	unique_ptr<string> ps;
	ps = tuniqp();  //������ps���ӣ�����ʱ����ֱ�ӹ�����ps�������ӣ�����ʱ����ᱻ�ͷţ�ͬʱ���ͷŵ���ָ��Ķ���
#endif

	//��:ָ��ɾ������delete��Ĭ��ɾ����
	//a)ָ��ɾ����
	//��ʽ��unique_ptr<ָ��Ķ������ͣ�ɾ����> ����ָ�������;
	//ɾ�������ɵ��ö��󣬱��纯���������ء�
	//����ѧϰ��shared_ptrɾ�������Ƚϼ�shared_ptr<int> p(new int(),mydelete);
	//unique_ptrɾ������Ը���һ�㣬����һ������Ҫ������ģ������д��ݽ�ȥ��������Ȼ���ڲ������ٸ������ɾ��������
#if 0
	typedef void(*fp)(string *);  //����һ������ָ�����ͣ�������Ϊfp��
	unique_ptr<string, fp> ps1(new string("I love china"), mydelete);

	using fp2 = void(*)(string *);  //��using����һ������ָ�����ͣ�������Ϊfp2
	unique_ptr<string, fp2> ps2(new string("I love china"), mydelete);

	typedef decltype(mydelete) * fp3;   //�������һ��*����Ϊdecltyoe���ص��Ǻ�������void(string *)
	                                    //��*��ʾ����ָ�����ͣ�����fp3Ӧ���� void *(string *)
	unique_ptr<string, fp3> ps3(new string("I love china"), mydelete);

	unique_ptr<string, decltype(mydelete)*> ps4(new string("I love china"), mydelete);
#endif
	//��lambda���ʽ  ����д����lambda���ʽ�������ɴ���operator()�����Ͷ���
#if 0
	auto mydella = [](string *pdel) {  //��lambda���ʽ����һ��class
		delete pdel;
		pdel = nullptr;
	};
	unique_ptr<string, decltype(mydella)> ps3(new string("I love china"), mydella);
#endif

	//b)ָ��ɾ��������˵��
	//shared_ptr:��������shared_ptrָ����ɾ��������ͬ��ֻҪ������ָ��Ķ�����ͬ����ô������shared_ptrҲ����ͬһ������
	//����unique_ptr��һ����ָ��unique_ptr�е�ɾ�����ͻ�Ӱ��unique_ptr�����ͣ����Դ��������˵��shared_ptr��Ƶĸ����
	//�����ڽ���shared_ptr��ʱ��ɾ������ͬ����ָ������һ����shared_ptr�����Էŵ�ͬһ�������vector<shared_ptr...>
	//unique_ptr��� ɾ������ͬ����ô�͵�������unique_ptr���Ͳ�ͬ���������Ͳ�ͬ��unique_ptr����ָ����û�а취�ŵ�ͬһ���������

	//�����ߴ����⣺ͨ������£�unique_ptr�ߴ����ָ��һ����
#if 0
	string *p;
	int ilenp = sizeof(p); //4�ֽ�
	unique_ptr<string> ps1(new string("I love china"));
	int ilen = sizeof(ps1); //4�ֽ�

	//������������Լ���ɾ��������unique_ptr�ĳߴ�������ӣ�Ҳ���ܲ�����
	//a)���lambda���ʽ����ɾ�������ߴ��û�仯
	auto mydella = [](string *pdel) {  //��lambda���ʽ����һ��class
		delete pdel;
		pdel = nullptr;
	};
	unique_ptr<string, decltype(mydella)> ps3(new string("I love china"), mydella);
	int ilen1 = sizeof(ps3);  //4�ֽ�
	//b)����һ��������Ϊɾ����
	typedef void(*fp)(string *);
	unique_ptr<string, fp> psl(new string("I love china"),mydelete);
	int ilen2 = sizeof(psl);
#endif
	//�����ֽڶ�Ч����Ӱ�죬�����Զ���ɾ����Ҫ���ã�
	//shared_ptr,������ָ��ʲôɾ������shared_ptr�ĳߴ綼����ָ���2��

	//�ġ�����ָ���ܽ�
	//(4.1)����ָ�뱳������˼��
	//����ָ����ҪĿ��:���������ͷ��ڴ棬�Է�ֹ���������ͷ��ڴ�ʱ��ɵ��ڴ�й©
	//c++98 auto_ptr = unique_ptr
	//(4.2)auto_ptrΪʲô������
	//auto_ptr:c++98ʱ��������ָ�룬����unique_ptr�Ĳ������ԣ�unique_ptr shared_ptr weak_ptr
	//�����������б��棬Ҳ���ܴӺ����з���auto_ptr;
	auto_ptr<string> ps(new string("I love china"));
	auto_ptr<string> ps2 = ps;           //ps2ָ���ַ�����ps��ɿ��ˣ�����Է�ֹps��ps2����һ��string����
	//��ps(��û����ʶ��ps�Ѿ�����),����ͻ������
	//���Ҳ��auto_ptr�÷��ϵ�һ������

	//��Ȼauto_ptr��unique_ptr���Ƕ�ռʽ�ģ���unique_ptr��������������ʱ��ͻᱨ��
	//������ĬĬ�İ�ps������Ȩת�Ƶ�ps2�ϣ�����������ʹ��ps���³�����������⣻
	//��Ȼ��������ƶ����壬Ҳ�ܴﵽauto_ptr��Ч��
	unique_ptr<string> ps3(new string("I love china"));
	unique_ptr<string> ps4 = std::move(ps3);   //�������ƶ�����

	//auto_ptr����������Ҫԭ����:��ƵĲ�̫�ã����ױ���������Ǳ�ڵĳ���������⡣����c++11������unique_ptr��ȡ��auto_ptr
	//c++11��ʾ��������ʹ��auto_ptr����ʦǿ�ҽ����ң���unique_ptrȡ����unique_ptr��auto_ptr����ȫ

	//(4.3)����ָ���ѡ��
	//shared_ptr��unique_ptr;
	//a)�������Ҫʹ�ö��ָ��ͬһ�������ָ�룬Ӧ��ѡ��shared_ptr;
	//b)���������ҪҪʹ�ö��ָ��ͬһ�������ָ�룬Ӧ��ѡ��unique_ptr;
	









	return 0;
}