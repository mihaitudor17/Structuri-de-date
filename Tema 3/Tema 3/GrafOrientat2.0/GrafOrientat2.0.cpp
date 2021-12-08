#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
using namespace std;
struct node {
    int data;
    node* next;
};
node* head = NULL;
bool find(int x, vector<node*> frontier)
{
    for (int i = 0; i < frontier.size(); i++)
        if (frontier[i]->data == x)
            return 0;
    return 1;
}
void kids(queue<node*>& search, vector<vector<int>> input, vector<node*>& frontier)
{
    node* temp = search.front();
    node* head1 = temp;
    int x = temp->data;
    for (int i = 0; i < input[x].size(); i++)
    {
        if (find(input[x][i], frontier))
        {
            node* temp = new node;
            temp->data = input[x][i];
            temp->next = head1;
            head = temp;
            search.push(temp);
            frontier.push_back(temp);
        }
    }
}
void show()
{
    while (head != NULL)
    {
        cout << head->data << endl;
        head = head -> next;
    }
}
bool drum(vector<vector<int>> input,int x=-1,int y=-1,int OK=1) 
{
    vector<node*> frontier;
    if (x == -1 && y == -1)
    {
        cout << "Introduceti x: ";
        cin >> x;
        cout << "Introduceti y: ";
        cin >> y;
    }
    queue<node*> search;
    node* temp = new node;
    temp->data = x;
    temp->next = head;
    head = temp;
    search.push(head);
    while (!search.empty())
    {
        if (search.front()->data == y)
        {
            head = search.front();
            if(OK)
                show();
            return 1;
        }
        kids(search, input,frontier);
        search.pop();
    }
    return 0;
}
void read(vector<vector<int>>& input)
{
    int n,x;
    ifstream f("input.txt");
    f >> n;
    input.resize(n);
    for (int i = 0; i < n; i++)
    {
        f >> x;
        input[i].resize(x);
        for (int j = 0; j < x; j++)
            f >> input[i][j];
    }
}
bool lant(vector<vector<int>> input,int x=-1,int y=-1,int OK=1)
{
    vector<vector<int>> cpy;
    cpy = input;
    for (int i = 0; i < cpy.size(); i++)
    {
        for (int j = 0; j < cpy[i].size(); j++)
        {
            int OK = 0, temp = cpy[i][j];
            for (int k = 0; k < cpy[temp].size(); k++)
                if (i == cpy[temp][k])
                    OK = 1;
            if (OK == 0)
            {
                cpy[temp].push_back(i);
            }
        }
    }
    if(OK)
    cout << "Lantul este:" << endl;
    if (!drum(cpy,x,y,OK))
    {
        if(OK)
        cout << "Nu exista lant" << endl;
        return 0;
    }
    return 1;
}
int findFreq(vector<int> frecv)
{
    for (int i = 0; i < frecv.size(); i++)
        if (frecv[i] == 0)
            return i;
    return -1;
}
bool explored(vector<int> expl,int x)
{
    for (int i = 0; i < expl.size(); i++)
        if (expl[i] == x)
            return 1;
    return 0;
}
void comp(vector<vector<int>> input)
{
    queue<int>search;
    vector<vector<int>> conexe;
    vector<int> expl;
    vector<int> frecv;
    int x = 0;
    int temp = input.size();
    frecv.resize(temp,0);
    while (findFreq(frecv)!=-1)
    {
        x++;
        search.push(findFreq(frecv));
        conexe.resize(x);
        while (!search.empty())
        {
            int temp = search.front();
            if (!explored(expl, temp))
            {
                frecv[temp] = 1;
                expl.push_back(temp);
                conexe[x-1].push_back(temp);
                for (int i = 0; i < input[temp].size(); i++)
                    if (!explored(expl, input[temp][i]))
                        search.push(input[temp][i]);

            }
            search.pop();
        }
    }
    cout << "Sunt " << conexe.size() << " parti conexe: " << endl;
    for (int i = 0; i < conexe.size(); i++)
    {
        for (int j = 0; j < conexe[i].size(); j++)
        {
            cout << conexe[i][j] << " ";
        }
        cout << endl;
    }
}
int main()
{
    vector<vector<int>> input;
    read(input);
    cout << "Drumul este:" << endl;
    if (!drum(input))
    {
        cout << "Nu exista drum" << endl;
    }
    lant(input);
    comp(input);
    return 0;
}
