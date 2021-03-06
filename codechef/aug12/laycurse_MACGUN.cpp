#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)

#define INT_INF 1000000000

int N1, N2, edge[130000][4], es[130000];
int mt[130000], visited[130000];
int visst[130000], vis_sz;

int MaxMatchGo(int u){
  int i,k;
  if(u<0) return 1;
  rep(i,es[u]){
    k = edge[u][i];
    if(visited[k]) continue;
    visited[k] = 1; visst[vis_sz++] = k;
    if(MaxMatchGo(mt[k])){
      mt[u] = k; mt[k] = u;
      return 1;
    }
  }
  return 0;
}

int MaxMatch(void){
  int i, j, k, res = 0;
  rep(i,N1+N2) mt[i] = -1, visited[i] = 0;
  rep(i,N1){
    rep(j,es[i]){
      k = edge[i][j];
      if(mt[k]==-1){
        res++;
        mt[i] = k; mt[k] = i;
        break;
      }
    }
  }
  
  rep(i,N1) if(mt[i]==-1){
    vis_sz = 0;
    res += MaxMatchGo(i);
    rep(k,vis_sz) visited[visst[k]]=0;
  }
  
  return res;
}

int x, y;
char in[710][710];
int num[710][710];

int main(){
  int i,j,k,l,m,area=0;
  int di, dj;
  int dx[4]={-1,-1,1,1};
  int dy[4]={-1,1,-1,1};
  int ci, cj, ni, nj;
  int res;

  for(;;){
    assert( scanf("%d%d",&x,&y)==2 );
    if(!x && !y) break;
    assert(1<=x && x<=700 && 1<=y && y<=700);
    area += x*y;
    assert(area <= 490000);

    rep(i,x) assert( scanf("%s",in[i])==1 );
    rep(i,x) assert( strlen(in[i])==y );
    rep(i,x) rep(j,y) assert( in[i][j]=='F'||in[i][j]=='G'||in[i][j]=='P' );

    res = 0;

    rep(i,x) rep(j,y){
      num[i][j] = -1;
      if(in[i][j]=='G'){
        rep(k,4){
          ci = i + dx[k]; ni = ci + dx[k];
          cj = j + dy[k]; nj = cj + dy[k];
          if(ni < 0 || ni < 0 || ni >= x || nj >= y) continue;
          assert(!(in[ci][nj]!='P' && in[ni][nj]=='G'));
          if(in[ci][cj]!='P' && in[ni][nj]=='F') in[ni][nj] = 'D'; /* this place is not available */
        }
      }
    }

    rep(di, 2) rep(dj, 2){ /* consider the cells (i mod 2, j mod 2) = (di, dj) */
      N1 = N2 = 0; /* N1 = the number of left nodes, N2 = right nodes */
      for(i=di  ;i<x;i+=4) for(j=dj;j<y;j+=2) if(in[i][j]=='F') num[i][j] = N1++;
      for(i=di+2;i<x;i+=4) for(j=dj;j<y;j+=2) if(in[i][j]=='F') num[i][j] = N2++;

      /* creating the graph */
      rep(i,N1+N2) es[i] = 0;
      for(i=di;i<x;i+=4) for(j=dj;j<y;j+=2) if(in[i][j]=='F'){
        rep(k,4){
          ci = i + dx[k]; ni = ci + dx[k];
          cj = j + dy[k]; nj = cj + dy[k];
          if(ni < 0 || ni < 0 || ni >= x || nj >= y) continue;
          if(in[ci][cj]!='P' && in[ni][nj]=='F'){
            l = num[i][j]; m = N1 + num[ni][nj];
            edge[l][es[l]++] = m;
          }
        }
      }
      
      res += N1+N2 - MaxMatch();
    }
    printf("%d\n",res);
  }

  return 0;
}

