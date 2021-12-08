/*
Complexitatea algoritmului este patratica deoarece vectorul este parcurs de de 2 
*/
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;
struct punct{
    int x, y;

};
struct minimum {
    int x;
    int y;
};
struct maximum {
    int x;
    int y;
};
void citire(vector<punct>& coord, int& n)
{
    ifstream f("input.txt");
    f >> n;
    coord.resize(n);
    for (int i = 0; i < n; i++)
    {
        punct temp;
        f >> temp.x;
        f >> temp.y;
        coord[i] = temp;
    }
}
float dist(vector<punct> coord, int i,int j) {
    float temp = pow((coord[j].x - coord[i].x), 2) + pow((coord[j].y - coord[i].y), 2);
    return sqrt(temp);
}
void distMinMax(vector<punct> coord, int n) {
    float minim, maxim;
    minim = dist(coord, 0, 1);
    maxim = dist(coord, 0 , 1);
    minimum imin;
    maximum imax;
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
        {
            float temp = dist(coord, i, j);
            if (temp > maxim)
            {
                maxim = temp;
                imax.x = i;
                imax.y = j;
            }
            else
                if (temp < minim)
                {
                    minim = temp;
                    imin.x = i;
                    imin.y = j;
                }

        }
    cout << "Dist maxima este: " << maxim << " (" << coord[imax.x].x << ", " << coord[imax.x].y << ")" << " (" << coord[imax.y].x << ", " << coord[imax.y].y << ")" << endl;
    cout << "Dist minima este: " << minim << " (" << coord[imin.x].x << ", " << coord[imin.x].y << ")" << " (" << coord[imin.y].x << ", " << coord[imin.y].y << ")" << endl;
}
int main()
{
    vector<punct> coord;
    int n;
    citire(coord, n);
    distMinMax(coord, n);
    return 0;
}

