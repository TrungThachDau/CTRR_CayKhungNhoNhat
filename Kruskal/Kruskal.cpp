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
struct canh
{
	int u, v;
	int trongso;
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
void sapxepcanhtheotrongso(DoThi g, canh dscanh[], int& m)
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
void Kruskal(DoThi g)
{
	int chuaxet[vmax];
	canh dscanh[100];
	int m;
	for (int i = 1; i <= g.n; i++)
	{
		chuaxet[i] = 0;
	}
	int socanh = 0;
	canh T[vmax];
	int sotplt = 0;
	sapxepcanhtheotrongso(g, dscanh, m);
	for (int i = 1; i <= m; i++)
	{
		printf("\n(%d, %d, %d)", dscanh[i].u, dscanh[i].v, dscanh[i].trongso);
	}
	for (int i = 1; i <= m; i++)
	{
		if (chuaxet[dscanh[i].u] == 0 && chuaxet[dscanh[i].v] == 0)
		{
			socanh++;
			T[socanh] = dscanh[i];
			sotplt++;
			chuaxet[dscanh[i].u] == sotplt;
			chuaxet[dscanh[i].v] == sotplt;
		}
		else
		{
			if (chuaxet[dscanh[i].u] == 0 && chuaxet[dscanh[i].v] != 0)
			{
				socanh++;
				T[socanh] = dscanh[i];
				chuaxet[dscanh[i].u] = chuaxet[dscanh[i].v];
			}
			else
			{
				if (chuaxet[dscanh[i].u] != 0 && chuaxet[dscanh[i].v == 0])
				{
					socanh++;
					T[socanh] = dscanh[i];
					chuaxet[dscanh[i].v] = chuaxet[dscanh[i].u];
				}
				else
				{
					if (chuaxet[dscanh[i].u] != chuaxet[dscanh[i].v])
					{
						socanh++;
						T[socanh] = dscanh[i];
						int j = 1;
						int tam = chuaxet[dscanh[i].v];
						while (j <= g.n)
						{
							if (chuaxet[j] == tam)
								chuaxet[j] = chuaxet[dscanh[i].u];
							j++;
						}
					}
				}
			}
			if (socanh == g.n - 1)
				break;
		}

	}

}
int main()
{
	DoThi g;
	docfile(g);
	xuatDoThi(g);
	Kruskal(g);
	return 0;
}