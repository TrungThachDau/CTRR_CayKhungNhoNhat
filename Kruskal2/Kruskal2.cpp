#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
using namespace std;
#define vc 100
#define vmax 20

struct DoThi
{
	int flag;	
	int n;		
	int w[vmax][vmax];
};
int chuaxet[vmax];

void docfile(DoThi& g)
{
	ifstream f;
	f.open("file.txt");
	if (f.eof()) cout << "Khong tim thay file";
	else
	{
		f >> g.flag;
		f >> g.n;
		for (int i = 1; i <= g.n; i++)
		{
			for (int j = 1; j <= g.n; j++)
			{
				f >> g.w[i][j];
			}
		}
	}
	f.close();
}
void xuatDoThi(DoThi g)
{
	if (g.flag == 0)
		cout << "\ndo thi vo huong";
	else
		cout << "\n Do thi co huong";
	cout << "\nMa tran cua do thi la: ";
	for (int i = 1; i <= g.n; i++)
	{
		cout << endl;
		for (int j = 1; j <= g.n; j++)
			cout << g.w[i][j] << "\t";
	}
}

struct canh
{
	int u, v;
	int trongso;
};
void sapxepcanhtheotrongso(DoThi g, canh dscanh[], int& m) //m là số cạnh của đồ thị
{
	m = 0;
	for (int i = 1; i <= g.n; i++)
		for (int j = i + 1; j <= g.n; j++)
		{
			if (g.w[i][j] < vc && g.w[i][j] != 0)
			{
				++m;
				dscanh[m].u = i;
				dscanh[m].v = j;
				dscanh[m].trongso = g.w[i][j];
			}
		}

	for (int i = 1; i < m; i++)
	{
		int min = i;
		for (int j = i + 1; j <= m; j++)
			if (dscanh[j].trongso < dscanh[min].trongso)
				min = j;
		if (i != min)
			swap(dscanh[i], dscanh[min]);
	}
}

int timCay(int father[], int i)
{
	while (father[i] > 0) i = father[i];
	return i;
}
void hopCay(int father[], int i, int j)
{
	if (father[i] > father[j])
	{
		father[j] += father[i];
		father[i] = j;
	}
	else
	{
		father[i] += father[j];
		father[j] = i;
	}
}

void xuat_caykhung_kruskal(DoThi g, canh Tree[])
{
	for (int i = 1; i < g.n; i++)
		printf("\n(%d, %d, %d)", Tree[i].u, Tree[i].v, Tree[i].trongso);
}

void Krukal(DoThi g)
{
	int m, n;
	int father[vmax];
	canh dscanh[100], Tree[vmax];

	for (int i = 1; i <= g.n; i++) father[i] = -1;

	sapxepcanhtheotrongso(g, dscanh, m);

	for (int i = 1; i <= m; i++)
	{
		printf("\n(%d, %d, %d)", dscanh[i].u, dscanh[i].v, dscanh[i].trongso);
	}

	n = g.n;
	int i = 1;
	while (n > 1 && i <= m)
	{
		int r1 = timCay(father, dscanh[i].u);
		int r2 = timCay(father, dscanh[i].v);

		if (r1 != r2)
		{
			hopCay(father, r1, r2);
			Tree[--n] = dscanh[i];
		}
		i++;
	}

	/*printf("\ncay khung theo Kruskal: ");

	for (int i = 1; i < g.n; i++)
		printf("\n(%d, %d, %d)", Tree[i].u, Tree[i].v, Tree[i].trongso);*/

}

void main()
{
	DoThi g;
	docfile(g);
	xuatDoThi(g);
	Krukal(g);

}