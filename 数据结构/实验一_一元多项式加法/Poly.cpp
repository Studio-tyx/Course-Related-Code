#include "Poly.h"
#include<iostream>
#include<iomanip>
using namespace std;
Poly::Poly() {

}

Poly::~Poly() {

}

//初始化
//输入数据PolyArray与多项式项数n
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

//打印多项式
void Poly::Print() {
	this->Sort();
	cout << "输出二项式：" << endl;
	PolyNode *tmp = Head->next;
	if (Head == NULL){
		cout << "这是一个空二项式！" << endl;
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

//按指数排序
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

//多项式加法
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
		else{//指数相等
			p->coef = p->coef + q->coef;
			if (p->coef == 0){//相加为零
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

