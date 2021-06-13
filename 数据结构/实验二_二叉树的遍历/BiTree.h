#pragma once
#include<iostream>
#define MAXSIZE 100
using namespace std;

typedef struct BiTNode {  //二叉树的存储结构 
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct //以树为基础的栈的存储结构 
{
	BiTree *base;
	BiTree *top;
	int stacksize;
} SqStack;

void InitStack(SqStack &S);	//初始化栈
bool StackEmpty(SqStack S);	//判断栈是否为空
int Push(SqStack &S, BiTree e);	//将树的结点压入栈中
int Pop(SqStack &S, BiTree &e);	//将栈的结点弹出至树
void createBiTree(BiTree &T);	//初始化树
int FirstOrderTraverse(BiTree T);	//递归先序遍历求非叶子结点
int FirstOrderTraverse_1(BiTree T);	//非递归先序遍历求非叶子结点


