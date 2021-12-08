#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
string sortString(string str)
{
	string temp;
	const int MAX_CHAR = 26;
	int charCount[MAX_CHAR] = { 0 };
	for (int i = 0; i < str.length(); i++)
		charCount[str[i] - 'a']++;
	for (int i = 0; i < MAX_CHAR; i++)
		for (int j = 0; j < charCount[i]; j++)
			temp.push_back( (char)('a' + i));
	return temp;
}
class Map
{
public:
	list<pair<string, int>>* table;
	int bucket;
	Map(int n)
	{
		bucket = n;
		table = new list<pair<string, int>>[bucket];
	}
	void insert(pair<string, int> node)
	{
		int index = hashing(node.first);
		table[index].push_back(node);
	}
	void del(pair<string, int> node)
	{
		int index = hashing(node.first);
		typename list<pair<string, int>>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			pair<string, int> temp = *i;
			if (temp.first == node.first)
			{
				table[index].erase(i);
				break;
			}
		}
	}
	int search(string key)
	{
		int index = hashing(key);
		typename list<pair<string, int>>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			pair<string, int> temp = *i;
			if (temp.first == key)
			{
				return temp.second;
			}
		}
		return NULL;
	}
	int hashing(string key)
	{
		int temp = 0;
		stringstream s(key);
		string temps, temps1;
		while (s >> temps1)
		{
			temps += temps1;
		}
		for (int i = 0; i < temps.size(); i++)
		{
			temp += temps[i] - '0';
		}
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
void verificare(Map map, vector<string> cuvinte)
{
	vector<int> frecv;
	frecv.resize(cuvinte.size(), 0);
	for (int i = 0; i < cuvinte.size(); i++)
	{
		if (frecv[i] == 0)
		{
			cout << cuvinte[i] << " ";
			frecv[i] = 1;
			string temp = sortString(cuvinte[i]);
			int index=map.hashing(temp);
			typename list<pair<string, int>>::iterator j;
			for (j = map.table[index].begin(); j != map.table[index].end();j++)
			{
				pair<string, int> temp1 = *j;
				if (temp1.first == temp&&cuvinte[i]!=cuvinte[temp1.second])
				{
					cout << cuvinte[temp1.second] << " ";
					frecv[temp1.second] = 1;
				}
			}
			cout << endl;
		}
	}
}
void citire(Map& map,vector<string>& cuvinte)
{
	ifstream f("input.txt");
	string s;
	getline(f, s);
	stringstream t(s);
	string temp;
	int i = 0;
	while (t >> temp)
	{
		cuvinte.push_back(temp);
		temp=sortString(temp);
		pair<string, int> temp1(temp, i);
		map.insert(temp1);
		i++;
	}
 }
int main()
{
	int n;
	cout << "Introduceti nr de cuvinte din propozitie:" << endl;
	cin >> n;
	Map map(n);
	vector<string> cuvinte;
	citire(map,cuvinte);
	verificare(map, cuvinte);
}
