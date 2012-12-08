#ifndef KNAP_H
#define KNAP_H
#include<iostream>
using  namespace std;
class Knap
{
public:
	Knap(int* vv, int* ww, int cc, int nn)
	{
		c = cc;
		n = nn;
		v = vv;
		w = ww;
		x = new int[n + 1];
		xx = new int[n + 1];
		indexx = new int[n +1];
		cv = 0;
		cw = 0;
		bestv = 0;
		init();
	}
public:
	void printResult();
	void knapsack();
private:
	void init();
	int Bound(int i);
	void Backtrack(int i);
	void sortGoods(int * v, int * w, int n);
	int c;     // capacity
	int n;       // amount
	int * w;   // weight array
	int * v;   // value array
	int cw;    // current weight
	int cv;    // current value
	int bestv; // current best value
	int * x;	// recursion trace back
	int * indexx;	// index
	int * xx;		// trace back
};
// sort Goods by increase order
void Knap::sortGoods(int * v, int * w, int n)
{
	int temp;
	for(int i = 0; i < n; i++)
	{
		int index = i;
		for(int j = i; j < n; j++)
		{
			if(1.0 * v[j] / w[j] > 1.0 * v[index] / w[index])
				index = j;
		}
		if(index != i)
		{
			temp = v[i];
			v[i] = v[index];
			v[index] = temp;
			temp = w[i];
			w[i] = w[index];
			w[index] = temp;
			temp = indexx[index];
			indexx[index] = indexx[i];
			indexx[i] = temp;
		}
	}
}

void Knap::init()
{
	for(int i = 0; i < n; i++)
	{
		indexx[i] = i;
	}
	// sort by v/w unit
	sortGoods(v, w, n);
}

int Knap::Bound(int i)
{   // calculate up-bound
	int cleft = c - cw;   // remain capacity
	int b = cv;
	// load goods as v/w unit by decress order
	while(i < n && w[i] <= cleft)
	{
		cleft -= w[i];
		b += v[i];
		i++;
	}
	// fill bag fully
	if(i < n)
	{
		b += v[i] * cleft / w[i];
	}
	return b;
}

void Knap::Backtrack(int i)
{
	if(i >= n)   // reach leave
	{
		//bestv = cv;
		if(bestv < cv) {
			bestv = cv;
			for(int i = 0; i < n; i++)
			{
				xx[i] = x[i];
			}
		}
		return;
	}
	if(cw + w[i] <= c)  // in left sub-tree
	{
		cw += w[i];
		cv += v[i];
		x[indexx[i]] = 1;  
		Backtrack(i + 1);
		cw -= w[i];
		cv -= v[i];
	}
	if(Bound(i + 1) > bestv)    // in right sub-tree
	{
		x[indexx[i]] = 0;  
		Backtrack(i + 1);
	}
}

void Knap::printResult(){
	cout << bestv << endl;
	int * tempx = new int[n + 1];
	for(int i = 0; i < n; i++){  
		tempx[indexx[i]] = xx[i];
	} 
	for(int i = 0; i < n; i++)
	{
		cout << x[i] << " ";
	}
	cout << endl;  
}  

void Knap::knapsack()
{
	Backtrack(0);
}
#endif