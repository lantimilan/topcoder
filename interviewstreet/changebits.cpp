// changebits.cpp
//
// Challenges /
// Changing Bits
//
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=200000+5;
int N, Q;
int R, NR;

char A[MAXN], B[MAXN], C[MAXN];
bool zero[MAXN], one[MAXN];
int  extra[MAXN];

void validate(int b)
{
    assert(extra[b]);
    extra[b]=0; assert(one[b]!=zero[b]);
    char ch=(one[b])?'1':'0';
    for(int i=b*R; i<(b+1)*R && i<N; ++i)
        C[i]=ch;
}

void setflag(int b)
{
    one[b]=zero[b]=true;
    for(int i=b*R; i<(b+1)*R; ++i) { 
        if (C[i]=='0') one[b]=false;
        else zero[b]=false;
    }
}

char query(int idx)
{
    int b=idx/R;
    if (extra[b]) {
        validate(b);
    }
    return C[idx];
}

void update(int idx, int val)
{
    int b=idx/R;
    if (extra[b]) validate(b); // start block
    if (val==1) { // add
        int carry=1;
        for(int i=idx; i<(b+1)*R && i<N; ++i) {
            if (C[i]=='0') { C[i]='1'; carry=0; break; }
            else { C[i]='0'; }
        }
        if (b<NR-1) { setflag(b); }
        if (!carry) return;
        ++b;
        while(b<NR && one[b]) {
            one[b]=false; zero[b]=true; 
            extra[b]=1-extra[b];
            b++;
        }
        if (extra[b]) validate(b); // end block
        for(int i=b*R; i<(b+1)*R && i<N; ++i) {
            if (C[i]=='0') { C[i]='1'; break; }
            else { C[i]='0'; }
        }
        if (b<NR-1) setflag(b);
    }
    else { // sub
        int borrow=1;
        for(int i=idx; i<(b+1)*R && i<N; ++i) {
            if (C[i]=='1') { C[i]='0'; borrow=0; break; }
            else { C[i]='1'; }
        }
        if (b<NR-1) { setflag(b); }
        if (!borrow) return;
        ++b;
        while(b<NR && zero[b]) {
            zero[b]=false; one[b]=true; 
            extra[b]=1-extra[b];
            b++;
        }
        if (extra[b]) validate(b); // end block
        for(int i=b*R; i<(b+1)*R && i<N; ++i) {
            if (C[i]=='0') { C[i]='1'; }
            else { C[i]='0'; break; }
        }
        if (b<NR-1) { setflag(b); }
    }
}

int main()
{
    scanf("%d%d ", &N, &Q);
    gets(A); reverse(A, A+N);
    gets(B); reverse(B, B+N);

    int carry=0;
    for(int i=0; i<N; ++i) {
        int d=A[i]-'0' + B[i]-'0' + carry;
        carry = d>>1;
        d%=2;
        C[i]=char(d+'0');
    }
    if (carry) { C[N]='1'; }
    else { C[N]='0'; }
    C[N+1]='\0';

    //puts(C);
    ++N; R=int(sqrt(N)); assert(R>0);
    NR=(N+R-1)/R;

    for(int b=0; b<NR-1; ++b) {
        setflag(b);
        extra[b]=0;
    }

    char cmd[30];
    for(int q=0; q<Q; ++q) {
        gets(cmd);
        int idx, val; // op=0 get, op=1 set
        const char *subcmd = cmd + strlen("set_a ");
        if (cmd[0]=='g') {
            sscanf(subcmd, "%d", &idx);
            char ch = query(idx);
            //printf("ans: "); 
            putchar(ch); //putchar('\n');
        }
        else {
            sscanf(subcmd, "%d %d", &idx, &val);
            char *p;
            if (cmd[4]=='a') p=A;
            else p=B;
            if (p[idx]==char(val+'0')) {}
            else { p[idx]=char(val+'0'); update(idx, val); }
        }
        //printf("C: %s\n", C);
    }
    putchar('\n');
}

// This is a simple problem but a bit messy to implement
// my algorithm is O(Q*sqrt(N))
// basic idea is to use a block of sqrt(N) to keep track of blocks with all '1's and blocks with all '0's
// extra[b] is 0 if the underlying C[] are the actual bits, and extra[b]=1 if the underlying C[] are the complementing bits
//
// Changing Bits    cpp     2012-02-27 04:56:15     Processed   Accepted
// Score: 30
//  View Details
//  Changing Bits   cpp     2012-02-27 02:29:34     Processed   Wrong Answer
//  1/11 testcases passed
//  Score: 1
//      View Details
//      Changing Bits   cpp     2012-02-27 02:19:28     Processed   Wrong Answer
//      1/11 testcases passed
//      Score: 1
//          View Details
//          Changing Bits   cpp     2012-02-27 01:30:53     Processed   Wrong Answer
//          1/11 testcases passed
//          Score: 1
//              View Details
//              Changing Bits   cpp     2012-02-27 01:17:36     Processed   Wrong Answer
//              1/11 testcases passed
//              Score: 1
//                  View Details
//                  Changing Bits   cpp     2012-02-27 01:02:29     Processed   Wrong Answer
//                  1/11 testcases passed
//                  Score: 1
//                      View Details
