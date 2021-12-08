#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
template <class K,class V>
class HashTable
{
public:
	list<pair<K, V>>* table;
	int bucket;
	HashTable(int n)
	{
		bucket = n;
		table = new list<pair<K, V>>[bucket];
	}
	void insert(pair<K,V> node)
	{
		int index = hashing(node.first);
		table[index].push_back(node);
	}
	void del(pair<K, V> node)
	{
		int index = hashing(node.first);
		typename list<pair<K, V>>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			pair<K, V> temp = *i;
			if (temp.first = node.first)
			{
				table[index].erase(i);
				break;
			}
		}
	}
	V search(K key)
	{
		int index = hashing(key);
		typename list<pair<K, V>>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			pair<K, V> temp = *i;
			if (temp.first == key)
			{
				return temp.second;
			}
		}
		V t = "nullptr";
		return t;
	}
	int hashing(K key)
	{
			int temp = 0;
			stringstream s(key);
			string temps,temps1;
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
				cout << " --> " << temp.first<<" "<<temp.second;
			cout << endl;
		}
	}
	V& operator[](int index)
	{

		if (!table[index].empty())
		{
			return table[index].front().second;
		}
		else
		{
			pair<K, V>temp;
			temp.first = "0";
			temp.second= "0";
			table[index].push_back(temp);
			return table[index].front().second;
		}
	}
};
void citire()
{
	int n;
	ifstream f("input.txt");
	f >> n;
	f.get();
	HashTable<string, string> H(n);
	for (int i = 0; i < n; i++)
	{
		string x;
		string y;
		getline(f, x);
		getline(f, y);
		pair<string, string> temp;
		temp.first = x;
		temp.second = y;
		H.insert(temp);
	}
	H.display();
	cout << H.search("blaga turcu") << endl;
	cout << H[1];
}
int main()
{
	citire();
}


