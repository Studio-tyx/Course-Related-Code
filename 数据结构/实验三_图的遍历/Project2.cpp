#include <iostream>
#include <fstream>
#include <stack>
const int MAXING = 1 << 28;
const int MAXPOINT = 21;
using namespace std;

struct point {
	int data;
	point* nextpoint;
};//边结点
struct headPoint
{
	int data;
	point* nextpoint;
};//表头结点

//展示邻接表
void show(int m, headPoint headpoints[MAXPOINT]) {

	cout << "邻接表为: " << endl;
	for (int i = 1; i <= m; i++) {//对每个表头展开
		cout << headpoints[i].data;
		point *p = headpoints[i].nextpoint;
		while (p) {
			cout << " -> " << p->data;
			p = p->nextpoint;
		}
		cout << endl;
	}
	cout << endl;
}

//构造邻接表
//参数：邻接表
//返回顶点数
int construct(headPoint headpoints[MAXPOINT]) {

	ifstream OpenFile("data.txt", ios::in);//打开文件
	int m;//表头结点数 
	int n;//边数
	OpenFile >> m >> n;
	for (int i = 1; i <= m; i++)
		headpoints[i].data = i;
	for (int i = 1; i <= n; i++) {
		int a, b;//边首，边尾
		OpenFile >> a >> b;

		//构造第一条边
		point* newpoint1 = new point;
		newpoint1->data = b;
		newpoint1->nextpoint = NULL;
		if (headpoints[a].nextpoint == NULL)
			headpoints[a].nextpoint = newpoint1;
		else {
			//point* tmppoint = new point;
			point*tmppoint = headpoints[a].nextpoint;
			while (tmppoint->nextpoint != NULL) {
				tmppoint = tmppoint->nextpoint;
			}
			tmppoint->nextpoint = newpoint1;
			//delete tmppoint;
		}

		//构造第二条边（无向图的边是双向的）
		point* newpoint2 = new point;
		newpoint2->data = a;
		newpoint2->nextpoint = NULL;
		if (headpoints[b].nextpoint == NULL)
			headpoints[b].nextpoint = newpoint2;
		else {
			//point* tmppoint = new point;
			point*tmppoint = headpoints[b].nextpoint;
			while (tmppoint->nextpoint != NULL) {
				tmppoint = tmppoint->nextpoint;
			}
			tmppoint->nextpoint = newpoint2;
			//delete tmppoint;
		}
	}
	return m;//返回顶点数
}

//DFS非递归遍历
//参数：顶点数与邻接表
void DFS(int m, headPoint headpoints[MAXPOINT]) {

	cout << "DFS结果为: " << endl;
	stack<int> s;//借助栈遍历
	bool *visited = new bool[m + 1];//是否已经访问
	memset(visited, false, m + 1);

	for (int i = 1; i <= m; i++) {//对每个顶点展开访问（防止不连通图）
		if (!visited[i]) {//该结点未访问
			visited[i] = true;//访问该结点
			if (i == 1) {
				cout << headpoints[i].data;//连通图的首结点
			}
			else {
				cout << " & " << headpoints[i].data;//不连通图
			}
			s.push(i);//入栈
			point *p = headpoints[i].nextpoint;
			while (!s.empty()) {//当栈非空时
				while (p) {//所指结点非空
					if (!visited[p->data]) {
						visited[p->data] = true;//访问该结点
						cout << " -> " << p->data;
						s.push(p->data);
						p = headpoints[p->data].nextpoint;
					}
					else {//重复访问则直接下一个
						p = p->nextpoint;
					}
				}
				//结点为空时弹栈
				p = headpoints[s.top()].nextpoint;
				s.pop();
			}
		}
	}
	cout << endl;
}
int main(){

	headPoint headpoints[MAXPOINT];//设最大20个表头
	for (int i = 0; i < MAXPOINT; i++) {//邻接表初始化
		headpoints[i].data = 0;
		headpoints[i].nextpoint = NULL;
	}
	int m = construct(headpoints);//构造邻接表并返回顶点数

	show(m, headpoints);//展示邻接表
	DFS(m, headpoints);//DFS非递归遍历
}
