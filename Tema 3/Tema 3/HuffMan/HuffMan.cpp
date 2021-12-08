#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
struct nod {
    char lit;
    int h;
    nod* dr;
    nod* st;
};
nod* head = new nod;
void citire(vector<int>& input,vector<char>& litere)
{
    ifstream f("input.txt");
    int n;
    f >> n;
    input.resize(n);
    litere.resize(n);
    for (int i = 0; i < n; i++)
        f >> input[i];
    for (int i = 0; i < n; i++)
        f >> litere[i];

}
void afisare()
{
    queue<nod*> show;
    nod* first;
    show.push(head);
    vector<vector<char>>nivele;
    while (!show.empty())
    {
        first = show.front();
        if (first->st != nullptr)
        {
            nod* temp;
            temp = first->st;
            char litera = temp->lit;
            show.push(temp);
            int inalt = temp->h;
            if (inalt >= nivele.size())
                nivele.resize(inalt + 1);
            nivele[inalt].push_back(litera);
        }
        if (first->dr != nullptr)
        {
            nod* temp;
            temp = first->dr;
            char litera = temp->lit;
            show.push(temp);
            int inalt = temp->h;
            if (inalt >= nivele.size())
                nivele.resize(inalt+1);
            nivele[inalt].push_back(litera);
        }
        show.pop();
    }
    cout << head->lit << endl;
    for (int i = 1; i < nivele.size(); i++)
    {
        for (int j = 0; j < nivele[i].size(); j++)
            cout << nivele[i][j] << " ";
        cout << endl;
    }
}
void parcurgere(vector<int> input, vector<char> litere)
{
    head->lit = '0';
    head->h = 0;
    head->st = nullptr;
    head->dr = nullptr;
    nod* current;
    for(int i=0;i<input.size();i++)
    {
        string str = to_string(input[i]);
        current = head;
        int inalt = 0;
        for (int j = 0; j < str.size(); j++)
        {
            inalt++;
            if (str[j] == '0')
            {
                if (current->st==nullptr)
                {
                    nod* temp=new nod;
                    temp->lit = '0';
                    temp->h = inalt;
                    temp->dr = nullptr;
                    temp->st = nullptr;
                    current->st = temp;
                    current = current->st;
                }
                else
                    current = current->st;
            }
            else
                if (current->dr==nullptr)
                {
                    nod* temp = new nod;
                    temp->lit = '0';
                    temp->h = inalt;
                    temp->dr = nullptr;
                    temp->st = nullptr;
                    current->dr = temp;
                    current =current->dr;
                }
                else
                    current = current->dr;
            if (j == str.size() - 1)
                current->lit = litere[i];
        }
    }
    afisare();
}
int main()
{
    vector<int> input;
    vector<char> litere;
    citire(input, litere);
    parcurgere(input, litere);
    return 0;
}



