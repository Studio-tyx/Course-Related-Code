#include <iostream>
#include "BiTree.h"
using namespace std;

int main(){
	BiTree T = nullptr;
	cout << "请按照先序遍历的顺序输入一个二叉树（空树以#标记）:" << endl;
	createBiTree(T);
	cout << "二叉树创建成功！" << endl;
	cout << "对二叉树查找非叶子结点" << endl;
	cout << "递归结果为:" << FirstOrderTraverse(T) << endl;
	cout << "非递归结果为:" << FirstOrderTraverse_1(T) << endl;
	return 0;
}