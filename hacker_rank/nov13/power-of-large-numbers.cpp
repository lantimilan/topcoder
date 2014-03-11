// power-of-large-numbers.cpp
//
// to compute A^B mod 10^9 + 7 efficiently
// A and B are both 10^100000
//
// since M is prime, Fermat's Little Theorem
// A^(M-1) = 1
//
// notice that if M is not prime, we can use Chinese Remainder's Theorem

#include <iostream>
using namespace std;

const int M = 1e9+7;

// Horner's rule
int process(const string &s, int rem)
{
    long long ans = 0;
    for (int i = 0; i < s.length(); ++i) {
        ans = ans * 10 + s[i] - '0';
        ans %= rem;
    }
    return (int)ans;
}

// return A^B mod M
// invariant: base ^ B = A0 ^ B0
int mypow(int A, int B)
{
    long long ans = 1;
    long long base = A;
    while (B) {
        if (B & 1) ans = ans * base % M;
        base = base * base % M;
        B /= 2;
    }
    return ans;
}

int main()
{
    int T; cin >> T;
    while (T--)
    {
        string strA, strB;
        cin >> strA >> strB;
        int A, B;
        A = process(strA, M);
        B = process(strB, M-1);
        //cout << "AB " << A << ' ' << B << endl;
        int ans = mypow(A, B);
        cout << ans << endl;
    }
}
