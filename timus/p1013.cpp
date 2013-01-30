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
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

struct bigint {
    vector<int> data;
    int sign;
    static const int UNIT = 1e9;  // 2*UNIT fits INT_MAX
//public:
    void print();
    bigint operator+(const bigint &b);
    bigint operator-(const bigint &b);
    bigint operator*(const bigint &b);
    bigint operator/(const bigint &b);
    void lshift(int n);
//private:
    bigint add(const bigint &b);  // unsigned add
    bigint sub(const bigint &b);
    bigint mult(const bigint &b);
    bigint fastmult(const bigint &b);
    int cmp(const bigint &b);
};

void bigint::lshift(int n)
{
    int l = data.size();
    data.resize(l + n);
    for (int i=l-1, j=n-1; i>=0; --i, --j) {
        data[j] = data[i]; data[i] = 0;
    }
}

void bigint::print()
{
    int i;
    for (i=data.size()-1; i>=0 && data[i] == 0; --i) ;  // skip leading zeros
    if (i < 0) cout << 0 << endl;
    else {
        cout << data[i];
        for (--i; i>=0; --i)
            cout << setfill('0') << setw(9) << data[i];  // need to pad zeros
        cout << endl;
    }
}

int bigint::cmp(const bigint &b)
{
    int n1 = data.size(), n2 = b.data.size();
    if (n1 != n2) return n1 - n2;
    for (int i=n1-1; i>=0; --i)
        if (data[i] != b.data[i]) return data[i] - b.data[i];
    return 0;
}

bigint bigint::operator+(const bigint &b) {
    bigint ans;
    int sign;
    if (this->sign > 0 && b.sign < 0) { ans = sub(b); sign = cmp(b); }
    if (this->sign > 0 && b.sign > 0) { ans = add(b); sign = 1; }
    if (this->sign < 0 && b.sign > 0) { ans = sub(b); sign = -cmp(b); }
    if (this->sign < 0 && b.sign < 0) { ans = add(b); sign = -1; }
    ans.sign = sign;
    return ans;
}

bigint bigint::operator-(const bigint &b) {
    bigint ans;
    int sign;
    if (this->sign > 0 && b.sign < 0) { ans = add(b); sign = 1; }
    if (this->sign > 0 && b.sign > 0) { ans = sub(b); sign = cmp(b); }
    if (this->sign < 0 && b.sign > 0) { ans = sub(b); sign = -1; }
    if (this->sign < 0 && b.sign < 0) { ans = add(b); sign = -cmp(b); }
    ans.sign = sign;
    return ans;
}

bigint bigint::operator*(const bigint &b) {
    bigint ans;
    int sign;
    if (this->sign != b.sign) sign = -1;
    else sign = 1;
    ans = fastmult(b);
    ans.sign = sign;
    return ans;
}

bigint bigint::add(const bigint &b)
{
    int n1 = data.size(), n2 = b.data.size();
    int n3 = max(n1,n2);
    bigint c; c.data.resize(n3);
    int carry = 0;
    for (int i=0; i<n3; ++i) {
        int t = carry;
        if (i < n1) t += data[i];
        if (i < n2) t += b.data[i];
        c.data[i] = t % UNIT;
        carry = t / UNIT;
    }
    if (carry) c.data.push_back(carry);
    return c;
}

bigint bigint::sub(const bigint &b)
{
    vector<int> v1, v2;
    v1 = this->data; v2 = b.data;
    if (cmp(b) < 0) v1.swap(v2);

    bigint ans; ans.data.resize(v1.size());
    int borrow = 0;
    for (int i=0; i<v1.size(); ++i) {
        int t = v1[i] - borrow;
        if (i < v2.size()) t -= v2[i];
        if (t < 0) borrow = 1;
        else borrow = 0;
        t += UNIT;
        ans.data[i] = t;
    }
    assert(borrow == 0);
    return ans;
}

bigint bigint::mult(const bigint &b)
{
    int n1 = data.size(), n2 = b.data.size();
    int n3 = n1*n2;
    bigint c; c.data.resize(n3);
    for (int i=0; i<n2; ++i) {
        // mult b[i] to a
        vector<int> row(n1, 0);
        int64 t=0, carry=0;
        for (int j=0; j<n1; ++j) {
            t = carry + (int64)b.data[i] * data[j];  // forgot to add carry earlier
            carry = t / UNIT;
            row[j] = t % UNIT;
        }
        if (carry) row.push_back(carry);
        bigint tmp; tmp.data = row;
        tmp.lshift(i);
        c = c.add(tmp);
    }
    return c;
}

// Karatsuba's algorithm
// O(n^1.59)
bigint bigint::fastmult(const bigint &b)
{
    int l1 = data.size(), l2 = b.data.size();
    int n = max(l1, l2);
    int l = n/2;
    if (min(l1,l2) < 5) return mult(b);

    bigint a1, a2, b1, b2;
    a1.data.resize(max(l1-l,0));
    a2.data.resize(l);
    b1.data.resize(max(0,l2-l));
    b2.data.resize(l);
    for (int i=0; i<l; ++i) {
        if (i < a1.data.size()) a1.data[i] = data[i];
        if (i < b1.data.size()) b1.data[i] = b.data[i];
    }
    for (int i=l; i<n; ++i) {
        if (i-l < a2.data.size()) a2.data[i-l] = data[i];
        if (i-l < b2.data.size()) b2.data[i-l] = b.data[i];
    }
    bigint A, B, C;
    A = a1.fastmult(b1);
    B = (a1+a2).fastmult(b1+b2);
    C = a2.fastmult(b2);
    A.lshift(2*l);
    B = B - (A + C);
    B.lshift(l);
    return A + B + C;
}

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

bigint mypow(int a, int n)
{
    bigint b; b.data = vector<int>(1,a);
    bigint c; c.data = vector<int>(1,1);
    for (int i=0; i<n; ++i)
        c = c * b;
    //cout << "mypow " << a << "^" << n << " " ; print(c);
    return c;
}

bigint choose(int n, int r)
{
    bigint ans; ans.data = vector<int>(1,1);
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

    for (int i=0; i<r; ++i) {
        bigint t; t.data = vector<int>(1, num[i]);
        ans = ans * t;
    }
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
        ans = ans + choose(other+1, zero) * mypow(K-1, other);
    }
    bigint t; t.data = vector<int>(1, K-1);
    ans = ans * t;
    ans.print();
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

