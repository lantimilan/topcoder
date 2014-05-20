#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <deque>

using namespace std;

const int MAXN = 25;

int n;
int a[MAXN];
int l[MAXN];

int pos = 0;
int s[MAXN];
int u[MAXN];

void rek(int cnt){

  if (cnt == n){
    while (s[pos] == 1) ++pos;
    if (pos == n){ printf("YES\n"); exit(0); }
    return;
  }

  for (int i = 0; i < s[pos]; ++i){
    if (l[i] == 0) continue;
    --l[i];

    s[cnt] = i;

    int opos = pos;
    s[pos] -= i;
    ++u[pos];

    if (u[pos] == 1 && s[pos] == 1);
    else{
      while (s[pos] == 1) ++pos;
      rek(cnt+1);
    }

    pos = opos;
    --u[pos];
    s[pos] += i;
    ++l[i];
  }
}

void solve (){
  sort(a, a+n);
  reverse(a, a+n);

  for (int i = 0; i < n; ++i) l[a[i]]++;
  l[a[0]]--;
  s[0] = a[0];

  rek(1);
}

int main (void){
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);

  int cnt = 0;
  for (int i = 0; i < n; ++i)
    cnt += a[i] == 1;

  if ((cnt+1)*2 < n) { printf("NO\n"); return 0; }

  solve();
  printf("NO\n");
  return 0;
}
