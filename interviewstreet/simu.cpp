// simulate connect country
//

#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int edge[31*31];
int pa[35], size[35];

int getparent(int k)
{
    while(pa[k]!=k) k=pa[k];
    return k;
}

int calc(int N)
{
    int M=0;
    for(int i=0; i<N; ++i) { pa[i]=i; size[i]=1; }

    for(int i=0; i<N; ++i)   
    for(int j=i+1; j<N; ++j)
        edge[M++] = i*N+j;
    
    int ans=0;
    int comp=N;
    while(comp>1) {
        ans++;
        int k=int(((double)rand()/RAND_MAX)*M);
        int p1=edge[k]/N, p2=edge[k]%N;
        for(int i=k+1; i<M; ++i) edge[i-1]=edge[i];
        --M;
        int pa1, pa2;
        pa1=getparent(p1), pa2=getparent(p2); 
        if (pa1 != pa2) {
            if (size[pa1]>=size[pa2]) {
                pa[pa2]=pa1; size[pa1] += size[pa2];
            }
            else {
                pa[pa1]=pa2; size[pa2] += size[pa1];
            }
            --comp;
        }
    }
    //printf("ans %d\n", ans);
    return ans;
}

int main(int argc, char *argv[])
{
    int N=0;
    if (argc==2) N=atoi(argv[1]);
    printf("N %d\n", N);
    srand((unsigned)time(0));
    int n=100000;
    int avg=0;
    for(int i=0; i<n; ++i) {
        avg+=calc(N);
    }
    avg/=n;
    printf("%d\n", avg);
}
