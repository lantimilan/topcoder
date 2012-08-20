// luckypart.cpp
//
// integer partition 
//
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

vector<int> seq;
bool isprime[150];
int maxsum;
vector<set<int> > sums;

void init()
{
    isprime[0] = isprime[1] = false;
    for(int i=2; i<140; ++i) {
        isprime[i]=true;
        for(int k=2; k*k<=i; ++k) if (i%k==0) isprime[i]=false;
    }
    //for(int i=0; i<140; ++i) if (isprime[i]) printf("%d ", i);
    //putchar('\n');
}

void part(int n, int k)
{
    if (n<0) return;
    if (seq.size()>18) return;
    if (n==0) {
        int sum=0, sqr=0;
        for(int i=0; i<int(seq.size()); ++i) {
            sum += seq[i];
            sqr += seq[i]*seq[i];
        }
        if (isprime[sum] && isprime[sqr]) {
            sums[sqr].insert(sum);           
            maxsum = max(maxsum, sum);
            for(int i=0; i<int(seq.size()); ++i)
                printf("%d ", seq[i]);
            putchar('\n');
        }
        return;
    }
    for(int d=k; d<=9; ++d) {
        seq.push_back(d);
        part(n-d*d, d);
        seq.pop_back();
    }
}

int main()
{
    init();
    sums.resize(140);
    int n; //scanf("%d", &n);
    for(n=1; n<140; ++n) if (isprime[n]) {
    for(int i=1; i<=9; ++i) {
        seq.push_back(i);
        part(n-i*i, i);
        seq.pop_back();
    }
    }
    for(n=1; n<140; ++n) if (isprime[n]) {
        printf("%d: ", n);
        for(set<int>::iterator it=sums[n].begin();
            it!=sums[n].end(); ++it)
            {
            printf("%d ", *it);
            }
            putchar('\n');
    }
    printf("maxsum %d\n", maxsum); // maxsum=47
}
