// square subseq
//
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD=1000000000+7;

char s[205];
char s1[205], s2[205];
int common[205][205];

inline int add(int a, int b)
{
    return ((long long)a+b) %MOD;
}
inline int sub(int a, int b)
{
    return ((long long)a-b+MOD)%MOD;
}

void refadd(int &a, int b)
{
    a = ((long long)a+b)%MOD;
}

// calculate number of common subseq betw s1[] and s2[]
// with s1[n1-1] must be matched
int calc()
{
    //printf("calc %s %s\n", s1, s2);
    memset(common, 0, sizeof common);
    int ans=0;
    int n1=strlen(s1), n2=strlen(s2);

    common[0][0]=1;
    for(int i=0; i<=n1; ++i)
    for(int j=0; j<=n2; ++j)
    {
        if (i-1>=0) refadd(common[i][j], common[i-1][j]);
        if (j-1>=0) refadd(common[i][j], common[i][j-1]);
        if (i-1>=0 && j-1>=0 && s1[i-1]!=s2[j-1])
            common[i][j]=sub(common[i][j], common[i-1][j-1]);
    }

    for(int j=0; j<n2; ++j) if (s1[n1-1]==s2[j])
    {
        refadd(ans, common[n1-1][j]);
    }

    //printf("ans %d\n", ans);
    return ans;
}

void solve(int tcase)
{
    gets(s); //puts(s);
    memset(s1, 0, sizeof s1);
    memset(s2, 0, sizeof s2);
    int n = strlen(s);
    int ans=0;

    for(int pos=0; pos+1<n; ++pos) {
        strncpy(s1, s, pos+1);
        strcpy(s2, s+pos+1);
        refadd(ans, calc());
    }
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d ", &T);
    for(int t=1; t<=T; ++t)
        solve(t);
}

// Square Subsequences  cpp     2012-02-17 11:08:17     Processed   Accepted    View Details
//
// #    Status  Signal  Time
// 1    Passed  Your code produced correct output for this testcase.    0.07061
// 2    Passed  Your code produced correct output for this testcase.    0.070552
// 3    Passed  Your code produced correct output for this testcase.    0.564724
// 4    Passed  Your code produced correct output for this testcase.    0.503675
// 5    Passed  Your code produced correct output for this testcase.    0.383056
// 6    Passed  Your code produced correct output for this testcase.    0.514264
// 7    Passed  Your code produced correct output for this testcase.    0.695142
// 8    Passed  Your code produced correct output for this testcase.    0.524266
// 9    Passed  Your code produced correct output for this testcase.    0.556575
// 10   Passed  Your code produced correct output for this testcase.    0.473493
//
// Rank     Hacker  Country     Score   Submissions     Solved
// 11   diogoaos    Brazil  811.00  56  21
// 12   lantimilan  USA     784.00  79  19
// 13   liangjiaxing    Canada  778.00  50  19
// 14   jin.ubc     Canada  763.00  42  20
// 15   uwi     Japan   760.00  39  19
// 15   megaterik   Belarus     760.00  102     22
// 17   hadi    Iran    740.00  48  19
// 18   Amtrix  Germany     735.00  20  19
// 19   chhung6     Hong Kong   732.00  76  19
// 20   ttim    Kazakhstan  730.00  95  19
