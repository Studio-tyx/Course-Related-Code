#include"Poly.h"
#include<iostream>
using namespace std;

int main() {
	Poly LA;
	Poly LB;
	PolyArray a[] = { {7.0,0},{3.0,1},{9.0,8},{5.0,16} };
	PolyArray b[] = { {8.0,1},{22,7},{-9.0,8} };
	LA.Create(a, 4);
	LA.Print();
	LB.Create(b, 3);
	LB.Print();
	LA.Add(LB);
	cout << "两式相加为:" << endl;
	LA.Print();
	return 0;
}