#include<cstdio>
#include<algorithm>
#include<cassert>
#include<cstring>
using namespace std;
const int MAX=11000;
const int MOD=1000000000+7;
int t,tt,n,m,matched[110];
char k1[110],k2[110];
bool b[110],e[110][110];
bool dfs(int x){
  b[x]=true;
  for(int y=0;y<m;y++)if(e[x][y]&&(matched[y]==-1||!b[matched[y]]&&dfs(matched[y]))){
    matched[y]=x;
    return true;
  }
  return false;
}
bool ok(){
  int n=strlen(k1);
  assert(n%m==0);
  memset(e,0,sizeof(e));
  for(int i=0;i<m;i++)for(int j=0;j<m;j++){
    e[i][j]=true;
    for(int k=0;k<n/m;k++){
      char first=k1[i*n/m+k];
      char second=k2[j*n/m+k];
      e[i][j]&=first=='?'||second=='?'||first==second;
    }
  }
  memset(matched,-1,sizeof(matched));
  for(int i=0;i<m;i++){
    memset(b,0,sizeof(b));
    if(!dfs(i))return false;
  }
  return true;
}
main(){
  scanf("%d",&t);
  for(int tt=1;tt<=t;tt++){
    scanf("%d %s %s",&m,k1,k2);
    printf("Case #%d: ",tt);
    if(!ok()){
      puts("IMPOSSIBLE");
    }else{
      for(int i=0;k1[i];i++)if(k1[i]=='?'){
        k1[i]='a';
        while(!ok()&&k1[i]<'f')++k1[i];
        assert(k1[i]<='f'&&ok());
      }
      puts(k1);
    }
  }
}

