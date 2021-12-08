#include <iostream>
#include <vector>
#include <fstream>
struct coada {
	std::vector<int> H;
	int lung = 0;
};
void increase(std::vector<int>& H, int i, int val)
{
	if (val > H[i])
	{
		H[i] = val;
		int p = (i - 1) / 2;
		while (i > 0 && H[p] < val)
		{
			H[i] = H[p];
			i = p;
			p = (i - 1) / 2;
		}
		H[i] = val;
	}
}
void insert(std::vector<int>& H,int& lung,int val)
{
	H.resize(lung + 1);
	H[lung] = 0;
	lung++;
	increase(H, lung - 1, val);
}
void citire(std::vector<int>& frecv)
{
	int n;
	std::ifstream f("input.txt");
	f >> n;
	frecv.resize(n);
	for (int i = 0; i < n; i++)
		f >> frecv[i];
}
int calcul(std::vector<int>& frecv)
{
	int maxim = 0, poz = -1;
	for (int i = 0; i < frecv.size(); i++)
		if (frecv[i] * (i+1) > maxim)
		{
			maxim = frecv[i] * (i+1);
			poz = i;
		}
	frecv[poz]--;
	return maxim;
}
void parcurgere(std::vector<int> frecv)
{
	coada prioritate;
	int n;
	std::cout << "Introduceti numarul biletului: ";
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		int temp = calcul(frecv);
		insert(prioritate.H, prioritate.lung, temp);
	}
	std::cout << "Costul biletului este: ";
	int temp = prioritate.lung - 1;
	std::cout << prioritate.H[temp];
}
int main()
{
	std::vector<int>frecv;
	citire(frecv);
	parcurgere(frecv);
	return 0;
}
