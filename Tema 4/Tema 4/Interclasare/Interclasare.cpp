#include <fstream>
#include <vector>
#include <iostream>
#include <limits>
void operator == (std::vector<int>& a,std::vector<int> b) 
{
	a.resize(b.size());
	a = b;
}
struct heap {
    int lung=0;
    std::vector<std::vector<int>> H;
};
std::vector<int> interclasare(std::vector<int> a, std::vector<int> b)
{
	int i = 0, j = 0,p=0,m=a.size(),n=b.size();
	std::vector<int> c;
	c.resize(m + n);
	while (i < m && j < n)
		if (a[i] < b[j])
			c[p++] = a[i++];
		else
			c[p++] = b[j++];
	while (i < m)
		c[p++] = a[i++];
	while (j < n)
		c[p++] = b[j++];
	return c;
}
void increase(std::vector<std::vector<int>>& H, int i, std::vector<int> val)
{
	if (val.size() < H[i].size())
	{
		
		H[i] == val;
		int p = (i - 1) / 2;
		while (i > 0 && H[p].size() > val.size())
		{
			H[i] == H[p];
			i = p;
			p = (i - 1) / 2;
		}
		H[i] == val;
	}
}
void insert(std::vector<std::vector<int>>& H, int& lung, std::vector<int> val)
{
	H.resize(lung + 1);
	int temp=INT_MAX;
	H[lung].resize(100);
	lung++;
	increase(H, lung - 1, val);
}
void citire(heap& coada)
{
	std::ifstream f("input.txt");
	int n;
	f >> n;
	for (int i = 0; i < n; i++)
	{
		int temp;
		f >> temp;
		std::vector<int> val;
		val.resize(temp);
		for (int j = 0; j < temp; j++)
			f >> val[j];
		insert(coada.H, coada.lung, val);
			
	}
}
void parcurgere(heap& coada)
{
	while (coada.H.size() > 1)
	{
		std::vector <int> temp = interclasare(coada.H[0], coada.H[1]);
		swap(coada.H[0], coada.H[coada.H.size() - 1]);
		swap(coada.H[1], coada.H[coada.H.size() - 2]);
		int temp1 = coada.H.size() - 2;
		coada.H.resize(temp1);
		coada.lung -= 2;
		insert(coada.H, coada.lung, temp);
	}
}
int main()
{
	heap coada;
	citire(coada);
	parcurgere(coada);
	for (int i = 0; i < coada.H[0].size(); i++)
		std::cout << coada.H[0][i] << " ";
	    std::cout<< std::endl;
		std::cout << coada.H[0].size();
}

