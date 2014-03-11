#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int MAX=1000000;
const int LEN=41000;
int t,tt,W,H,P,Q,N,X,Y,a,b,c,d,x[MAX],y[MAX],cur[LEN];
void process(const vector<int> &t,int delta){
  for(int i=0;i<t.size();i++)cur[t[i]]+=delta;
}
int calc(){
  int sum=0,ans=0;
  for(int i=0;i<Q;i++)sum+=cur[i];
  ans+=!sum;
  for(int i=Q;i<H;i++){
    sum+=cur[i];
    sum-=cur[i-Q];
    ans+=!sum;
  }
  return ans;
}
main(){
  scanf("%d",&t);
  for(int tt=1;tt<=t;tt++){
    scanf("%d %d %d %d %d %d %d %d %d %d %d",&W,&H,&P,&Q,&N,&X,&Y,&a,&b,&c,&d);
    x[0]=X;
    y[0]=Y;
    for(int i=1;i<N;i++){
      x[i]=(x[i-1]*a+y[i-1]*b+1)%W;
      y[i]=(x[i-1]*c+y[i-1]*d+1)%H;
    }
    vector<int> s[LEN];
    for(int i=0;i<N;i++)s[x[i]].push_back(y[i]);
    int ans=0;
    memset(cur,0,sizeof(cur));
    for(int i=0;i<P;i++)process(s[i],1);
    ans+=calc();
    for(int i=P;i<W;i++){
      process(s[i],1);
      process(s[i-P],-1);
      ans+=calc();
    }
    printf("Case #%d: %d\n",tt,ans);
  }
}
