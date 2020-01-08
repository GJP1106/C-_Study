#include <iostream>
#include <vector>
#include <string>
using namespace std;

//�����������С��eʹ��
struct student {
	int num;
};
//�������ѳ�����ʾ
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
    //һ�����������
	//vector
	//��������һ�ֱ���������Ԫ�ص��������ͣ������������͸о��е���ָ�룬��������ʱ������Ϊ����������ָ�������е�ĳ��Ԫ�ء�
	//string��vector��[], ������[], �����õķ��ʷ�ʽ�����õ�����(��ͨ��)��
	//ͨ�������������ǾͿ��Զ�ȡ�����е�Ԫ��ֵ����string�е�ÿ���ַ����������޸�ĳ����������ָ���Ԫ��ֵ��
	//++��--
	//list��map������ѧ���õ����������������е�Ԫ�ء�
	//���������ĵ���������
#if 0
	vector<int> iv = { 100, 200, 300 };
	vector<int>::iterator iter;        //�����������Ҳ������vector<int>

	//���������ʱ�򣬾Ͱ�������vector<int>::iterator ����һ�����ͣ��������;�ר��Ӧ���ڵ�������
	//��������������Ͷ���һ��������ʱ��������������Ǹ�������������iter����������ǵ�������



	//����������begin() / end()���������������rbegin() / rend()����
	//begin() / end()���� ���� �������͡�rbegin() / rend()���� ���� �������͡�
	//a)begin()����һ������������(��Ҿ����Ϊ����һ��������);

	iter = iv.begin(); //�����������Ԫ�أ���begin���صĵ�������ָ����������еĵ�һ��Ԫ�ء�
    //�൱��iterָ����iv[0];

	//b)end() :����һ������������(��Ҿ����ɷ���һ��������);
	iter = iv.end(); //end���صĵ�����ָ��Ĳ�����ĩ��Ԫ�أ�����ĩ��Ԫ�صĺ�ߣ�����������ô��⣿
	//���Ǿ�����end()ָ�����һ�������ڵ�Ԫ�ء�
#endif
	//c)���һ������Ϊ�գ���ôbegin()��end()���صĵ���������ͬ��
#if 0
	vector<int> iv2;
	vector<int>::iterator iterbegin = iv2.begin();
	vector<int>::iterator iterend = iv2.end();
	if (iterbegin == iterend)
	{
		cout << "����iv2Ϊ��" << endl;
	}
#endif
	//d)
#if 0
	vector<int> iv = { 100, 200, 300 };   //����һ������
	for (vector<int>::iterator iter = iv.begin(); iter != iv.end(); iter++) {
		cout << *iter << endl; //100 200 300
	}

	//����������������Ӻ���ǰ����һ����������ô����������ͱȽϷ��㡣
	//���������(���������)���õ�rbegin(), rend();
	//rbegin():����һ�������������ָ����������ĵ�һ��Ԫ�أ�
	//rend():����һ�������������ָ��������������Ԫ�ص���һ��λ�á�
	//ע��ʹ�÷�������������������������:
	//�������������ʹ�� vector<int>::reverse_iterator
	for (vector<int>::reverse_iterator riter = iv.rbegin(); riter != iv.rend(); riter++) {
		cout << *riter << endl; //100 200 300
	}
#endif

	//�ģ������������
#if 0
	//a) *iter: ���ص�����iter��ָ��Ԫ�ص����á����뱣֤���������ָ�������Ч������Ԫ�أ�
	//����ָ��end()����Ϊend()��ĩ��Ԫ�صĺ�ߣ�Ҳ����end()ָ�����һ�������ڵ�Ԫ�ء�
	vector<int> iv = { 100, 200, 300 };
#if 0 //����д����ʹ��������ʱ����
	vector<int>::iterator iter = iv.end();
	cout << *iter << endl;
#endif
#if 0  //����д��OK
	vector<int>::iterator iter = iv.begin();
	cout << *iter << endl;
#endif


	//b)++iter; iter++;  �õ�����ָ�������е���һ��Ԫ�أ��Ѿ�ָ��end()��ʱ���㲻����++;
#if 0 //������ʹ����ֱ�ӱ���
	vector<int>::iterator iter = iv.end();
	iter++;
#endif
	vector<int>::iterator iter = iv.begin();
	iter++;
	cout << *iter << endl; //OK ������Ϊ200

#endif
	
	//c)--iter��iter--; �õ�����ָ�������е���һ��Ԫ�ء�ָ��ͷԪ�أ��Ͳ�����--
#if 0
	vector<int> iv = { 100, 200, 300 };
#if 0 //��������
	vector<int>::iterator iter = iv.begin();
	iter--;
#endif
	vector<int>::iterator iter = iv.end();
	iter--;
	cout << *iter << endl;  //300
#endif


	//d)iter1 == iter2, iter1 != iter2 �ж������������Ƿ���ȡ�
	//�������������ָ�����ͬһ��Ԫ�أ�����ȣ�����Ͳ��ȡ�

	//e)
#if 0 //�˴���Ҫ�õ���ͷ������Ľṹ��
	vector<student> sv;
	student mystu;
	mystu.num = 100;
	sv.push_back(mystu);  //�Ѷ���mystu��ֵ����sv�����У�

	vector<student>::iterator iter;
	iter = sv.begin();  //ָ���һ��Ԫ��
	cout << (*iter).num << endl;
	cout << iter->num << endl;  //���������ʽ����
#endif

	//��:const_iterator��������const:����
	//const_iterator����������ʾֵ���ܸı����˼�������ֵ���ܸı��ʾ���������ָ���Ԫ�ز��ܸı䣬
	//�����Ǳ�ʾ��������������ܸı䣬Ҳ����˵�������������ǿ��Բ���ָ����һ��Ԫ�أ�
	//ֻ�ܴ������ж�Ԫ�أ�����ͨ�������������д�����е�Ԫ�ء��о�����������ָ�롣
	//iterator���ܶ���д��
#if 0
	vector<int> iv = { 100, 200, 300 };
	vector<int>::const_iterator iter;
	for (iter = iv.begin(); iter != iv.end(); ++iter) {
		//*iter = 4;  //ֱ�ӱ���
		cout << *iter << endl; //����������
	}
#endif

#if 0
	//�������һ��������������ʹ��const_iterator�ͻᱨ��
	const vector<int> iv = {100, 200, 300 };
	//vector<int>::iterator iter;  //��ʹ��const_iterator�ͻᱨ��
	vector<int>::const_iterator iter;  //OK
	for (iter = iv.begin(); iter != iv.end(); ++iter) {
		//*iter = 4;  //ֱ�ӱ���
		cout << *iter << endl; //����������
	}
#endif

#if 0
	//(5.1)cbegin()��cend()����
	//c++11����������º���cbegin(), cend(),��begin, end���ơ�cbegin, cend�����صĶ��ǳ�����������
	vector<int> iv = { 100, 200, 300 };
	for (auto iter = iv.cbegin(); iter != iv.cend(); ++iter) {
		//*iter = 4; //�������ܸ�������ֵ����˵��cbegin���ص��ǳ�����������
		cout << *iter << endl;
	}
#endif

	//��:������ʧЧ
	vector<int> vecvalue{ 1, 2, 3, 4, 5 };
#if 0
	//�������
	for (auto vecitem : vecvalue) {
		cout << vecitem << endl;
	}
	//�����������
	for (auto vecitem : vecvalue) {
		vecvalue.push_back(1);   //������������ݻ���
		cout << vecitem << endl;
	}
#endif

#if 0
	//������ �������
	for (auto beg = vecvalue.begin(), end = vecvalue.end(); beg != end; ++beg) {
		cout << *beg << endl;
	}
	//���������
	for (auto beg = vecvalue.begin(), end = vecvalue.end(); beg != end; ++beg) {
		vecvalue.push_back(1);   //������������ݻ���
		cout << *beg << endl;
	}
#endif

	//�ڲ����������Ĺ�����(ʹ���˵���������ѭ����)��ǧ��Ҫ�ı�vector������������Ҳ���ǲ�Ҫ���ӻ���ɾ��vector�����е�Ԫ�ء�
	//�����������ӻ��ߴ�������ɾ��Ԫ�أ���Щ�������ܻ�ʹָ������Ԫ�ص�ָ�롢���á�������ʧЧ��
	//ʧЧ�ͱ�ʾ�����ڴ����κ������е�Ԫ�أ�һ��ʹ��ʧЧ�Ķ������͵��ڷ������صĳ�����󣬺ܶ�����£������ֱ�ӱ�����
#if 0
	//vector,list,map
	for (auto beg = vecvalue.begin(), end = vecvalue.end(); beg != end; ++beg) {
		vecvalue.push_back(1);   //push��֮��Ҫ�����˳�����Ҫ�������������ɱ���������⡣
		break;
	}
	for (auto beg = vecvalue.begin(), end = vecvalue.end(); beg != end; ++beg) {
		cout << *beg << endl;
	}
#endif

	//(6.1)���ѳ�����ʾ1
#if 0  //����һ
	auto beg = vecvalue.begin();
	auto end = vecvalue.end();
	while (beg != end) {
		cout << *beg << endl;
		//������������begin���λ�ò�����ֵ��������insert
		vecvalue.insert(beg, 80);   //������ֵ����һ������Ϊ����λ�ã��ڶ�������Ϊ����Ԫ�ء�
		                            //������һ���룬�϶��ᵼ�µ�����ʧЧ������begin, endʧЧ��
		                            //�����ĸ�������ʧЧ��ȡ�����������vector�ڲ���ʵ��ԭ�����ǿ��Բ�������ϸ�о���
		                            //�������ǲ�̫��ȷ�ĸ�������ʧЧ�ˣ������ǵ���������������ֻҪһ�������ݣ�������Ͼ�break��ѭ���塣
		break;   //�����ǵķ�ֹ������ʧЧ�ķ��������������ܱ���
		++beg; //��Ҫ���ǣ�����Ҫ����ѭ��ĩβ
	}

	beg = vecvalue.begin();
	end = vecvalue.end();
	while (beg != end) {
		cout << *beg << endl;
		++beg; //��Ҫ���ǣ�����Ҫ����ѭ��ĩβ
	}

#endif
#if 0   //������
	auto beg = vecvalue.begin();
	int icount = 0;
	while (beg != vecvalue.end()) {   //ÿ�θ���end��ֹendʧЧ
		beg = vecvalue.insert(beg, icount + 80);  //insert�ķ��ؽ���Ҿ�Ҫ����
		icount++;
		if (icount > 10)
			break;
		++beg;
	}
	beg = vecvalue.begin();
	auto end = vecvalue.end();
	while (beg != end) {
		cout << *beg << endl;
		++beg;  //��Ҫ���ǣ�����Ҫ����ѭ��ĩβ
	}
#endif

	//(6.2)���ѳ�����ʾ2

	vector<int> iv = { 100, 200, 300 };
#if 0 //��������
	for (auto iter = iv.begin(); iter != iv.end(); ++iter) {
		iv.erase(iter);   //erase����,�Ƴ�iterλ���ϵ�Ԫ�أ�������һ��Ԫ��λ�á�
	}
#endif
#if 0 //ɾ������ȷ����1
	vector<int>::iterator iter = iv.begin();
	vector<int>::iterator iterend = iv.end();
	while (iter != iv.end()) {
		iter = iv.erase(iter);
	}
#endif
#if 0 //����Ч��ɾ������2
	while (!iv.empty()) {
		auto iter = iv.begin();  //��Ϊ��Ϊ�գ����Է���begin()ʱû���⡣
		iv.erase(iter);  //ɾ����λ���ϵ�Ԫ��
	}
#endif

	//�ߣ�������ʾ
	//7.1) �õ���������һ��string���͵�����
#if 0
	string str("I Love China!");
	for (auto iter = str.begin(); iter != str.end(); ++iter) {
		*iter = toupper(*iter);
	}
	cout << str << endl;
#endif
	//7.2)vector�������ò������ڴ��ͷ�
	//ʵ������:
	conf *pconf1 = new conf;
	strcpy_s(pconf1->itemname, sizeof(pconf1->itemname), "ServerName");
	strcpy_s(pconf1->itemcontent, sizeof(pconf1->itemcontent), "1��");

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

	//����Ҫ�ͷ��ڴ棬�Լ�new�ľ�Ҫ�Լ��ͷţ����������ڴ�й©
	std::vector<conf *>::iterator pos;
	for (pos = conflist.begin(); pos != conflist.end(); ++pos) {
		delete (*pos);   //*pos�����Ǹ�ָ��
	}

	conflist.clear();   //���Ҫ��Ҫ���� 

}