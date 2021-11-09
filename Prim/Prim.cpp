#include <iostream>
#include <fstream>
using namespace std;
#define vc 100
#define vmax 20
struct DoThi
{
	int f;
	int n;
	int m[vmax][vmax];
};
int chuaxet[vmax];
void docFile(DoThi& g)
{
	ifstream f;
	f.open("file.txt");
	if (f.eof()) cout << "Khong tim thay file";
	else
	{
		f >> g.f;
		f >> g.n;
		for (int i = 1; i <= g.n; i++)
		{
			for (int j = 1; j <= g.n; j++)
			{
				f >> g.m[i][j];
			}
		}
	}
	f.close();
}
void xuatDoThi(DoThi g)
{
	if (g.f == 0)
		cout << "\ndo thi vo huong";
	else
		cout << "\n Do thi co huong";
	cout << "\nMa tran cua do thi la: ";
	for (int i = 1; i <= g.n; i++)
	{
		cout << endl;
		for (int j = 1; j <= g.n; j++)
			cout << g.m[i][j] << "\t";
	}
}
struct Nhan
{
	int dinh, chiphi;
};
void xuatBangChiPhi(DoThi g, Nhan bang[vmax][vmax])
{
	cout << "\n Bang mo ta thuat toan Prim tim cay khung nho nhat: \n";
	for (int i = 1; i <= g.n; i++)
		cout << "\t" << i;
	for (int i = 0; i <= g.n; i++)
	{
		cout << "\n----------------------------------------------------------------------------------------------\n";
		for (int j = 1; j <= g.n; j++)
		{
			cout << "\t(" << bang[i][j].dinh << "," << bang[i][j].chiphi << ")";
		}
	}
}
void xuatCayKhung(DoThi g, Nhan bang[vmax][vmax])
{
	cout << "\nDanh sach cac canh thuoc cay khung nho nhat\n";
	int i = 2;
	int tongchiphi = 0;
	while (i <= g.n)
	{
		cout << "\t(" << bang[g.n][i].dinh << "," << i << ")";
		tongchiphi += bang[g.n][i].chiphi;
		i++;
	}
	cout << "\nTong chi phi cua cay khung nho nhat la: " << tongchiphi;
}
void Prim(DoThi g, Nhan bang[vmax][vmax], int dinhKhoiDau)
{
	int chuaxet[vmax];
	for (int i = 1; i <= g.n; i++)
	{
		chuaxet[i] = 0;
		bang[0][i].chiphi = vc;
		bang[0][i].dinh = 0;
	}
	bang[0][dinhKhoiDau].chiphi = 0;
	bang[0][dinhKhoiDau].dinh = 0;
	int i = 0;
	while (i < g.n)
	{
		int chondinh_min = 1;
		while (chuaxet[chondinh_min] == 1)
			chondinh_min++;
		for (int j = 1; j <= g.n; j++)
		{
			if (chuaxet[j] == 0 && bang[i][j].chiphi < bang[i][chondinh_min].chiphi)
				chondinh_min = j;
		}
		chuaxet[chondinh_min] = 1;
		i++;
		for (int j = 1; j <= g.n; j++)
		{
			if (chuaxet[j] == 1 || g.m[chondinh_min][j] == vc)
				bang[i][j] = bang[i - 1][j];
			if (chondinh_min != j && chuaxet[j] == 0 && g.m[chondinh_min][j] < vc)
				if (bang[i - 1][j].chiphi > g.m[chondinh_min][j])
				{
					bang[i][j].chiphi = g.m[chondinh_min][j];
					bang[i][j].dinh = chondinh_min;
				}
				else
				{
					bang[i][j] = bang[i - 1][j];
				}
		}
	}

}
int main()
{
	DoThi g;
	docFile(g);
	xuatDoThi(g);
	Nhan bang[vmax][vmax];
	Prim(g, bang, 1);
	xuatBangChiPhi(g, bang);
	xuatCayKhung(g, bang);
	return 0;
}