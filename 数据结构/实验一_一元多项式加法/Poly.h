#pragma once
const int maxN = 20;

//���ڳ�ʼ��������
struct PolyArray{
	float coef;
	int exp;
};

//�������
struct PolyNode{
	float coef;
	int exp;
	PolyNode *next;
};

//����
class Poly{
private:
	PolyNode *Head;
public:
	Poly();
	~Poly();
	void Create(PolyArray *a, int n);//��ʼ��
	void Print();//��ӡ����ʽ
	void Sort();//����ʽ��ָ������
	void Add(Poly LB);//����ʽ�ӷ�
};

