#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
class Map
{
public:
	list<pair<char, int>>* table;
	int bucket;
	Map(int n)
	{
		bucket = n;
		table = new list<pair<char, int>>[bucket];
	}
	void insert(pair<char, int> node)
	{
		int OK = 0;
		int index = hashing(node.first);
		if (table[index].empty())
			table[index].push_back(node);
		else
		{
			typename list<pair<char, int>>::iterator i;
			for (i = table[index].begin(); i != table[index].end(); i++)
			{
				pair<char, int> temp = *i;
				if (temp.first == node.first)
				{
					temp.second++;
					*i = temp;
					OK = 1;
					i=table[index].end();
					i--;
				}
			}
			if (i == table[index].end()&&OK==0)
			{
				table[index].push_back(node);
			}
		}
	}
	void del(pair<char, int> node)
	{
		int index = hashing(node.first);
		typename list<pair<char, int>>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			pair<char, int> temp = *i;
			if (temp.first = node.first)
			{
				table[index].erase(i);
				break;
			}
		}
	}
	int search(char key)
	{
		int index = hashing(key);
		typename list<pair<char, int>>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			pair<char, int> temp = *i;
			if (temp.first == key)
			{
				return temp.second;
			}
		}
		return NULL;
	}
	int hashing(char key)
	{
		int temp = key-'0';
		return (temp % bucket);
	}
	void display() {
		for (int i = 0; i < bucket; i++) {
			cout << i;
			for (auto temp : table[i])
				cout << " --> " << temp.first << " " << temp.second;
			cout << endl;
		}
	}
};
bool verificare(Map map,int n)
{
	int imp;
	if (n % 2 == 0)
		imp = 0;
	else
		imp = 1;
	for (int i = 0; i < map.bucket; i++) {
		for (auto temp : map.table[i])
		{
			if (temp.second % 2 == 1)
				imp--;
			if (imp < 0)
			{
				cout << "Nu este palindrom";
				return 0;
			}
		}
	}
	cout << "Este palindrom";
	return 1;
}
void citire()
{
	ifstream f("input.txt");
	int n;
	f >> n;
	Map map(n);
	for (int i = 0; i < n; i++)
	{
		char temp;
		f >> temp;
		pair<char, int> temp1(temp, 1);
		map.insert(temp1);
	}
	verificare(map,n);
}
int main()
{
	citire();
}

