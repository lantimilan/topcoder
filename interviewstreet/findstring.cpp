// suffix array
// Submission Accepted
// 7/7 testcases passed
//
// use vector<string> for suffix[] would mem limit exceeded
// Wrong Answer
// terminate called after throwing an instance of 'std::bad_alloc' what(): std::bad_alloc Aborted
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
using namespace std;

char W[60][2005];
int m[60];
int N; // number string
int M; // max length

typedef pair<int,int> pii;
map<int,pair<pii,int> > mp; // q, (id,start), length
vector<pii> suffix;
vector<int> query;

bool cmp(pii a, pii b)
{
    int i1=a.first, p1=a.second, l1=strlen(W[i1]);
    int i2=b.first, p2=b.second, l2=strlen(W[i2]);
    for(; p1<l1 && p2<l2; ++p1, ++p2) {
        if (W[i1][p1] != W[i2][p2]) {
            return W[i1][p1] < W[i2][p2];
        }     
    }
    if (l1-p1 < l2-p2) return true;
    return false;
}
// only 2000*2000*50 = 10^8 substr
// only 2000*50 suffix and each substr is a prefix of a suffix
void solve()
{
    vector<int> qq = query;
    sort(qq.begin(), qq.end());
    int Q=query.size();
    int ns=0, nq=0;
    for(int i=0; i<N; ++i)
    for(int p=0; p<m[i]; ++p)
    {
        suffix.push_back(pii(i,p));
    }
    sort(suffix.begin(), suffix.end(), cmp);
    
    int cnt=0;
    for(int i=0; i<int(suffix.size()); ++i)
    {
        int id=suffix[i].first;
        int start=suffix[i].second;
        int len=strlen(W[id]) - start;
        int pos=0;
        if (i>0) {
            int id1=suffix[i-1].first, s1=suffix[i-1].second;
            int id2=suffix[i].first, s2=suffix[i].second;
            int l1 = strlen(W[id1]), l2=strlen(W[id2]);
            for(pos=0; pos<len; ++pos) {
                if (pos >= l1-s1 || 
                    W[id2][s2+pos]>W[id1][s1+pos])
                    break;
            }
        }
        if (pos>=len) continue;
        int next = cnt + len-pos;
        
        while (nq < Q && next >= qq[nq]) {
            int k=qq[nq];
            mp[k]=make_pair(pii(id,start), pos+k-cnt);
            nq++;
        }
        if (nq >= Q) break;
        cnt = next;        
    }
    //printf("%d\n", cnt);
}

int main()
{
    scanf("%d", &N);
    M=0;
    for(int i=0; i<N; ++i) {
        scanf("%s", W[i]); //puts(W[i]);
        m[i] = strlen(W[i]); //printf("%d\n", m[i]);
        M = max(M, m[i]);
    }
    
    int q, k; scanf("%d", &q);
    for(int i=0; i<q; ++i) {
        scanf("%d", &k); //printf("%d\n", k);
        query.push_back(k);
        mp[k];
    }
    solve();
    for(int i=0; i<q; ++i) {
        int k=query[i];
        if (mp[k].second == 0) {
            puts("INVALID");
        }
        else {
            int ii = mp[k].first.first;
            int ss = mp[k].first.second;
            int ll = mp[k].second;
            char out[2005]={0}; strncpy(out, W[ii]+ss, ll);
            puts(out);
        }
    }
}
