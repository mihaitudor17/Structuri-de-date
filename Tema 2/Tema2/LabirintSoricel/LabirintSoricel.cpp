/*
Complexitatea algoritmului este influentata de catra locatia startului si a finalului, in cel mai rau caz aceasta fiin n^2 iar in cel mai bun caz fiin lineara. Algoritmul 
foloseste un BFS pentru a gasi cel mai scurt drum catre final, iar apoi parcurge aceasta cale pentru a o afisa si a modifica matricea initiala corespunzator.
*/
#include <queue>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
void citire(vector<vector<int>>& labirint, queue<int>& x, queue<int>& y)
{
    int n, m;
    ifstream f("input.txt");
    f >> n >> m;
    labirint.resize(n);
    for (int i = 0; i < n; i++)
        labirint[i].resize(m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            int temp;
            f >> temp;
            labirint[i][j] = temp;
        }
    cout << "Introduceti coordonata x a soarecelui: ";
    int l;
    cin >> l;
    cout << "Introduceti coordonata y a soarecelui: ";
    int c;
    cin >> c;
    while (labirint[l][c] == -1)
    {
        cout << "Introduceti o coordonata valabila: ";
        cin >> c;
    }
    x.push(l);
    y.push(c);
    cout << "Introduceti coordonata x a branzei: ";
    cin >> l;
    cout << "Introduceti coordonata y a branzei: ";
    cin >> c;
    x.push(l);
    y.push(c);
}
int vecini(vector<vector<int>>&labirint, int i, int j,int mutari,queue<int>&x,queue<int>&y)
{
    int nrVec = 0;
    if (i > 0 && labirint[i - 1][j] == 0)
    {
        x.push(i - 1);
        y.push(j);
        labirint[i - 1][j] = mutari;
        nrVec++;
    }
    if (j > 0 && labirint[i][j - 1] == 0)
    {
        x.push(i);
        y.push(j - 1);
        labirint[i][j - 1] = mutari;
        nrVec++;
    }
    if (i < labirint.size() - 1 && labirint[i + 1][j] == 0)
    {
        x.push(i + 1);
        y.push(j);
        labirint[i + 1][j] = mutari;
        nrVec++;
    }
    if (j < labirint[0].size() - 1 && labirint[i][j + 1] == 0)
    {
        x.push(i);
        y.push(j + 1);
        labirint[i][j + 1] = mutari;
        nrVec++;
    }
    return nrVec;
}
void drumInapoi(vector<vector<int>>labirint,int finx,int finy)
{
    for (int i = labirint[finx][finy]; i >= 0; i--)
    {
        cout << finx << " " << finy << endl;
        int minim = labirint[finx][finy],minimi=finx,minimj=finy;
        labirint[finx][finy] = -2;
        if (finx > 0 && labirint[finx - 1][finy] <= minim&& labirint[finx - 1][finy] >0)
        {
            minim = labirint[finx - 1][finy];
            minimi = finx-1;
            minimj = finy;
        }
        if (finy > 0 && labirint[finx][finy - 1] <= minim&&labirint[finx][finy-1] >0)
        {
            minim = labirint[finx][finy - 1];
            minimi = finx;
            minimj = finy-1;
        }
        if (finx < labirint.size() - 1 && labirint[finx + 1][finy] <= minim&& labirint[finx + 1][finy] >0)
        {
            minim = labirint[finx + 1][finy];
            minimi = finx+1;
            minimj = finy;
        }
        if (finy < labirint[0].size() - 1 && labirint[finx][finy + 1] <= minim&& labirint[finx][finy+1] >0)
        {
            minim = labirint[finx][finy + 1];
            minimi = finx;
            minimj = finy+1;
        }
        finx = minimi;
        finy = minimj;
    }
    for (int i = 0; i < labirint.size(); i++)
    {
        for (int j = 0; j < labirint[i].size(); j++)
        {
            if (labirint[i][j] == -2)
                cout << " 1 ";
            else
                if (labirint[i][j] > 0)
                    cout << " 0 ";
                else
                    cout << "-1 ";
        }
        cout << endl;
    }
}
void parcurgere(vector<vector<int>> labirint,queue<int> x, queue<int> y)
{
    int stx = x.front(), sty = y.front();
    x.pop(); y.pop();
    int finx = x.front(), finy = y.front();
    x.pop(), y.pop();
    int OK = 0, mutari = 1;
    x.push(stx); y.push(sty);
    labirint[stx][sty] = mutari;
    int NrVec=1;
    while (OK != 1||NrVec!=0)
    {
        int sumVec = 0;
        while (NrVec)
        {
            int tempx = x.front(), tempy = y.front();
            if (tempx == finx && tempy == finy)
                OK = 1;
            sumVec+=vecini(labirint, tempx, tempy, mutari, x, y);
            x.pop(); y.pop();
            NrVec--;
        }
        NrVec = sumVec;
        mutari++;
    }
    drumInapoi(labirint, finx, finy);
}
int main()
{
    vector<vector<int>> labirint;
    queue<int> x;
    queue<int> y;
    citire(labirint,x,y);
    parcurgere(labirint,x,y);
    return 0;
}

