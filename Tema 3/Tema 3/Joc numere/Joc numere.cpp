#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
struct node {
    int data,i,j;
    node* next;
};
node* head = NULL;
void read(vector<vector<int>>& input)
{
    int n;
    ifstream f("input.txt");
    f >> n;
    input.resize(n);
    for (int i = 0; i < n; i++)
    {
        input[i].resize(n);
        for (int j = 0; j < n; j++)
            f >> input[i][j];
    }
}
void neigh(queue<node*>&search, vector<vector<int>>& input)
{
    node* temp = search.front();
    node* head1 = temp;
    int x = temp->data;
    int i1 = temp->i;
    int j1 = temp->j;
    if (i1 - x >= 0 && input[i1 - x][j1] != -1)
    {
        node* temp = new node;
        temp->data = input[i1 - x][j1];
        temp->i = i1-x;
        temp->j = j1;
        temp->next = head1;
        head = temp;
        search.push(temp);
        input[i1 - x][j1] = -1;
    }
    if (i1 + x < input.size() && input[i1 + x][j1] != -1)
    {
        node* temp = new node;
        temp->data = input[i1 + x][j1];
        temp->i = i1+x;
        temp->j = j1;
        temp->next = head1;
        head = temp;
        search.push(temp);
        input[i1+x][j1] = -1;
    }
    if (j1 - x >= 0 && input[i1][j1-x] != -1)
    {
        node* temp = new node;
        temp->data = input[i1][j1-x];
        temp->i = i1;
        temp->j = j1-x;
        temp->next = head1;
        head = temp;
        search.push(temp);
        input[i1][j1-x] = -1;
    }
    if (j1 + x < input[0].size() && input[i1][j1+x] != -1)
    {
        node* temp = new node;
        temp->data = input[i1][j1+x];
        temp->i = i1;
        temp->j = j1+x;
        temp->next = head1;
        head = temp;
        search.push(temp);
        input[i1][j1 + x] = -1;
    }
}
void show() 
{
    while (head!=NULL)
    {
        cout << head->i << " " << head->j << endl;
        head = head->next;
    }
}
bool road(vector<vector<int>> input)
{   
    queue<node*> search;
    node* temp = new node;
    temp->data = input[0][0];
    input[0][0] = -1;
    temp->i = 0;
    temp->j = 0;
    temp->next = head;
    head = temp;
    search.push(head);
    while (!search.empty())
    {
        temp = search.front();
        if (temp->i == input.size() - 1 && temp->j == input[0].size() - 1)
        {
            head = temp;
            show();
            return 1;
        }
        neigh(search, input);
        search.pop();
    }
    return 0;
}
int main()
{
    vector<vector<int>> input;
    read(input);
    road(input);
    return 0;
}
