#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cstring>
using namespace std;
void citire(string& input)
{
    ifstream f("input.txt");
    getline(f,input);
}
int prioritate(char temp)
{
    if (temp == '{')
        return 3;
    if (temp == '[')
        return 2;
    if (temp == '(')
        return 1;
    if (temp == '}')
        return -3;
    if (temp == ']')
        return -2;
    if (temp == ')')
        return -1;
}
bool parcurgere(string input)
{
    stack<int> paranteze;
    for (int i = 0; i < input.size(); i++)
    {
        if (strchr("{[()]}", input[i]))
        {
            if (strchr("{[(", input[i]))
            {
                int temp = prioritate(input[i]);
                if (!paranteze.empty())
                    if (temp > paranteze.top())
                      return 0;
                paranteze.push(temp);
            }
            else
            {
                
                int temp = prioritate(input[i]),sum=0;
                sum += temp;
                    while (!paranteze.empty() && sum != 0)
                    {
                        sum += paranteze.top();
                        paranteze.pop();
                    }
                if (sum != 0)
                    return 0;
            }
        }
    }
    return 1;
}
int main()
{
    string input;
    citire(input);
    if (parcurgere(input))
        cout << "Corect";
    else
        cout << "Gresit";
    return 0;
}

