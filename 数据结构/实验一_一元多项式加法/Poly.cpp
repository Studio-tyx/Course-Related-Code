#include "Poly.h"
#include<iostream>
#include<iomanip>
using namespace std;
Poly::Poly() {

}

Poly::~Poly() {

}

//��ʼ��
//��������PolyArray�����ʽ����n
void Poly::Create(PolyArray *a, int n){
	Head = new PolyNode;
	PolyNode *s, *r;
	r = Head;
	for (int i = 0; i < n; i++){
		s = new PolyNode;
		s->coef = a[i].coef;
		s->exp = a[i].exp;
		s->next = NULL;
		r->next = s;
		r = s;
	}
}

//��ӡ����ʽ
void Poly::Print() {
	this->Sort();
	cout << "�������ʽ��" << endl;
	PolyNode *tmp = Head->next;
	if (Head == NULL){
		cout << "����һ���ն���ʽ��" << endl;
		return;
	}
	while (tmp != NULL){
		cout << "(" << fixed << setprecision(2) << tmp->coef << "x^" << tmp->exp << ")";
		tmp = tmp->next;
		if (tmp != NULL) {
			cout << "+";
		}
	}
	cout << endl;
}

//��ָ������
void Poly::Sort() {
	PolyNode *p, *q;
	int exp; 
	float coef;
	for (p = Head->next; p != NULL; p = p->next) {
		for (q = p->next; q != NULL; q = q->next) {
			if ((p->exp) > (q->exp)){
				exp = p->exp;
				coef = p->coef;
				p->exp = q->exp;
				p->coef = q->coef;
				q->exp = exp;
				q->coef = coef;
			}
		}
	}
}

//����ʽ�ӷ�
void Poly::Add(Poly LB) {
	PolyNode* pre = Head, *p = pre->next;
	PolyNode* qre = LB.Head, *q = qre->next;
	PolyNode* temp = NULL;
	while (p != NULL && q != NULL){
		if (p->exp < q->exp){
			pre = p;
			p = p->next;
		}
		else if (p->exp > q->exp){
			temp = q->next;
			pre->next = q;
			q->next = p;
			pre = q;
			q = temp;
			qre->next = q;
		}
		else{//ָ�����
			p->coef = p->coef + q->coef;
			if (p->coef == 0){//���Ϊ��
				pre->next = p->next;
				delete p;
				p = pre->next;
			}
			else{
				pre = p;
				p = p->next;
			}
			qre->next = q->next;
			delete q;
			q = qre->next;
		}
	}
	if (p == NULL)
		pre->next = q;
	LB.Head->next = NULL;
}

