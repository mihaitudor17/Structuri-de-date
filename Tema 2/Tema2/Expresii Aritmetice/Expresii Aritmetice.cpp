#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <math.h>
#include <vector>
#include <cstring>
using namespace std;
void citire(string &input)
{
    ifstream f("input.txt");
    getline(f,input);

}
int precedenta(char s)
{
    switch (s)
    {
    case '(':
        return 0;
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    }
}
bool polonez(string input,stack<char>& s,vector<string>& p)
{
    int nr = 0, par = 0, op = 0;
    for (int i = 0; i < input.size(); i++)
    {
        
        if (strchr("+-/*().", input[i]) || (input[i] >= '0' && input[i] <= '9'))
        {
            if (isdigit(input[i]))
            {
                int y = 0, n = 0;
                double x = input[i] - '0';
                if (isdigit(input[i + 1]))
                {
                    while (isdigit(input[i + 1]) && i + 1 < input.size())
                    {
                        i++;
                        x = x * 10 + (input[i] - '0');
                    }
                }
                if (input[i + 1] == '.' )
                {
                    if (!isdigit(input[i + 2]))
                    {
                        cout << "Formatare gresita";
                        return 0;
                    }
                    i += 1;
                    while (isdigit(input[i + 1]) && i + 1 < input.size())
                    {
                        i++;
                        y = y * 10 + (input[i] - '0');
                        n++;
                    }
                }
                x=x+(double)y/pow(10,n);
                p.push_back(to_string(x));
                nr++;
            }
            else
            {
                if (input[i] == '(')
                {
                    s.push(input[i]);
                    par++;
                }
                else
                {
                    if (input[i] == ')')
                    {
                        if (par < 1)
                        {
                            cout << "Prea multe paranteze";
                            return 0;
                        }
                        par--;
                        while (s.top() != '(' && !s.empty())
                        {
                            string temp(1, s.top());
                            p.push_back(temp);
                            s.pop();
                        }
                        if (s.empty())
                        {
                            cout << "Prea multe paranteze";
                            return 0;
                        }
                        else
                            s.pop();
                    }
                    else
                    {
                        while (!s.empty() && precedenta(input[i]) <= precedenta(s.top()))
                        {
                            string temp(1, s.top());
                            p.push_back(temp);
                            s.pop();
                        }
                        s.push(input[i]);
                        op++;
                    }
                }
            }
        }
        else
            if (input[i] != ' ')
            {
                cout << "Caractere neacceptate";
                return 0;
            }
    }
    if (par > 0)
    {
        cout << "Prea multe paranteze";
        return 0;
    }
    while (!s.empty())
    {
        string temp(1, s.top());
        p.push_back(temp);
        s.pop();
    }
    if (op >= nr)
    {
        cout << "Prea multi operatori";
        return 0;
    }
    else
        if (nr > op + 1)
        {
            cout << "Prea multe numere";
            return 0;
        }
    return 1;
}
void calcul(vector<string>p,stack<double>& nr) 
{
    for (int i = 0; i < p.size(); i++)
        if (isdigit(p[i][0]))
            nr.push(stoi(p[i]));
        else
        {
            double y = nr.top();
            nr.pop();
            double x = nr.top();
            nr.pop();
                switch (p[i][0])
                {
                case '+':
                    nr.push(x + y);
                    break;
                case '-':
                    nr.push(x - y);
                    break;
                case '*':
                    nr.push(x * y);
                    break;
                case '/':
                    nr.push(x / y);
                    break;

                }
            
        }
    cout<<  nr.top();
}
void afisare(vector<string> p)
{
    cout << "Forma poloneza este: ";
    for (int i = 0; i < p.size(); i++)
        cout << p[i] << " ";
    cout << endl;
}
int main()
{
    string input;
    stack<char> s;
    stack<double> nr;
    vector<string> p;
    citire(input);
    if (polonez(input, s, p))
    {
        afisare(p);
        cout << "Rezultatul este: ";
        calcul(p, nr);
    }
    return 0;
}
