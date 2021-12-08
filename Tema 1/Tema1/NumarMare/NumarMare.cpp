/*
Numarul este memorat intr-un vector de cifre, iar acesta este impartit pe bucati pentru 
a cauta cifrele maxime de dupa un anumit pivot. Acest algoritm duce la o complexitate de tipul
(n-p)*n, unde p este numarul de cifre "taiate". 
*/
#include <iostream>
#include<vector>
#include<math.h>
#include<algorithm>
#include <fstream>
using namespace std;
void citire(int& n,int& p, long int& numar)
{
    ifstream f("input.txt");
    f >> n;
    f >> p;
    f >> numar;
}
void afisare(vector<int>nrMaxim)
{
    for (int i = 0; i < nrMaxim.size(); i++)
        cout << nrMaxim[i];
}
int cautare(long int numar,int n, vector<int>&nrMaxim,int st, int dr)
{   
    if (dr != n)
    {
        int maxim = -1, poz = -1;
        for (int i = dr; i > st; i--)
        {
            int u = (long int)(numar / pow(10, n - 1 - i)) % 10;
            if (u > maxim)
            {
                maxim = u;
                poz = i;
            }
        }
        nrMaxim.push_back(maxim);
        return cautare(numar,n, nrMaxim, poz, dr + 1);
    }
    return 0;
}
int main()
{
    int n,p;
    long int numar;
    vector<int>nrMaxim;
    citire(n,p, numar);
    cautare(numar,n, nrMaxim, 0, n - p + 1);
    cout << nrMaxim.size() << endl;
    afisare(nrMaxim);
    return 0;
}

