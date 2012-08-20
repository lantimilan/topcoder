// savehuman.cpp
//
// Save Humanity
// algorithm:
//
// use the Z-algorithm to compute Z[i] which is the length of longest substr from pos=i
// that matches a prefix of s[]
//
//
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=200000+5;
char s[MAXN];
char t[MAXN];
char tmp[MAXN];
int front[MAXN];
int back[MAXN];
int ans[MAXN];
int N;

// not really kmp but equivalent Z-algorithm to compute prefix
void kmp(const char s[], int a[])
{
    int L, R;
    L=R=0;
    for(int i=1; i<N; ++i) {
        if (i>R) { // i out of range, new [L..R] start from pos=i
            L=R=i;
            while(R<N && s[R-L]==s[R]) R++;
            a[i]=R-L; --R;
        }
        else {
            int k=i-L;
            if (a[k] < R-i+1) a[i]=a[k];
            else { // new [L..R] interval start from pos=i
                L=i;
                while(R<N && s[R-L]==s[R]) R++;
                a[i]=R-L; --R;
            }
        }
        //printf("L %d R %d\n", L, R);
    }
}

void solve()
{
    gets(s); gets(t);
    //puts(s); puts(t);

    int n=strlen(s);
    int k=strlen(t);
    N=n+k;

    strcpy(tmp, t);
    strcat(tmp, s);
    kmp(tmp, front);
    //reverse(s,s+n);
    //reverse(t,t+k);
    //strcpy(tmp, t);
    //strcat(tmp, s);
    reverse(tmp, tmp+k);
    reverse(tmp+k, tmp+n+k);
    kmp(tmp, back);
    
    //for(int i=1; i<=n; ++i) printf("%d ", front[i]); putchar('\n');
    //for(int i=1; i<=n; ++i) printf("%d ", back[i]); putchar('\n');

    int cnt=0;
    for(int i=0; i<n; ++i) {
        int last=i+k-1;
        if (last<0 || last>=n) continue;
        if (front[k+i] + back[k+n-1-last] >= k-1) {
            if (cnt) putchar(' ');
            printf("%d", i);
            ans[cnt++]=i;
        }
    }
    //for(int i=0; i<cnt; ++i) {
    //    if (i) putchar(' ');
    //    printf("%d", ans[i]);
    //}
    putchar('\n');
}

int main()
{
    int T; scanf("%d ", &T);
    for(int t=0; t<T; ++t) {
        solve();
        getchar();
    }
}

// Save Humanity    cpp     2012-02-15 01:36:07     Processed   Accepted    View Details
//
// TLE, maybe too many string copies. No, wrong implementation, 
// when a[k]<R-i+1, do not reset R since you already matched the whole prefix from 0..a[k]
//
// #    Status  Signal  Time
// 1    Passed  Your code produced correct output for this testcase.    0.660041
// 2    Passed  Your code produced correct output for this testcase.    0.708044
// 3    Passed  Your code produced correct output for this testcase.    0.756047
// 4    Failed  Your code exceeded the timelimit for this testcase.     3.80024
// 5    Failed  Your code exceeded the timelimit for this testcase.     6.84443
// 6    Failed  Your code exceeded the timelimit for this testcase.     9.88862
// 7    Failed  Your code exceeded the timelimit for this testcase.     12.9368
// 8    Failed  Your code exceeded the timelimit for this testcase.     15.981
// 9    Failed  Your code exceeded the timelimit for this testcase.     19.0252
// 10   Failed  Your code exceeded the timelimit for this testcase.     22.0694
//
