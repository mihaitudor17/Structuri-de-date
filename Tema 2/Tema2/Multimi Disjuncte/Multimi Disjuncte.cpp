/* Complexitatea algoritmului tinde catre n patrat deoarece intreaga matrice de pixeli este parcursa 
pentru a afla coordonatele pixelilor din care se compun imaginile*/
#include <vector>
#include <iostream>
#include <stack>
#include <fstream>
using namespace std;
struct coord {
	int x;
	int y;
};
void citire(vector<vector<int>>& input, int& n, int& m)
{
	ifstream f("input.txt");
	f >>n>>m;
	input.resize(n);
	for (int i = 0; i < n; i++)
		input[i].resize(m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			f >> input[i][j];
}
int vecini(vector<vector<int>> input, int i, int j,int& nrVec,int n, int m)
{
	int dir = 0;
	nrVec = 0;
	if (i > 0 && input[i - 1][j] == 1)
	{
		nrVec++;
		dir = 1;
	}
	if (j > 0 && input[i][j - 1] == 1)
	{
		nrVec++;
		dir = 2;
	}
	if (i < n - 1 && input[i + 1][j] == 1)
	{
		nrVec++;
		dir = 3;
	}
	if (j < m - 1 && input[i][j + 1] == 1)
	{	nrVec++;
		dir = 4;
	}
	if (j < m - 1&&i<n-1 && input[i+1][j + 1] == 1)
	{
		nrVec++;
		dir = 5;
	}
	if (j < m - 1 && i>0 &&input[i-1][j + 1] == 1)
	{
		nrVec++;
		dir = 6;
	}
	if (j > 0 && i > 0 && input[i - 1][j - 1] == 1)
	{
		nrVec++;
		dir = 7;
	}
	if (i < n - 1 && j>0&& input[i+1][j - 1] == 1)
	{
		nrVec++;
		dir = 8;
	}
	
	return dir;
}
int parcurgere(vector<coord>& pixel, vector<vector<int>> &input,int n,int m)
{
	stack< coord > ramificatie;
	int nrVec, obiecte = 0, maxim = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int i1 = i, j1 = j,OK=0,nr=0;
			while (input[i1][j1] == 1||OK==1)
			{
				OK = 0;
				int dir = vecini(input, i1, j1, nrVec, n, m);
				if (nrVec > 1)
				{
					coord temp;
					temp.x = i1;
					temp.y = j1;
					ramificatie.push(temp);
				}
				if (input[i1][j1] == 1)
				{
					coord temp;
					temp.x = i1;
					temp.y = j1;
					pixel.push_back(temp);
					input[i1][j1] = 0;
					nr++;
				}
				switch (dir)
				{
				case 1:
					i1--;
					break;
				case 2:
					j1--;
					break;
				case 3:
					i1++;
					break;
				case 4:
					j1++;
					break;
				case 5:
					j1++;
					i1++;
					break;
				case 6:
					j1++;
					i1--;
					break;
				case 7:
					j1--;
					i1--;
					break;
				case 8:
					j1--;
					i1++;
					break;
				}
				if (dir==0&&!ramificatie.empty())
				{
					coord temp = ramificatie.top();
					i1 = temp.x;
					j1 = temp.y;
					ramificatie.pop();
					OK = 1;
				}
					
			}
			if (nr != 0)
			{
				if (nr > maxim)
					maxim = nr;
				obiecte++;
				coord temp = { -1,-1 };
				pixel.push_back(temp);
			}
			
		}

	cout << "Nr obiecte este: " << obiecte << endl;
	cout << "Nr maxim de nr este: " << maxim << endl;
	return obiecte;
}
void obiecte(vector<coord>pixel, vector<vector<vector<int>>>& imagini)
{
	int nrOb = 0;
	for (int i = 0; i < pixel.size(); i++)
	{
		if (pixel[i].x != -1)
		{
			int i1 = i, minimL = pixel[i].x, minimC = pixel[i].y, maximL = 0, maximC = 0;
			while (pixel[i1].x != -1)
			{
				if (pixel[i1].x < minimL)
					minimL = pixel[i1].x;
				if (pixel[i1].x > maximL)
					maximL = pixel[i1].x;
				if (pixel[i1].y > maximC)
					maximC = pixel[i1].y;
				if (pixel[i1].y < minimC)
					minimC = pixel[i1].y;
				i1++;
			}
			int n = maximL - minimL + 1, m = maximC - minimC + 1;
			vector<vector<int>> temp;
			temp.resize(n);
			for (i1 = 0; i1 < n; i1++)
				temp[i1].resize(m);
			i1 = i;
			while (pixel[i1].x != -1)
			{
				temp[pixel[i1].x-minimL][pixel[i1].y-minimC] = 1;
				i1++;
			}
			imagini[nrOb]=temp;
			nrOb++;
			i = i1;
		}
	}
}
void afisare(vector<vector<vector<int>>> imagini)
{

	for (int i = 0; i < imagini.size(); i++)
	{
		for (int j = 0; j < imagini[i].size(); j++)
		{
			for (int k = 0; k < imagini[i][j].size(); k++)
				cout << imagini[i][j][k] << " ";
			cout << endl;
		}
		cout << endl;
	}
}
int main()
{
	vector<vector<int>> input;
	vector<vector<vector<int>>> imagini;
	vector<coord> pixel;
	int n, m;
	citire(input, n, m);
	int temp=parcurgere(pixel, input, n, m);
	imagini.resize(temp);
	obiecte(pixel, imagini);
	afisare(imagini);
	return 0;
}