#pragma once
const int maxN = 20;

//用于初始化的数组
struct PolyArray{
	float coef;
	int exp;
};

//单独结点
struct PolyNode{
	float coef;
	int exp;
	PolyNode *next;
};

//链表
class Poly{
private:
	PolyNode *Head;
public:
	Poly();
	~Poly();
	void Create(PolyArray *a, int n);//初始化
	void Print();//打印多项式
	void Sort();//多项式按指数排序
	void Add(Poly LB);//多项式加法
};

