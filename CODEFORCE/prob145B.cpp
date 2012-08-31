// 104 B
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

char ans[3000000];

int main()
{
    int cnt[4];
    for(int i=0; i<4; ++i) scanf("%d", &cnt[i]);
    
    if (abs(cnt[2]-cnt[3])>=2) {
        puts("-1"); return 0;
    }
    if (min(cnt[0],cnt[1])<max(cnt[2],cnt[3])) {
        puts("-1"); return 0;
    }
    
    
    int pos=0;
    if (cnt[2]==cnt[3]+1) {
        for(int i=0; i<cnt[0]-cnt[2]; ++i) ans[pos++]='4';
        for(int i=0; i<cnt[2]; ++i) { ans[pos++]='4'; ans[pos++]='7'; }
        for(int i=0; i<cnt[1]-cnt[2]; ++i) ans[pos++] = '7';
        //ans=string(cnt[0]-cnt[2], '4');
        //for(int i=0; i<cnt[2]; ++i) ans += "47";
        //ans += string(cnt[1]-cnt[2], '7');        
    }
    else if (cnt[2]==cnt[3]) {
        if (cnt[0]>cnt[2]) {
            for(int i=0; i<cnt[0]-cnt[2]-1; ++i)
                ans[pos++]='4';
            for(int i=0; i<cnt[2]; ++i) {
                ans[pos++]='4'; ans[pos++]='7';
            }
            for(int i=0; i<cnt[1]-cnt[3]; ++i)
                ans[pos++]='7';
            ans[pos++]='4';
            //ans=string(cnt[0]-cnt[2]-1, '4');
            //for(int i=0; i<cnt[2]; ++i) ans += "47";
            //ans += string(cnt[1]-cnt[3], '7');        
            //ans += '4';
        }
        else if (cnt[1]>cnt[3]) {            
            ans[pos++]='7'; cnt[1]--;
            for(int i=0; i<cnt[2]; ++i) {
                ans[pos++]='4'; ans[pos++]='7';
            }
            for(int i=0; i<cnt[1]-cnt[3]; ++i) {
                ans[pos++]='7';
            }
            //ans+='7'; cnt[1]--;            
            //for(int i=0; i<cnt[2]; ++i) ans += "47";
            //ans += string(cnt[1]-cnt[3], '7');            
        }
        else strcpy(ans,"-1");
    }
    else {
        ans[pos++]='7';
        for(int i=0; i<cnt[0]-cnt[2]-1; ++i)
            ans[pos++]='4';
        for(int i=0; i<cnt[2]; ++i) {
            ans[pos++]='4'; ans[pos++]='7';
        }
        for(int i=0; i<cnt[1]-cnt[3]; ++i) 
            ans[pos++]='7';
        ans[pos++]='4';
        //ans=string(1,'7');
        //if (cnt[0]>cnt[2])
        //    ans += string(cnt[0]-cnt[2]-1, '4');
        //for(int i=0; i<cnt[2]; ++i) ans += "47";
        //ans += string(cnt[1]-cnt[3], '7');
        //ans += '4';
    }
    //puts(ans.c_str());
    puts(ans);
}
