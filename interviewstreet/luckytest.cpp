// luckytest.cpp
//
// find all integer representable as sum of 18 or less digits
//
#include <cstdio>
using namespace std;

bool dp[20][1600];

int main()
{
    dp[0][0]=true;
    for(int len=1; len<=18; len++)
    for(int sum=0; sum<1600; sum++)
    for(int d=0; d<10; ++d) if (sum>=d*d)
        if (dp[len-1][sum-d*d])
            dp[len][sum]=true;

    for(int sum=0; sum<1600; ++sum)
    for(int len=0; len<=18; ++len)
        if (dp[len][sum]) { 
            printf("%d\n", sum); break; 
        }
}
