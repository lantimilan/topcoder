#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int N;
int deg[205];
int deg2[205];
int machine[205];
vector<int> neighbor[205];

int solve(int start)
{
  memcpy(deg2, deg, sizeof deg);
  queue<int> que[3];
  for(int i=0; i<N; ++i) if (deg2[i]==0) {
    que[machine[i]].push(i);
  }
  int pos=start;
  int total=N;
  int ans=0;
  while(total) {
    while(!que[pos].empty()) {
      int cur = que[pos].front();
      que[pos].pop();
      total--;
      for(int i=0; i<int(neighbor[cur].size()); ++i) {
        int next = neighbor[cur][i];
        deg2[next]--;
        if (deg2[next]==0) que[machine[next]].push(next);
      }
    }
    pos = (pos+1)%3;
    ans++;
  }
  return ans-1;
}

void chmin(int &a, int b)
{
  a=a<b?a:b;
}

int main()
{
  scanf("%d", &N);
  for(int i=0; i<N; ++i) {
    scanf("%d", machine+i);
    machine[i]--;
  }
  for(int i=0; i<N; ++i) {
    scanf("%d", deg+i);
    for(int k=0; k<deg[i]; ++k) {
      int b; scanf("%d", &b);
      --b;
      neighbor[b].push_back(i);
    }
  }
  int ans=200*10;
  for(int s=0; s<3; ++s)
    chmin(ans, solve(s));

  printf("%d\n", ans+N);
}
