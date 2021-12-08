/*Programul nu foloseste spatiu suplimentar( spirala parcursa nu este memorata, ci este doar simulata)
iar complexitatea programului este una patratica, intrucat in cel mai rau caz programul va parcurge 
n*n numere pentru a ajunge la rezultat*/
#include <iostream>
#include <fstream>
using namespace std;
void citire(int &n,int &p)
{
	ifstream f("input.txt");
	f >> n >> p;
}
int strat(int n, int p)
{
	for (int i = 1; i < n; i++)
		if (p <= i * n * n)
			return i;
}
void impar(int n, int p)
{
	int x = 0, y = 0;
	int z = strat(n, p);
	int poz = (z - 1) * n * n + 1;
	int i = poz;
	if (poz == p)
		cout << x << " " << y << " " << z;
	else
	{
		while (i < poz + n * n)
		{
			while (x + y != n - 1 && i < poz + n * n)
			{
				y++;
				i++;
				if (i == p)
				{
					cout << x << " " << y << " " << z;
					i = n * n * n;
				}
			}
			while (x != y && i < poz + n * n)
			{
				x++;
				i++;
				if (i == p)
				{
					cout << x << " " << y << " " << z;
					i = n * n * n;
				}
			}
			while (x + y != n - 1 && i < poz + n * n)
			{
				y--;
				i++;
				if (i == p)
				{
					cout << x << " " << y << " " << z;
					i = n * n * n;
				}
			}
			while (x - 1 != y && i < poz + n * n)
			{
				x--;
				i++;
				if (i == p)
				{
					cout << x << " " << y << " " << z;
					i = n * n * n;
				}
			}
		}
	}
}
void par(int n, int p)
{
	int x = (n-1)-(n-1)/2, y = (n-1)/2;
	int z = strat(n, p);
	int poz = (z - 1) * n * n + 1;
	int i = poz;
	if (poz == p)
		cout << x << " " << y << " " << z;
	else
	{
		while (i < poz + n * n)
		{
			while (x != y && i < poz + n * n)
			{
				y++;
				i++;
				if (i == p)
				{
					cout << x << " " << y << " " << z;
					i = n * n * n;
				}
			}
			while (x +y != n - 1 && i < poz + n * n)
			{
				x--;
				i++;
				if (i == p)
				{
					cout << x << " " << y << " " << z;
					i = n * n * n;
				}
			}
			while (x -1!= y && i < poz + n * n)
			{
				y--;
				i++;
				if (i == p)
				{
					cout << x << " " << y << " " << z;
					i = n * n * n;
				}
			}
			while (x + y != n-1 && i < poz + n * n)
			{
				x++;
				i++;
				if (i == p)
				{
					cout << x << " " << y << " " << z;
					i = n * n * n;
				}
			}
		}
	}
}
void spirala(int n,int p) 
{
	int z = strat(n, p);
	if (z % 2 == 1)
		impar(n, p);
	else
		par(n, p);
}
void prime(int n)
{
	for (int i = 1; i <= n; i++)
	{
		int sum = 0;
		for (int poz = n * n * (i - 1) + 1; poz < n * n * i; poz++)
		{
			int ok = 0;
			for (int div = 2; div * div <= poz; div++)
				if (poz % div == 0)
				{
					ok = 1;
					div = poz;
				}
			if (ok == 0&&poz!=1)
				sum++;
		}
		cout << endl;
		cout << "Pe latura " << i << " se gasesc " << sum << " nr prime";
	}
}
int main()
{
	int n, p;
	citire(n, p);
	spirala(n, p);
	prime(n);
	return 0;

}
