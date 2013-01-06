#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DrawingPointsDivTwo
{
public:
int maxSteps(vector <string> points);
};

int DrawingPointsDivTwo::maxSteps(vector <string> points)
{
	const int shift = 100;
	const int size = 240;
	int mat[size][size]; memset(mat, 0, sizeof mat);
	for (int i=0; i<points.size(); ++i)
	for (int j=0; j<points[i].size(); ++j)
		if (points[i][j] == '*')
			mat[i*2+shift][j*2+shift] = 1;
	int cap = 100; // for finite ans, has to stop after all * meet
	int ans = 0;
	int lastmat[size][size], prevmat[size][size];
	int lo, hi, guess;
	lo = 0; hi = 100;
	//for (int guess=0; guess<=cap; ++guess)
	while (lo+1 < hi)  // lo is good, hi is bad, need keep looking when [lo, hi) > 1 element
	{
	guess = (lo + hi)/2;
	memcpy(lastmat, mat, sizeof mat);
	// play back
	for (int x=0; x<guess; ++x) {
		memset(prevmat, 0, sizeof prevmat);
		for (int i=1; i+1<size; ++i)
		for (int j=1; j+1<size; ++j)
			if (lastmat[i][j]) {
				prevmat[i-1][j-1] = prevmat[i-1][j+1] = prevmat[i+1][j-1] = prevmat[i+1][j+1] = 1;
			}
		memcpy(lastmat, prevmat, sizeof prevmat);
	}
	// play forward
	for (int x=0; x<guess; ++x) {
		memcpy(prevmat, lastmat, sizeof lastmat);
		memset(lastmat, 0, sizeof lastmat);
		for (int i=0; i+2<size; ++i)
		for (int j=0; j+2<size; ++j)
			if (prevmat[i][j] && prevmat[i][j+2] && prevmat[i+2][j] && prevmat[i+2][j+2])
				lastmat[i+1][j+1] = 1;
	}
	// check eq
	bool equal = true;
	for (int i=0; i<size; ++i)
	for (int j=0; j<size; ++j)
		if (mat[i][j] != lastmat[i][j]) {
			equal = false; break;
		}
	if (equal) lo = guess;
	else hi = guess;
	}
	ans = lo;
	if (ans+1 >= cap) return -1;
	else return ans;
}