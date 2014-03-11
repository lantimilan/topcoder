#include <algorithm>
#include <iostream>
#include <vector>

static const int MaxN = 10000, Mod = 1000000007;
static int nCr[MaxN+1][MaxN+1];

int main()
{
    // Precalculate binomial coefficients:
    for (int n = 0; n <= MaxN; ++n)
    {
        nCr[n][0] = nCr[n][n] = 1;
        for (int r = 1; r < n; ++r)
            nCr[n][r] = (nCr[n - 1][r] + nCr[n - 1][r - 1])%Mod;
    }

    int cases = 0;
    std::cin >> cases;
    for (int caseno = 1; caseno <= cases; ++caseno)
    {
        // Read input:
        int N = 0, K = 0;
        std::cin >> N >> K;
        std::vector<int> A(N);
        for (int i = 0; i < N; ++i)
            std::cin >> A[i];

        // Calculate sum:
        std::sort(A.begin(), A.end());
        int answer = 0;
        for (int i = K - 1; i < N; ++i)
            answer = (answer + (long long)nCr[i][K - 1]*A[i])%Mod;

        std::cout << "Case #" << caseno << ": " << answer << std::endl;
    }
}
