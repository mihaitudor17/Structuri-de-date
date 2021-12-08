#include <iostream>
#include <list>
#include <unordered_set>
#include <fstream>
using namespace std;
void citire(list<float>& numere)
{
    int n;
    ifstream f("input.txt");
    f >> n;
    for (int i = 0; i < n; i++)
    {
        float temp;
        f >> temp;
        numere.push_back(temp);
    }
}
void parcurgere(list<float>& numere, unordered_set<float>& map) 
{
    
    for (list<float>::iterator i = numere.begin(); i != numere.end(); i++)
    {
        float temp = *i;
        if (map.find(temp) != map.end())
        {
            numere.erase(i++);
            i--;
        }
        else
            map.insert(temp);
    }
    for (list<float>::iterator i = numere.begin(); i != numere.end(); i++)
    {
        cout << (*i) << endl;
    }
}
int main()
{
    list<float> numere;
    unordered_set<float> map;
    citire(numere);
    parcurgere(numere, map);
}

