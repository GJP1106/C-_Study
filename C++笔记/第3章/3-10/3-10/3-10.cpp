// 3-10.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "human.h"
#include "men.h"
#include "women.h"

int main()
{
	//һ��RTTI��ʲô(Run Time Identification)����ʱ����ʶ��
	//ͨ������ʱ����ʶ�𣬳����ܹ�ʹ�û����ָ����������������Щָ�����������ָ�Ķ����ʵ���������͡�
	//Human *phuman = new Men;
	//Human &q = *phuman; //*phuman��ʾָ��phuman��ָ��Ķ���
	//RTTI���ǿ��԰�����ƺ�������һ��ϵͳ�ṩ�����ǵ�һ������������һ�ֹ��ܡ����ֹ��ܻ���������ͨ��2������������֣�
	//(1)dynamic_cast�����:�ܹ��������ָ��������ð�ȫ��ת��Ϊ�������ָ��������á�
	//(2)typeid�����:����ָ�����������ָ�����ʵ�����͡�
	//���䣺Ҫ����RTTI������������ܹ�������������ô�����б�������Ҫ��һ���麯������Ȼ����������������Ľ���Ϳ��ܸ�����Ԥ�ڲ�һ����
	//��Ϊֻ���麯���Ĵ��ڣ�������������Ż�ʹ��ָ������������󶨵Ķ���Ķ�̬����(��new������)
	//phuman->eat();
	//phuman->menfunc();

	//����dynamic_cast������������������ܹ�ת���ɹ���˵�����ָ��ʵ������Ҫת�������Ǹ����͡����������ܹ�����������ȫ���
	//Human *phuman = new Men;
	//Men *p = (Men *)(phuman);  //��c���Է���ǿ������ת����Ӳ��ָ��ת����Men *;
	//p->testfunc();  //�ܹ������ĵ���Men��ĳ�Ա����testfunc()

	//Women *p1 = (Women *)(phuman);//Ҳ��ת�����ǻ��з�������Ŀ���

	//Men *pmen = dynamic_cast<Men *>(phuman);
	//if (pmen != nullptr) {
		//std::cout << "phumanʵ����һ��Men����" << std::endl;
		//�����������Men��ߵĳ�Ա��������Ա�������ܹ��������Ұ�ȫ�Ĳ���
		//pmen->testfunc();
	//}
	//else {
		//ת��ʧ��
		//std::cout << "phumanʵ�ʲ�����һ��Men����" << std::endl;
	//}

	//�������ã������dynamic_castת��ʧ�ܣ���ϵͳ���׳�һ��std::bad_cast�쳣��try()...catch(){}
	//Human *phuman = new Men;
	//Human &q = *phuman;  //���������
	//try {
	//	Men &menbm = dynamic_cast<Men &>(q); //ת�����ɹ���������ֱ�ӽ��뵽catch���ȥ�����ת���ɹ������̼��������ߡ�
	//	std::cout << "phumanʵ������һ��Men����" << std::endl;
	//	//�����������Men�ĳ�Ա�������ǰ�ȫ��
	//	menbm.testfunc();
	//}
	//catch(std::bad_cast){
	//	std::cout << "phumanʵ���ϲ���һ��Men����" << std::endl;
	//}


	//����typeid�����
	//typeid(����); Ҳ����typeid(���ʽ);
	//�ǵ�����������Ϣ��typeid�ͻ᷵��һ�� ������������ã������������ ��һ����׼�����ͣ�type_info(��/����)
	//Human *phuman = new Men;
	//Human &q = *phuman;
	//std::cout << typeid(*phuman).name() << std::endl;  //class Men
	//std::cout << typeid(q).name() << std::endl; //class Men
	//char a[10] = { 5, 1 };
	//int b = 120;
	//std::cout << typeid(a).name() << std::endl;  //char [10]
	//std::cout << typeid(b).name() << std::endl;  //int

	//typeid��Ҫ��Ϊ�˱Ƚ�����ָ���Ƿ�ָ��ͬһ�����͵Ķ���
	//(1)����ָ�붨���������ͬ(Human);��������new����ɶ��typeid�����
	//������̫�������ǵ����κ�Ҫ��
	/*Human *phuman1 = new Men;
	Human *phuman2 = new Men;
	if (typeid(phuman1) == typeid(phuman2)) {
		std::cout << "phuman1��phuman2��ͬһ������[��ָ�붨��]" << std::endl;
	}*/
	//�Ƚ϶���ʱ��������new���������ĸ�������߸�ָ��ָ������ĸ����󣬺Ͷ����ָ��ʱ���������û��ϵ��
	//Human *phuman = new Men;
	//Men *phuman2 = new Men;
	//Human *phuman3 = phuman2;
	//if (typeid(*phuman) == typeid(*phuman2)) {  //ǧ��Ҫ��*����
	//	std::cout << "phuman��phuman2��ͬһ������" << std::endl;
	//}
	//if (typeid(*phuman2) == typeid(*phuman3)) {
	//	std::cout << "phuman2��phuman3��ͬһ������" << std::endl;
	//}

	//Human *phuman = new Men;
	//if (typeid(*phuman) == typeid(Men)) {
	//	std::cout << "Phumanָ��Men" << std::endl;
	//}
	//else if (typeid(*phuman) == typeid(Human)) {  //���û���麯������if����
	//	std::cout << "Phumanָ��humen" << std::endl;
	//}
    //�������Ҫ���麯���������ϱߵ�������������
	//�мǣ�ֻ�е��������麯��ʱ���������Ż��typeid()�еı��ʽ��ֵ���������ĳ�����Ͳ������麯����
	//��typeid()���ص�ʽ���ʽ�ľ�̬����(����ʱ������),��Ȼ�Ƕ�������ͣ��������Ͳ���Ҫ�Ա��ʽ��ֵҲ��֪�����ʽ�ľ�̬����

	//�ġ�type_info��
	//typeid�ͻ᷵��һ�� ������������ã������������ ��һ����׼�����ͣ�type_info(��/����)
#if 0
	//a)name: ����
	Human *phuman = new Men;
	const type_info &tp = typeid(*phuman);
	std::cout << tp.name() << std::endl;  //class Men

	//b) == ��!= 
	Human *phuman1 = new Men;
	const type_info &tp1 = typeid(*phuman1);
	if (tp == tp1) {
		std::cout << "tp==tp1������ͬ" << std::endl;
	}
	Human *phuman3 = new Women;
	const type_info &tp2 = typeid(*phuman3);
	if (tp == tp2) {
		std::cout << "tp==tp2������ͬ" << std::endl;
	}
#endif
	//�ġ�RTTI���麯����
	//c++�У���������溬���麯�����������ͻ�Ը������һ���麯����
	//�麯�������кܶ��ÿһ��� һ��ָ�롣ÿ��ָ��ָ������������ĸ����麯������ڵ�ַ��
	//�麯���������һ����������⣬��ָ��Ĳ����麯������ڵ�ַ����ָ���ʵ�����������������������type_info����
	Human *phuman = new Men;
	const type_info &ty = typeid(*phuman);

	//phuman��������һ�����ǿ�������ָ�룬���ָ��ָ��˭��ָ���������������ڵ���Men����麯����



	return 0;
}

