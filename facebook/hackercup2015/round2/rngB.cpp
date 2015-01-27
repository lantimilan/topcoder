#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

void main2(void){
	double p;
	cin >> p;
	
	long double ans = 0.0;
	int i;
	REP(i,1000000) ans += pow(1.0 - pow(1.0 - p, i), 20);
	ans = 1000000.0 - ans;
	
	printf("%.5f\n", (double)ans);
}

///////////////////////////////////////////////////////////////////////////////////////

int main(void){
	int T,t;
	cin >> T;
	REP(t,T){
		printf("Case #%d: ", t+1);
		main2();
	}
	return 0;
}

