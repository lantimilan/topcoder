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
    static const int PAD = 9;  // log_10 of UNIT
//public:
    bigint();
    void print(ostream &os);
    bigint operator+(const bigint &b);
    bigint operator-(const bigint &b);
    bigint operator*(const bigint &b);
    bigint operator/(const bigint &b);  // not implemented
    void lshift(int n);
    void trim();  // remove leading zeros
//private:
    bigint add(const vector<int> &b);
    bigint sub(const vector<int> &b);
    bigint slowmult(const bigint &b);
    bigint fastmult(const bigint &b);
    bigint single_mult(int b);
    int cmp(const vector<int> &b);
};

ostream& operator<<(ostream& os, const bigint &b) {
    if (b.data.size() == 0) return os << 0;
    int i = b.data.size()-1;
    for (; i > 0 && b.data[i] == 0; --i) ;
    if (i==0 && b.data[i] == 0) if (b.sign == -1) os << "-";
    os << b.data[i];
    for (--i; i>=0; --i)
        os << setfill('0') << setw(b.PAD) << b.data[i];  // need to pad zeros
    return os;
}

bigint::bigint() {
    sign = 1;
}

void bigint::lshift(int n)
{
    int l = data.size();
    data.resize(l + n);
    for (int i=l-1, j=l+n-1; i>=0; --i, --j) {
        data[j] = data[i];
    }
    for (int i=0; i<n; ++i) data[i] = 0;
}

void bigint::trim()
{
    int len = data.size();
    while (len-1 > 0 && data[len-1] == '0')
        len--;
    //assert(len > 0);
    data.resize(len);
}

int bigint::cmp(const vector<int> &b)
{
    int n1 = data.size(), n2 = b.size();
    // skip leading zeros
    for (; n1 > 0 && data[n1-1] == 0; --n1) ;
    for (; n2 > 0 && b[n2-1] == 0; --n2) ;
    if (n1 != n2) return n1 - n2;
    for (int i=n1-1; i>=0; --i)
        if (data[i] != b[i]) return data[i] - b[i];
    return 1;  // treat zero as +0
}

int getsign(int k)
{
    if (k>=0) return 1;
    else return -1;
}

bigint bigint::operator+(const bigint &b) {
    bigint ans;
    int sign;
    if (this->sign > 0 && b.sign < 0) { ans = sub(b.data); sign = getsign(cmp(b.data)); }
    if (this->sign > 0 && b.sign > 0) { ans = add(b.data); sign = 1; }
    if (this->sign < 0 && b.sign > 0) { ans = sub(b.data); sign = -getsign(cmp(b.data)); }
    if (this->sign < 0 && b.sign < 0) { ans = add(b.data); sign = -1; }
    ans.sign = sign; assert(sign == -1 || sign == 1);
    ans.trim();
    return ans;
}

bigint bigint::operator-(const bigint &b) {
    bigint ans;
    int sign;
    if (this->sign > 0 && b.sign < 0) { ans = add(b.data); sign = 1; }
    if (this->sign > 0 && b.sign > 0) { ans = sub(b.data); sign = getsign(cmp(b.data)); }
    if (this->sign < 0 && b.sign > 0) { ans = sub(b.data); sign = -1; }
    if (this->sign < 0 && b.sign < 0) { ans = add(b.data); sign = -getsign(cmp(b.data)); }
    ans.sign = sign; assert(sign == -1 || sign == 1);
    ans.trim();
    return ans;
}

bigint bigint::operator*(const bigint &b) {
    //bigint ans = fastmult(b);
    bigint ans = slowmult(b);
    ans.trim(); assert(sign == -1 || sign == 1);
    return ans;
}

bigint bigint::add(const vector<int> &b)
{
    int n1 = data.size(), n2 = b.size();
    int n3 = max(n1,n2);
    bigint c; c.data.resize(n3);
    int carry = 0;
    for (int i=0; i<n3; ++i) {
        int t = carry;
        if (i < n1) t += data[i];
        if (i < n2) t += b[i];
        c.data[i] = t % UNIT;
        carry = t / UNIT;
    }
    if (carry) c.data.push_back(carry);
    return c;
}

bigint bigint::sub(const vector<int> &b)
{
    vector<int> v1, v2;
    v1 = this->data; v2 = b;
    if (cmp(b) < 0) v1.swap(v2);

    bigint ans; ans.data.resize(v1.size());
    int borrow = 0;
    for (int i=0; i<v1.size(); ++i) {
        int t = v1[i] - borrow;
        if (i < v2.size()) t -= v2[i];
        if (t < 0) { borrow = 1; t += UNIT; }
        else { borrow = 0; }
        ans.data[i] = t;
    }
    assert(borrow == 0);
    return ans;
}

bigint bigint::single_mult(int b)
{
    // mult b[i] to a
    vector<int> row(data.size(), 0);
    int64 t=0, carry=0;
    for (int j=0; j<data.size(); ++j) {
        t = carry + (int64)b * data[j];  // forgot to add carry earlier
        carry = t / UNIT;
        row[j] = t % UNIT;
    }
    if (carry) row.push_back(carry);
    bigint ans; ans.data = row;
    ans.sign = getsign(b * this->sign);
    return ans;
}

bigint bigint::slowmult(const bigint &b)
{
    int sign;
    if (this->sign == b.sign) sign = 1;
    else sign = -1;
    int n1 = data.size(), n2 = b.data.size();
    int n3 = n1*n2;
    bigint c; c.sign = sign;
    for (int i=0; i<n2; ++i) {
        bigint tmp = single_mult(b.data[i]);
        tmp.lshift(i);
        c = c.add(tmp.data);
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
    if (min(l1,l2) < 5) return slowmult(b);

    bigint a1, a2, b1, b2;
    a1.data.resize(max(l1-l, 0));
    a2.data.resize(min(l1, l));
    a1.sign = a2.sign = this->sign;
    b1.data.resize(max(l2-l, 0));
    b2.data.resize(min(l2, l));
    b1.sign = b2.sign = b.sign;
    for (int i=0; i<l; ++i) {
        if (i < a2.data.size()) a2.data[i] = data[i];
        if (i < b2.data.size()) b2.data[i] = b.data[i];
    }
    for (int i=l; i<n; ++i) {
        if (i-l < a1.data.size()) a1.data[i-l] = data[i];
        if (i-l < b1.data.size()) b1.data[i-l] = b.data[i];
    }
    bigint A, B, C;
    A = a1.fastmult(b1);
    B = (a1+a2).fastmult(b1+b2);
    C = a2.fastmult(b2);
    A.lshift(2*l);
    B = B - (A + C);
    B.lshift(l);
    bigint ans = A+B+C;
    ans.trim();
    return ans;
}

int gcd(int a, int b)
{
    return b==0 ? a : gcd(b, a%b);
}

bigint mypow(int a, int n)
{
    bigint c; c.data = vector<int>(1,1);
    /*
    for (int i=0; i<n; ++i) c = c.single_mult(a);
    return c;
    */
    bigint base; base.data = vector<int>(1,a);
    while (n > 0) {
        if (n & 1) c = c * base;
        base = base * base;
        n /= 2;
    }
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
        ans = ans.single_mult(num[i]);
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
    cout << ans << endl;

    /*
    bigint a, b;
    a.data = vector<int>(2, 123456789);
    b.data = vector<int>(2, 987654321);
    cout << (a+b) << endl;
    cout << (a-b) << endl;
    cout << (a*b) << endl;
    cout << (a-a) << endl;
    b.data[1] = a.data[1];
    cout << (b-a) << endl;
    b.data[1] = b.data[0];
    b.data[0] = a.data[0];
    cout << (b-a) << endl;
    */
}

