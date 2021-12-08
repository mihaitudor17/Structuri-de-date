#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void citire(vector<int>& cost) 
{
	int x, y;
	cout << "Introduceti nr de randuri: ";
	cin >> x;
	cout << "Introduceti nr de scaune: ";
	cin >> y;
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			cost.push_back((i + 1) * (j + 1));
}
void bilet(vector<int>cost)
{
	sort(cost.begin(), cost.end());
	cout << "Introduceti numar bilet: ";
	int temp;
	cin >> temp;
	cout << "Costul este: " <<* (cost.end() - temp);
}
int main()
{
	vector<int> cost;
	citire(cost);
	bilet(cost);
	return 0;
}


