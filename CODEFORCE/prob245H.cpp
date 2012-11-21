// O(n^2) algorithm to find all substr that is palindrom

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

typedef pair<int, int> pii;

pii interval[10000+10];

int bsearch(int n, pii seg)  // seg is not in 
{
  int l, r;
  l=-1, r=n;  // interval[l] < seg <= interval[r]
  while (l+1 < r) {
    int m = (l+r)/2;  // l < m < r, and m is valid
    if (interval[m] < seg) l = m;
    else r = m;
  }
  assert(l+1 == r);
  return r;
}

int main()
{
  string s;
  cin >> s;
  int n = s.length();
  int l, r;
  int cnt = 0;
  for (int i=1; i<2*n; ++i) {
    // even pos, i/2-1 and i/2
    // odd pos, i/2
    if (i&1) {
      for (l=r=i/2; 0<=l && r<n && s[l] == s[r]; --l, ++r) ;
      interval[cnt++] = pii(l+1, r-1);
    } else {
      for (l=i/2-1, r=i/2; 0<=l && r<n && s[l] == s[r]; --l, ++r) ;
      if (l+1 < r-1) interval[cnt++] = pii(l+1, r-1);
    }
  }

  int q; cin >> q;
  for (int i=0; i<q; ++i) {
    int ans = 0;
    int a, b; cin >> a >> b; --a, --b;
    // find number of intervals contained in [a,b]
    for (int i=0; i<cnt; ++i) {
    	int a1, a2, c1, c2;
	a1 = interval[i].first; a2 = interval[i].second;
	if (a2-a1+1 & 1) {  // odd pal
	  c1 = c2 = (a1 + a2) / 2;
	} else {  // even pal
	  c1 = (a1 + a2) / 2;
	  c2 = (a1 + a2) / 2 + 1;
	}
	a1 = max(a1, a);
	a2 = min(a2, b);
	if (a1 <= c1 && c2 <= a2)
	  ans += 1 + min(c1-a1, a2-c2);
    }
    cout << ans << endl;
  }
}

// TLE
