/*
Complexitatea algoritmului este n^3 datorita inmultirii matricilor sub forma a vectori unidimensionali
*/
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
int pozitie(int i, int j)
{
    if (j > i)
        return -1;
    else
    {
        int poz = (i + 1) * (i + 2) / 2 - (i + 1 - j);
        return poz;
    }
}
void citire(vector<int>&matrice,int& n,int nrMatrice)
{
    ifstream f("input.txt");
    int k = 1, x;
    f >> n;
    for (int i = 0; i < (nrMatrice-1)*n; i++)
        for (int j = 0; j < n; j++)
            f >> x;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            f >> x;
            if (j < i+1)
                matrice.push_back(x);
        }
        k++;
    }
}
void afisare(vector<int> matrice)
{
    for (int i = 0; i < matrice.size(); i++)
        cout << matrice[i] << " ";
}
void produs(vector<int>matrice1, vector<int>matrice2, vector<int>&matrice3,int n)
{
    int size = n*(n + 1) / 2;
    matrice3.resize(size,0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i + 1; j++)
            for (int k = 0; k < i + 1; k++)
            {
                if (pozitie(i, k) == -1 || pozitie(k, j) == -1)
                    matrice3[pozitie(i, j)] += 0;
                else
                    matrice3[pozitie(i, j)] += matrice1[pozitie(i, k)] * matrice2[pozitie(k, j)];
            }
        
}
int main()
{
    vector<int>matrice1,matrice2,matrice3;
    int n;
    citire(matrice1, n,1);
    citire(matrice2, n,2);
    produs(matrice1, matrice2, matrice3, n);
    afisare(matrice3);
    return 0;
}

