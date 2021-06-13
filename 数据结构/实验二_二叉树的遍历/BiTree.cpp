#include "BiTree.h"
#include <iostream>
using namespace std;

//创造一个空栈
void InitStack(SqStack &S){ 
	S.base = new BiTree[MAXSIZE];
	if (!S.base) exit(-2);
	S.top = S.base;
	S.stacksize = MAXSIZE;
}

//判断栈是否为空
bool StackEmpty(SqStack S){
	if (S.top == S.base) return true;
	else return false;
}

//将树的结点压入栈中
int Push(SqStack &S, BiTree e){ 
	if (S.top - S.base == S.stacksize)return -1;
	*(S.top++) = e;
	return 1;
}

//将栈的结点弹出至树
int Pop(SqStack &S, BiTree &e){  
	if (S.top == S.base) return 0;
	e = *(--S.top);
	return 1;
}

//初始化树
void createBiTree(BiTree &T) {  
	char ch;
	cin >> ch;
	if (ch == '#')T = NULL;	//“#”为叶子结点 
	else {
		T = new BiTNode;
		T->data = ch;
		createBiTree(T->lchild);	//创建左子树 
		createBiTree(T->rchild);	//创建右子树 
	}
}

//递归先序遍历求非叶子结点
int FirstOrderTraverse(BiTree T) {  
	if (T == NULL)return 0;
	else if (T->lchild != NULL || T->rchild != NULL) {
		//cout << T->data << endl;	
		return FirstOrderTraverse(T->lchild) + FirstOrderTraverse(T->rchild) + 1;
	}
	else return FirstOrderTraverse(T->lchild) + FirstOrderTraverse(T->rchild);
}

//非递归先序遍历求非叶子结点
int FirstOrderTraverse_1(BiTree T) {
	SqStack S;	//借助栈实现非递归先序遍历
	int count = 0;
	InitStack(S);
	BiTree p, q;
	p = T;
	q = new BiTNode;
	while (p || !StackEmpty(S)) {
		if (p) {	//没到底
			if (p->lchild != NULL || p->rchild != NULL) {
				count++;
				//cout << p->data << endl;
			}
			Push(S, p);	//压栈
			p = p->lchild;
		}
		else {	//到底了
			Pop(S, q);	//弹栈
			p = q->rchild;
		}
	}
	return count;
}