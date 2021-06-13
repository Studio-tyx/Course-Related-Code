#include "BiTree.h"
#include <iostream>
using namespace std;

//����һ����ջ
void InitStack(SqStack &S){ 
	S.base = new BiTree[MAXSIZE];
	if (!S.base) exit(-2);
	S.top = S.base;
	S.stacksize = MAXSIZE;
}

//�ж�ջ�Ƿ�Ϊ��
bool StackEmpty(SqStack S){
	if (S.top == S.base) return true;
	else return false;
}

//�����Ľ��ѹ��ջ��
int Push(SqStack &S, BiTree e){ 
	if (S.top - S.base == S.stacksize)return -1;
	*(S.top++) = e;
	return 1;
}

//��ջ�Ľ�㵯������
int Pop(SqStack &S, BiTree &e){  
	if (S.top == S.base) return 0;
	e = *(--S.top);
	return 1;
}

//��ʼ����
void createBiTree(BiTree &T) {  
	char ch;
	cin >> ch;
	if (ch == '#')T = NULL;	//��#��ΪҶ�ӽ�� 
	else {
		T = new BiTNode;
		T->data = ch;
		createBiTree(T->lchild);	//���������� 
		createBiTree(T->rchild);	//���������� 
	}
}

//�ݹ�����������Ҷ�ӽ��
int FirstOrderTraverse(BiTree T) {  
	if (T == NULL)return 0;
	else if (T->lchild != NULL || T->rchild != NULL) {
		//cout << T->data << endl;	
		return FirstOrderTraverse(T->lchild) + FirstOrderTraverse(T->rchild) + 1;
	}
	else return FirstOrderTraverse(T->lchild) + FirstOrderTraverse(T->rchild);
}

//�ǵݹ�����������Ҷ�ӽ��
int FirstOrderTraverse_1(BiTree T) {
	SqStack S;	//����ջʵ�ַǵݹ��������
	int count = 0;
	InitStack(S);
	BiTree p, q;
	p = T;
	q = new BiTNode;
	while (p || !StackEmpty(S)) {
		if (p) {	//û����
			if (p->lchild != NULL || p->rchild != NULL) {
				count++;
				//cout << p->data << endl;
			}
			Push(S, p);	//ѹջ
			p = p->lchild;
		}
		else {	//������
			Pop(S, q);	//��ջ
			p = q->rchild;
		}
	}
	return count;
}