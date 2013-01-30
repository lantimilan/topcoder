// cap = ceil((N-1)/2)
// ans = sum {zero = 0 to cap} (other+1 choose zero) * 9^other
// other = N-1 - zero
// ans *= 9
//
// first digit can be 1 to 9
// then enumerate possible num of zero
//
// dude, large integer arithmetic

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;
typedef vector<int> bigint;

const int UNIT = 1e9;  // 2*UNIT fits INT_MAX

void print(const bigint &b)
{
    int i;
    for (i=b.size()-1; i>=0 && b[i] == 0; --i) ;
    if (i < 0) cout << 0 << endl;
    else {
        cout << b[i];
        for (--i; i>=0; --i)
            cout << setfill('0') << setw(9) << b[i];  // need to pad zeros
        cout << endl;
    }
}

bigint add(const bigint &a, const bigint &b)
{
    int n1 = a.size(), n2 = b.size();
    int n3 = max(n1,n2);
    bigint c(n3, 0);
    int carry = 0;
    for (int i=0; i<n3; ++i) {
        int t = carry;  // forgot to add carry earlier
        if (i < n1) t += a[i];
        if (i < n2) t += b[i];
        c[i] = t % UNIT;
        carry = t / UNIT;
    }
    if (carry) c.push_back(carry);
    return c;
}

bigint mult(const bigint &a, const bigint &b)
{
//cout << "mult " << a[0] << ' ' << b[0] << ' ';
    int n1 = a.size(), n2 = b.size();
    int n3 = n1*n2;
    bigint c(n3, 0);
    for (int i=0; i<n2; ++i) {
        // mult b[i] to a
        vector<int> row(n1, 0);
        int64 t=0, carry=0;
        for (int j=0; j<n1; ++j) {
            t = carry + (int64)b[i] * a[j];  // forgot to add carry earlier
            carry = t / UNIT;
            row[j] = t % UNIT;
        }
        //cout << "carry " << carry << endl;
        if (carry) row.push_back(carry);
        bigint tmp(i+row.size(), 0);
        for (int j=0; j<row.size(); ++j) tmp[i+j] = row[j];
        //cout << "tmp "; print(tmp);
        c = add(c, tmp);
    }
//print(c);
    return c;
}

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

bigint mypow(int a, int n)
{
    bigint b(1,a);
    bigint c(1,1);
    for (int i=0; i<n; ++i)
        c = mult(c, b);
    //cout << "mypow " << a << "^" << n << " " ; print(c);
    return c;
}

bigint choose(int n, int r)
{
    bigint ans(1,1);
    vector<int> num(r), deno(r);
    for (int i=0; i<r; ++i) num[i] = n-i;
    for (int i=0; i<r; ++i) deno[i] = i+1;

    for (int i=0; i<r; ++i) {
        int t = deno[i];
        while (t > 1) {
            for (int j=0; j<r; ++j) {
                int g = gcd(t, num[j]);
                t /= g; num[j] /= g;
            }
        }
    }

    for (int i=0; i<r; ++i) ans = mult(ans, bigint(1,num[i]));
    return ans;
}

/*
int64 mypow(int a, int n)
{
    int64 ans = 1;
    for (int i=0; i<n; ++i)
        ans *= a;
    return ans;
}

int64 choose(int n, int r)
{
    int64 ans = 1;
    for (int i=0; i<r; ++i) ans *= (n-i);
    for (int i=1; i<=r; ++i) ans /= i;
    return ans;
}
*/

int main()
{
    int N, K; cin >> N >> K;
    bigint ans;

    int zero, other;
    for (zero = 0; zero <= N/2; ++zero) {
        other = N-1 - zero;
        ans = add(ans, mult(choose(other+1, zero), mypow(K-1, other)));
    }
    ans = mult(ans, bigint(1,K-1));
    print(ans);
    //cout << ans << endl;

    //vector<int> x(2); x[0]=1; x[1] = 1;
    //print(x);
    /* test code for bigint
    bigint a(2), b(2);
    a[0] = 123456789; a[1] = 123456789;
    b[0] = 987654321;
    b[1] = 987654321;
    print(a);
    print(b);
    print(mult(a,b));
    */
}

// 4746021  15:23:15 29 Jan 2013
// lantimilan  1012. K-based Numbers. Version 2    C++ Accepted    0.062   232 KB
//
// missed carry in both add() and mult()
// also missed padding leading zeros when print bigint
//
