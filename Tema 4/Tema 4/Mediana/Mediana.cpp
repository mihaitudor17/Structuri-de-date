#include <iostream>
#include <vector>
#include <limits>
struct coada {
	std::vector<int> H;
	int lung = 0;
};
void increase(std::vector<int>& H, int i, int val)
{
	if (val > H[i])
	{
		H[i] = val;
		int p = (i - 1) / 2;
		while (i > 0 && H[p] < val)
		{
			H[i] = H[p];
			i = p;
			p = (i - 1) / 2;
		}
		H[i] = val;
	}
}
void decrease(std::vector<int>& H, int i, int val)
{
	if (val < H[i])
	{
		H[i] = val;
		int p = (i - 1) / 2;
		while (i > 0 && H[p] > val)
		{
			H[i] = H[p];
			i = p;
			p = (i - 1) / 2;
		}
		H[i] = val;
	}
}
void maxH(std::vector<int>& H, int& lung, int val)
{
	H.resize(lung + 1);
	H[lung] = 0;
	lung++;
	increase(H, lung - 1, val);
}
void minH(std::vector<int>& H, int& lung, int val)
{
	H.resize(lung + 1);
	H[lung] = INT_MAX;
	lung++;
	decrease(H, lung - 1, val);
}
int main()
{
	int n;
	coada heapMax, heapMin;
	double mij=0;
	std::cin >> n;
	while (n)
	{
		if (heapMax.H.size() > heapMin.H.size())
		{
			if (n < mij)
			{
				int temp = heapMax.H[0];
				minH(heapMin.H, heapMin.lung, temp);
				heapMax.H.erase(heapMax.H.begin());
				heapMax.lung--;
				maxH(heapMax.H, heapMax.lung, n);
			}
			else
			{
				minH(heapMin.H, heapMin.lung, n);
			}
			mij = (heapMin.H[0] + heapMax.H[0]) / 2;
			mij += 0.5;
		}
		else
			if (heapMax.H.size() < heapMin.H.size())
			{
				if (n > mij)
				{
					int temp = heapMin.H[0];
					maxH(heapMax.H, heapMax.lung, temp);
					heapMin.H.erase(heapMin.H.begin());
					heapMin.lung--;
					minH(heapMin.H, heapMin.lung, n);
				}
				else
				{
					maxH(heapMax.H, heapMax.lung, n);
				}
				mij = (heapMin.H[0] + heapMax.H[0]) / 2;
				mij += 0.5;
			}
			else
			{
				if (n < mij)
				{
					maxH(heapMax.H, heapMax.lung, n);
					mij = heapMax.H[0];
				}
				else
				{
					minH(heapMin.H, heapMin.lung, n);
					mij = heapMin.H[0];
				}
			}
		std::cout <<  mij << std::endl;
		std::cin >> n;
	}

}
