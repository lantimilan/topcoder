// TLE, 3 out of 7 PASSED
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

struct loc {
    int index, start, length;
};

typedef pair<int,int> pii; // pos, len
map<int,loc> mp;
vector<pii> mark[60];

// only 2000*2000*50 = 10^8 substr
//
void solve()
{
    char ans[2005]={0};    
    int cnt=0;
    int pos=0;
    char ch='a';
    while(pos>=0) {
        bool good = false;
        loc occ={-1,-1,-1};
        
        if (pos==0) {                        
            for(int i=0; i<N; ++i) {
                assert(mark[i].empty());
                for(int p=0; p<m[i]; ++p) {
                    if (W[i][p]==ch) {
                        mark[i].push_back(pii(p,1));
                        good = true;
                        occ.index = i;
                        occ.start = p;
                        occ.length = 1;
                    }
                }
            }
        }
        else
        {
            for(int i=0; i<N; ++i) {
                for(int p=int(mark[i].size())-1; p>=0; --p) {
                    int pp = mark[i][p].first;
                    int len = mark[i][p].second;
                    if (len < pos) break;
                    assert(len==pos);
                    if (W[i][pp+pos]==ch) {
                        mark[i].push_back(pii(pp,pos+1));
                        good=true;
                        occ.index = i;
                        occ.start = pp;
                        occ.length = pos+1;
                    }
                }                
            }
        }
        if (good) {
            cnt++; ans[pos++]=ch; ch='a';
            if (mp.count(cnt)) { 
                mp[cnt].index=occ.index; 
                mp[cnt].start=occ.start;
                mp[cnt].length=occ.length;                
            }
            printf("pos %d cnt %d ans %s\n", pos, cnt, ans);
        }
        else {
            if (ch >= 'z') {
                for(int i=0; i<N; ++i) {
                    while(!mark[i].empty()) {
                        if (mark[i].back().second==pos) mark[i].pop_back();
                        else break;
                    }
                }
                if (pos==0) break;
                else {ch=ans[--pos]+1; ans[pos]='\0'; }
            }
            else { ch++; }
        }
    }    
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
    vector<int> query;
    int q, k; scanf("%d", &q);
    for(int i=0; i<q; ++i) {
        scanf("%d", &k); //printf("%d\n", k);
        query.push_back(k);
        mp[k].index = mp[k].start = mp[k].length = -1;
    }
    solve();
    for(int i=0; i<q; ++i) {
        int k=query[i];
        if (mp[k].index<0) {
            puts("INVALID");
        }
        else {
            int i = mp[k].index;
            int s = mp[k].start;
            int l = mp[k].length;
            char out[2005]={0};
            strncpy(out, W[i]+s, l);
            puts(out);
        }
    }
}
