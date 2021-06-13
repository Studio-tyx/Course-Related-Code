#include <iostream>
#include <fstream>
#include <stack>
const int MAXING = 1 << 28;
const int MAXPOINT = 21;
using namespace std;

struct point {
	int data;
	point* nextpoint;
};//�߽��
struct headPoint
{
	int data;
	point* nextpoint;
};//��ͷ���

//չʾ�ڽӱ�
void show(int m, headPoint headpoints[MAXPOINT]) {

	cout << "�ڽӱ�Ϊ: " << endl;
	for (int i = 1; i <= m; i++) {//��ÿ����ͷչ��
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

//�����ڽӱ�
//�������ڽӱ�
//���ض�����
int construct(headPoint headpoints[MAXPOINT]) {

	ifstream OpenFile("data.txt", ios::in);//���ļ�
	int m;//��ͷ����� 
	int n;//����
	OpenFile >> m >> n;
	for (int i = 1; i <= m; i++)
		headpoints[i].data = i;
	for (int i = 1; i <= n; i++) {
		int a, b;//���ף���β
		OpenFile >> a >> b;

		//�����һ����
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

		//����ڶ����ߣ�����ͼ�ı���˫��ģ�
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
	return m;//���ض�����
}

//DFS�ǵݹ����
//���������������ڽӱ�
void DFS(int m, headPoint headpoints[MAXPOINT]) {

	cout << "DFS���Ϊ: " << endl;
	stack<int> s;//����ջ����
	bool *visited = new bool[m + 1];//�Ƿ��Ѿ�����
	memset(visited, false, m + 1);

	for (int i = 1; i <= m; i++) {//��ÿ������չ�����ʣ���ֹ����ͨͼ��
		if (!visited[i]) {//�ý��δ����
			visited[i] = true;//���ʸý��
			if (i == 1) {
				cout << headpoints[i].data;//��ͨͼ���׽��
			}
			else {
				cout << " & " << headpoints[i].data;//����ͨͼ
			}
			s.push(i);//��ջ
			point *p = headpoints[i].nextpoint;
			while (!s.empty()) {//��ջ�ǿ�ʱ
				while (p) {//��ָ���ǿ�
					if (!visited[p->data]) {
						visited[p->data] = true;//���ʸý��
						cout << " -> " << p->data;
						s.push(p->data);
						p = headpoints[p->data].nextpoint;
					}
					else {//�ظ�������ֱ����һ��
						p = p->nextpoint;
					}
				}
				//���Ϊ��ʱ��ջ
				p = headpoints[s.top()].nextpoint;
				s.pop();
			}
		}
	}
	cout << endl;
}
int main(){

	headPoint headpoints[MAXPOINT];//�����20����ͷ
	for (int i = 0; i < MAXPOINT; i++) {//�ڽӱ��ʼ��
		headpoints[i].data = 0;
		headpoints[i].nextpoint = NULL;
	}
	int m = construct(headpoints);//�����ڽӱ����ض�����

	show(m, headpoints);//չʾ�ڽӱ�
	DFS(m, headpoints);//DFS�ǵݹ����
}
