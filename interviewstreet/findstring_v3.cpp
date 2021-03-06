// still TLE 4 out of 7 PASSED
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
    loc() { index=start=length=-1; }
    loc(int ii, int ss, int ll) { index=ii; start=ss; length=ll; }
};

map<int,loc> mp;
vector<loc> mark;

// only 2000*2000*50 = 10^8 substr
//
void solve()
{
    char ans[2005]={0};    
    int alpha[30]={0};    
    int cnt=0;
    int pos=0;    
    
    for(int i=0; i<N; ++i)
    for(int p=0; p<m[i]; ++p)
        alpha[W[i][p]-'a']=1;
        
    char ch='a';    
    while(pos>=0) {                
        loc occ;
        char next='z'+1;
        if (pos==0) {                        
            assert(mark.empty());
            for( ; ch<='z' && alpha[ch-'a']==0; ++ch)
                ;
            
            if (ch >'z') break;
            for(int i=0; i<N; ++i) {                
                for(int p=0; p<m[i]; ++p) {
                    if (W[i][p]==ch) {                                                
                        occ = loc(i,p,1);
                        if (p+1 < m[i]) {
                            mark.push_back(loc(i,p,1));
                            next = min(next, W[i][p+1]);
                        }
                    }
                }
            }
        }
        else
        {
            for(int x=int(mark.size())-1; x>=0; --x) {                
                int ii = mark[x].index;
                int pp = mark[x].start;
                int ll = mark[x].length;
                
                if (ll < pos) break;
                assert(ll==pos);
                if (W[ii][pp+pos]==ch) {                                        
                    occ = loc(ii,pp,ll+1);
                    if (pp+pos+1 < m[ii]) {
                        mark.push_back(loc(ii,pp,ll+1));
                        next = min(next, W[ii][pp+pos+1]);
                    }
                }
            }
        }
        cnt++; ans[pos++]=ch; //printf("cnt %d ans %s\n", cnt, ans);
        if (mp.count(cnt)) mp[cnt]=occ;
        
        while(next > 'z') {
            if (pos==0) break;
            else { ch=ans[pos-1]; ans[--pos]='\0'; }
            //printf("ch %c pos %d\n", ch, pos);     
            vector<loc> newvec;
            int x;
            for(x=int(mark.size())-1; x>=0; --x) {
                int ii = mark[x].index;
                int pp = mark[x].start;
                int ll = mark[x].length;                
                if (ll==pos) {                    
                    if (pp+pos<m[ii] && W[ii][pp+pos]>ch) {
                        next=min(next, W[ii][pp+pos]);
                        newvec.push_back(mark[x]);
                    }                    
                }
                else break;            
            }
            mark.erase(mark.begin()+x+1, mark.end());
            for(int i=0; i<int(newvec.size()); ++i)
                mark.push_back(newvec[i]);
        }
        if (next <= 'z') ch=next;
        else ch++;        
        //printf("pos %d ch %c ans %s\n", pos, ch, ans);
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
