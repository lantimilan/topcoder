// bigint.cpp

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class bigint;  // forward declaration
bigint operator+(const bigint &a, const bigint &b);
bigint operator-(const bigint &a, const bigint &b);
bigint operator*(const bigint &a, const bigint &b);
bigint operator*(const bigint &a, int b);
pair<bigint,bigint> operator/(const bigint &a, const bigint &b);  // not implemented
ostream& operator<<(ostream &os, const bigint &b);

class bigint {
  public:
    // interface
    bigint& operator+=(const bigint &b);  // why return reference here? for a += b += c?
    bigint& operator-=(const bigint &b);
    bigint& operator*=(const bigint &b);
    bigint& operator*=(int b);

    static const int UNIT = 1e9;
    static const int PAD = 9;  // digits in one unit

    // constructor
    bigint();
    explicit bigint(int sign);
    bigint(int sign, const vector<int> &v);

    // getter
    int get_sign() const;
    const vector<int> &get_data() const;

  private:
    vector<int> data;
    int sign;

    bigint& slow_mult(const bigint &b);
    bigint& fast_mult(const bigint &b);

    pair<bigint,bigint> split(int l);
    // static
    static vector<int> add(const vector<int> &v1, const vector<int> &v2);
    static vector<int> sub(const vector<int> &v1, const vector<int> &v2);
    static vector<int> mult(const vector<int> &v1, const vector<int> &v2);
    static vector<int> mult(const vector<int> &v1, int b);
    static int cmp(const vector<int> &v1, const vector<int> &v2);
    static int show_sign(int k);
    static void lshift(vector<int> &v, int p);
};

// global operators
ostream& operator<<(ostream &os, const bigint &b)
{
    const vector<int> &v = b.get_data();
    if (v.empty()) { return os << 0; }
    int i;
    for (i=v.size()-1; i>0 && v[i] == 0; --i) ;  // skip leading zero
    if (b.get_sign() < 0 && v[i] > 0) os << "-";  // minus sign if negative
    os << v[i];
    for (--i; i>=0; --i) os << setfill('0') << setw(b.PAD) << v[i];
    return os;
}

bigint operator+(const bigint &a, const bigint &b)
{
    bigint c = a; c += b; return c;
}

bigint operator-(const bigint &a, const bigint &b)
{
    bigint c = a; c -= b; return c;
}

bigint operator*(const bigint &a, const bigint &b)
{
    bigint c = a; c *= b; return c;
}

bigint operator*(const bigint &a, int b)
{
    bigint c = a; c *= b; return c;
}


// constructors
bigint::bigint() { sign=1; }
bigint::bigint(int sign) { this->sign=sign; }
bigint::bigint(int sign, const vector<int> &v) { this->sign = sign; this->data = v; }

// getters
int bigint::get_sign() const { return sign; }
const vector<int> & bigint::get_data() const { return data; }

// members
bigint& bigint::operator+=(const bigint &b)
{
    vector<int> v;
    if (this->sign == b.sign) {
        v = add(data, b.data);
    } else {
        if (cmp(data, b.data) >= 0) {
            v = sub(data, b.data);
        } else {  // need to change sign
            this->sign = b.sign;
            v = sub(b.data, data);
        }
    }
    this->data = v;
    return *this;
}

bigint& bigint::operator-=(const bigint &b)
{
    vector<int> v;
    if (this->sign != b.sign) {
        v = add(data, b.data);
    } else {
        if (cmp(data, b.data) >= 0) {
            v = sub(data, b.data);
        } else {
            this->sign = -b.sign;
            v = sub(b.data, data);
        }
    }
    this->data = v;
    return *this;
}

bigint& bigint::operator*=(int b)
{
    this->sign = this->sign * show_sign(b);
    if (b < 0) b = -b;
    this->data = mult(this->data, b);
    return *this;
}

bigint& bigint::operator*=(const bigint &b)
{
    return slow_mult(b);
    // return fast_mult(b);
}

// static
vector<int> bigint::mult(const vector<int> &v1, int b)
{
    assert(b >= 0 && "multiplier must be nonnegative");
    vector<int> vec(v1.size());
    int carry = 0;
    for (int i=0; i<v1.size(); ++i) {
        long long t = carry + (long long)b * v1[i];
        carry = t / UNIT;
        vec[i] = t % UNIT;
    }
    if (carry) vec.push_back(carry);
    return vec;
}

bigint& bigint::slow_mult(const bigint &b)
{
    this->sign = this->sign * b.sign;
    vector<int> ans;
    for (int i=0; i<this->data.size(); ++i) {
        vector<int> tmp = mult(b.data, this->data[i]);
        lshift(tmp, i);
        ans = add(ans, tmp);
    }
    this->data = ans;
    return *this;
}

/*
bigint bigint::fast_mult(const bigint &b)
{
    int l1, l2, t1, t2;
    bigint a1, a2, b1, b2;
    l1 = data.size(); l2 = b.data.size();

    if (min(l1,l2) <5) return slow_mult(b);

    int l = max(l1, l2), m = l/2;
    t1 = min(m, l1); t2 = l1 - t1;
    a1.data.resize(t1); a2.data.resize(t2);
    for (int i=0; i<t1; ++i) a1.data[i] = data[i];
    for (int i=0; i<t2; ++i) a2.data[i] = data[i+t1];
    a1.sign = a2.sign = this->sign;

    t1 = min(m, l2); t2 = l2 - t1;
    b1.data.resize(t1); b2.data.resize(t2);
    for (int i=0; i<t1; ++i) b1.data[i] = b.data[i];
    for (int i=0; i<t2; ++i) b2.data[i] = b.data[i+t1];
    b1.sign = b2.sign = b.sign;

    bigint A, B, C;
    A = a2.fast_mult(b2);
    B = (a1+a2).fast_mult(b1+b2);
    C = a1.fast_mult(b1);

    A.lshift(2*m);
    B.lshift(m);
    return A+B+C;
}
*/

vector<int> bigint::add(const vector<int> &v1, const vector<int> &v2)
{
    int carry = 0;
    int n1, n2, n3;
    n1 = v1.size(); n2 = v2.size();
    n3 = max(n1, n2);
    vector<int> v3(n3);
    for (int i=0; i<n3; ++i) {
        int t = carry;
        if (i<n1) t += v1[i];
        if (i<n2) t += v2[i];
        carry = t / UNIT;
        v3[i] = t % UNIT;
    }
    if (carry) v3.push_back(carry);
    return v3;
}

vector<int> bigint::sub(const vector<int> &v1, const vector<int> &v2)
{
    int n1, n2, n3;
    assert(cmp(v1, v2) >= 0 && "subtract large from small");
    n1 = v1.size(); n2 = v2.size(); n3 = n1;
    vector<int> v3(n3);
    int borrow = 0;
    for (int i=0; i<n1; ++i) {
        int t = v1[i] - borrow;
        if (i < n2) t -= v2[i];
        if (t < 0) { borrow = 1; t += UNIT; }
        else { borrow = 0; }
        v3[i] = t;
    }
    return v3;
}

int bigint::cmp(const vector<int> &v1, const vector<int> &v2)
{
    int n1, n2;
    n1 = v1.size(); n2 = v2.size();
    for (; n1>0 && v1[n1-1] == 0; n1--) ;  // skip leading zero
    for (; n2>0 && v2[n2-1] == 0; n2--) ;  // skip leading zero
    if (n1 != n2) return show_sign(n1-n2);
    for (int i=n1-1; i>=0; --i) {
        if (v1[i] != v2[i]) return show_sign(v1[i]-v2[i]);
    }
    return 0;
}

int bigint::show_sign(int k)
{
    if (k>=0) return 1;
    else return -1;
}

void bigint::lshift(vector<int> &v, int p)
{
    int n = v.size();
    v.resize(n+p);
    for (int i=n-1, j=n+p-1; i>=0; --i, --j)
        v[j] = v[i];
    for (int i=0; i<p; ++i)
        v[i] = 0;
}
// end static

// test code
int main()
{
    vector<int> a(4, 123456789), b(4, 987654321);
    bigint b1(1,a), b2(1,b), b3;
    cout << b1 << ' ' << b2 << endl;
    cout << b1 + b2 << endl;
    cout << b1 - b2 << endl;
    cout << b1 * b2 << endl;
}
