#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
template<class T>
struct NOD {
	T informatie;
	int inaltime;
	NOD* parinte;
	NOD* st;
	NOD* dr;
};
template<class T>
class AVL
{
public:
	NOD<T>* radacina;
	AVL()
	{
		radacina = nullptr;
	}
	NOD<T>* nouNOD(int info)
	{
		NOD<T>* temp = new NOD<T>;
		temp->informatie = info;
		temp->inaltime = 1;
		temp->dr = nullptr;
		temp->parinte = nullptr;
		temp->st = nullptr;
		return temp;
	}
	int balans(NOD<T>* frunza)
	{
		if (frunza == nullptr)
			return 0;
		int dr = 0, st = 0;
		if (frunza->dr != nullptr)
		{
			dr = frunza->dr->inaltime;
		}
		if (frunza->st != nullptr)
		{
			st = frunza->st->inaltime;
		}
		return dr - st;
	}
	NOD<T>* MINIM(NOD<T>* subradacina)
	{
		NOD<T>* temp;
		temp = subradacina;
		while (temp->st != nullptr)
		{
			subradacina = temp;
			temp = temp->st;
		}
		return subradacina;
	}
	NOD<T>* MAXIM(NOD<T>* subradacina)
	{
		NOD<T>* temp;
		temp = subradacina;
		while (temp->dr != nullptr)
		{
			subradacina = temp;
			temp = temp->dr;
		}
		return subradacina;
	}
	NOD<T>* SUCCESOR(NOD<T>* x)
	{
		NOD<T>* y;
		if (x->dr != nullptr)
			y = MINIM(x->dr);
		else
		{
			y = x->parinte;
			while (y != nullptr && x == y->dr)
			{
				x = y;
				y = y->parinte;
			}
		}
		return y;
	}
	NOD<T>* PREDECESOR(NOD<T>* x)
	{
		NOD<T>* y;
		if (x->st != nullptr)
			y = MAXIM(x->st);
		else
		{
			y = x->parinte;
			while (y != nullptr && x == y->st)
			{
				x = y;
				y = y->parinte;
			}
		}
		return y;
	}
	NOD<T>* SEARCH(AVL<T> tree,T val)
	{
		NOD<T>* temp = tree.radacina;
		while (temp != nullptr)
		{
			if (temp->informatie != val)
				return temp;
			if (val > temp->informatie)
				temp = temp->dr;
			else
				if (val < temp->informatie)
					temp = temp.st;
		}
		return nullptr;
	}
	bool EMPTY(AVL<T> tree)
	{
		if (tree.radacina == nullptr)
			return 0;
		return 1;
	}
	void CLEAR(AVL<T>& tree)
	{
		queue<NOD<T>*> search;
		search.push(tree.radacina);
		while (!search.empty())
		{
			NOD<T>* temp = search.front();
			search.pop();
			if (temp->st != nullptr)
			{
				search.push(temp->st);
			}
			if (temp->dr != nullptr)
			{
				search.push(temp->dr);
			}
			delete temp;
		}
		tree.radacina = nullptr;
	}
	void CONSTRUCT(AVL<T>tree, vector<T> input)
	{
		for (int i = 0; i < input.size(); i++)
		{
			tree.INSERT(input[i]);
		}
	}
	void ROT_ST(AVL<T>& tree, NOD<T>* y)
	{
		NOD<T>* x = y->dr;
		y->dr = x->st;
		if (x->st != nullptr)
			x->st->parinte = y;
		x->parinte = y->parinte;
		if (y->parinte == nullptr)
		{
			tree.radacina = x;
		}
		else
			if (y = y->parinte->st)
			{
				y->parinte->st = x;
			}
			else
				y->parinte->dr = x;
		x->st = y;
		y->parinte = x;
		x->inaltime = max(x->st->inaltime, x->dr->inaltime) + 1;
		y->inaltime = max(y->st->inaltime, y->dr->inaltime) + 1;
	}
	void ROT_DR(AVL<T>& tree, NOD<T>* x)
	{
		NOD<T>* y = x->st;
		x->st = y->dr;
		if (y->dr != nullptr)
			y->dr->parinte = x;
		y->parinte = x->parinte;
		if (x->parinte == nullptr)
		{
			tree.radacina = y;
		}
		else
			if (x = x->parinte->dr)
			{
				x->parinte->dr = y;
			}
			else
				x->parinte->st = y;
		y->dr = x;
		x->parinte = y;
		y->inaltime = max(y->st->inaltime, y->dr->inaltime) + 1;
		x->inaltime = max(x->st->inaltime, x->dr->inaltime) + 1;
	}
	void INSERT_REPARA(AVL<T>& tree, NOD<T>* frunza)
	{
		NOD<T>* temp = frunza->parinte;
		int factor = balans(temp);
		if (factor == 1 || factor == -1)
		{
			INSERT_REPARA(tree, temp);
		}
		else
			if (factor == 2 || factor == -2)
			{
				if (balans(temp) == -2 && balans(temp->st) == -1)
				{
					ROT_DR(tree, temp);
					INSERT_REPARA(tree, temp);
				}
				else
					if (balans(temp) == 2 && balans(temp->st) == 1)
					{
						ROT_ST(tree, temp);
						INSERT_REPARA(tree, temp);
					}
					else
						if (balans(temp) == -2 && balans(temp->st) == 1)
						{
							ROT_ST(tree, temp->st);
							ROT_DR(tree, temp);
							INSERT_REPARA(tree, temp);
						}
						else
							if (balans(temp) == 2 && balans(temp->st) == -1)
							{
								ROT_DR(tree, temp->dr);
								ROT_ST(tree, temp);
								INSERT_REPARA(tree, temp);
							}
			}
	}
	void INSERT(AVL<T>& tree, NOD<T>* frunza)
	{
		if (tree.radacina == nullptr)
			tree.radacina = frunza;
		else
		{
			NOD<T>* temp;
			bool dir;
			temp = tree.radacina;
			while (temp != nullptr)
			{
				frunza->parinte = temp;
				if (frunza->informatie < temp->informatie)
				{
					temp = temp->st;
					dir = 0;
				}
				else
				{
					temp = temp->dr;
					dir = 1;
				}
			}
			temp = frunza->parinte;
			if (dir == 0)
				temp->st = frunza;
			else
				temp->dr = frunza;
			INSERT_REPARA(tree, frunza);
		}
	}
	void DELETE(AVL& tree, NOD<T>* frunza)
	{
		if (frunza->dr == nullptr || frunza->st == nullptr)
		{
			NOD<T>* y = SUCCESOR(frunza);
			frunza = y;
			y = y->dr;
			DELETE_REPARA(tree, frunza->parinte);
		}
		else
		{
			if (frunza->dr != nullptr)
				frunza = frunza->dr;
			else
				frunza = frunza->st;
			DELETE_REPARA(tree, frunza->parinte);
		}
	}
	void DELETE_REPARA(AVL& tree,NOD<T>* frunza)
	{
			if (frunza != nullptr) {
				NOD<T>* temp = frunza->parinte;
				int factor = balans(tree,temp);
				if (factor == 0) {
					DELETE_REPARA(tree,temp);
				}
				else 
					if (factor == 2 || factor == -2) 
					{
					if (balans(tree,temp) == -2 && balans(temp->st) == 0) 
					{
						ROT_DR(tree,temp);
					}
					else
						if (balans(tree,temp) == -2 && balans(temp->st) == -1) 
						{
						ROT_DR(tree,temp);
						DELETE_REPARA(tree,temp);
						}
					else 
						if (balans(tree,temp) == 2 && balans(temp->dr) == 0) 
						{
							ROT_ST(tree,temp);
						}
					else 
						if (balans(tree,temp) == 2 && balans(temp->dr) == 1) 
						{
							ROT_ST(tree,temp);
							DELETE_REPARA(tree,temp);
						}
					else 
						if (balans(tree,temp) == -2 && balans(temp->st) == 1) 
						{
							ROT_ST(temp->st);
							ROT_DR(tree,temp);
							DELETE_REPARA(tree,temp);
						}
					else 
						if (balans(tree,temp) == 2 && balans(temp->dr) == -1) 
						{
							ROT_DR(temp->dr);
							ROT_ST(tree,temp);
							DELETE_REPARA(tree,temp);
						}
				}
			}
	}
	void preOrdine(NOD<T>* radacina)
	{    
		if (radacina != nullptr)
		{
			cout << radacina->informatie << " ";
			preOrdine(radacina->st);
			preOrdine(radacina->dr);
		}
	}
	void afisareNiv(NOD<T>* radacina)
	{
		queue<NOD<T>*> search;
		search.push(radacina);
		T inaltime = radacina->inaltime;
		while (!search.empty())
		{
			NOD<T>* temp = search.front();
			search.pop();
			cout << temp->informatie << " ";
			if (temp->inaltime < inaltime)
			{
			cout << endl;
			inaltime--;
			}
			if (temp->st != nullptr)
			{
				search.push(temp->st);
			}
			if (temp->dr != nullptr)
			{
				search.push(temp->dr);
			}
		}
	}
	void preOrdine(NOD<T>* radacina,vector<T>& vector)
	{
		if (radacina != nullptr)
		{
			vector.push_back(radacina);
			preOrdine(radacina->st);
			preOrdine(radacina->dr);
		}
	}
	AVL<T> MERGE(AVL<T> tree1, AVL<T> tree2)
	{
		AVL<T> tree3;
		vector<T> vector1, vector2,vector3;
		preOrdine(tree1.radacina, vector1);
		preOrdine(tree2.radacina, vector2);
		vector3.resize(vector1.size() + vector2.size());
		merge(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(),vector3.begin());
		for (int i = 0; i < vector3.size(); i++)
		{
			tree3.INSERT(tree3, vector3[i]);
		}
	}
};

void citire(AVL<int>& tree)
 {
	int n;
	ifstream f("input.txt");
	f >> n;
	for (int i = 0; i < n; i++)
	{
		int x;
		f >> x;
		tree.INSERT(tree,tree.nouNOD(x));
	}
 }
int main()
{
	AVL<int> tree;
	citire(tree);
	tree.afisareNiv(tree.radacina);
	tree.CLEAR(tree);
	tree.preOrdine(tree.radacina);
}
