// DELNMS.cpp
//
// naive algorithm
// 1 element at a time
//
// notice that n is 10^5 and we need better than O(n^2)

#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    int n; scanf("%d", &n);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);
        printf("%d %d\n", 1, n-i);
    }
}

// Correct Answer
// Execution Time: 0.17
