#pragma once
#include<iostream>
#define MAXSIZE 100
using namespace std;

typedef struct BiTNode {  //�������Ĵ洢�ṹ 
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct //����Ϊ������ջ�Ĵ洢�ṹ 
{
	BiTree *base;
	BiTree *top;
	int stacksize;
} SqStack;

void InitStack(SqStack &S);	//��ʼ��ջ
bool StackEmpty(SqStack S);	//�ж�ջ�Ƿ�Ϊ��
int Push(SqStack &S, BiTree e);	//�����Ľ��ѹ��ջ��
int Pop(SqStack &S, BiTree &e);	//��ջ�Ľ�㵯������
void createBiTree(BiTree &T);	//��ʼ����
int FirstOrderTraverse(BiTree T);	//�ݹ�����������Ҷ�ӽ��
int FirstOrderTraverse_1(BiTree T);	//�ǵݹ�����������Ҷ�ӽ��


