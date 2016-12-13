// ChessFerz.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

int x[8];
bool a[8];
bool c[15], b[15];
void Try(int& i);
int m;


void next(int&j, int&i, bool&eos);
void First(bool&eos, int& j, int& i);
bool CanBeDone(int& i, int& j);
void queens(void);

struct Duplicates
{
	int first[8];
	int second[8];
	bool isFull = false;
};

vector<Duplicates> Results;


int main()
{
	queens();
	int i;
	cin >> i;
    return 0;
}

void Try(int& i, bool& done)
{
	int j;
	bool eos;
	if (i < 8)
	{
		First(eos, j, i);
		while (!eos && !CanBeDone(i, j))
		{
			next(j, i, eos);
		}
		done = !eos;
	}
	else
		done = true;
}

void Try(int & i)
{
	int j;
	if (i < 8) {
		for (j = 0; j < 8; j++) {
			if (a[j] && b[i + j] && c[i - j + 7])
			{
				x[i] = j;
				a[j] = false;
				b[i + j] = false;
				c[i - j + 7] = false;
				int temp = i + 1;
				Try(temp);
				x[i] = -1;
				a[j] = true;
				b[i + j] = true;
				c[i - j + 7] = true;
			}
		}
	}
	else
	{
		bool insert = false;
		for (int s = 0; s < Results.size(); s++)
		{
			Duplicates* elem = &Results[s];
			if (elem->isFull)
				continue;
			int t;
			for (t = 0; t < 8; t++)
			{
				if (elem->first[t] == x[7 - t])
					continue;
				else
					break;
			}
			if (t == 8) {
				for (t = 0; t < 8; t++)
					elem->second[t] = x[t];
				elem->isFull = true;
				insert = true;
				break;
			}
		}
		if (!insert)
		{
			Duplicates elem;
			for (int t = 0; t < 8; t++)
				elem.first[t] = x[t];
			Results.insert(Results.end(), elem);
		}
		m = m + 1;
	}
}

void next(int & j, int&i, bool & eos)
{
	do
	{
		j++;
	} while (j<8 && (!a[j] || !b[i+j] || !c[i-j+7]));
	eos = j == 8;
}

void First(bool & eos, int & j, int & i)
{
	eos = false;
	j = -1;
	next(j, i, eos);
}

bool CanBeDone(int & i, int & j)
{
	bool done;
	x[i] = j;
	a[j] = false;
	b[i + j] = false;
	c[i - j + 7] = false;
	Try(++i, done);
	if (!done)
	{
		x[i] = -1;
		a[j] = true;
		b[i + j] = true;
		c[i - j + 7] = true;
	}
	return done;
}

void queens(void)
{
	bool done;
	int i, j;
	for (i = 0; i < 8; i++) {
		a[i] = true;
		x[i] = -1;
	}
	for (i = 0; i < 15; i++) {
		b[i] = true;
		c[i] = true;
	}
	m = 0;
	int index = 0;
	Try(index);
	cout << "All results: " << m << endl << "All Duplicates: "<<Results.size()<<endl<<"Please enter duplicate index:";
	cin >> index;
	cout << "First variant : " << endl;
	Duplicates variant = Results[index];
	for (i = 0; i < 8; i++)
		cout << cout.width(4) << variant.first[i];
	cout << endl;
	cout << "Second variant : " << endl;
	for (i = 0; i < 8; i++)
		cout << cout.width(4) << variant.second[i];
	cout << endl;
}
