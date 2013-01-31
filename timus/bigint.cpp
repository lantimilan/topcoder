// bigint.cpp

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class bigint {
  public:
    // interface
    bigint operator+(const bigint &b) const;
    bigint operator-(const bigint &b) const;
    bigint operator*(const bigint &b) const;
    pair<bigint,bigint> operator/(const bigint &b) const;  // not implemented
    static const int UNIT = 1e9;
    static const int PAD = 9;  // digits in one unit

    // constructor
    bigint();
    bigint(int sign);
    bigint(int sign, const vector<int> &v);

    // mutator
    void lshift(int p);

    // getter
    int get_sign() const;
    const vector<int> &get_data() const;

  private:
    vector<int> data;
    int sign;

    bigint mult(int b) const;
    bigint slow_mult(const bigint &b) const;
    bigint fast_mult(const bigint &b) const;
    static vector<int> add(const vector<int> &v1, const vector<int> &v2);
    static vector<int> sub(const vector<int> &v1, const vector<int> &v2);
    static int cmp(const vector<int> &v1, const vector<int> &v2);
    static int show_sign(int k);
};

ostream& operator<<(ostream &os, const bigint &b)
{
    const vector<int> &v = b.get_data();
    if (v.empty()) { return os << 0; }
    int i;
    for (i=v.size()-1; i>0 && v[i] == 0; --i) ;  // skip leading zero
    if (b.get_sign() < 0 && v[i] > 0) os << "-";  // sign if negative
    os << v[i];
    for (--i; i>=0; --i) os << setfill('0') << setw(b.PAD) << v[i];
    //for (; i>=0; --i) os << v[i];
    return os;
}


bigint::bigint() { sign=1; }
bigint::bigint(int sign) { this->sign=sign; }

bigint::bigint(int sign, const vector<int> &v) { this->sign = sign; this->data = v; }

int bigint::get_sign() const { return sign; }
const vector<int> & bigint::get_data() const { return data; }

bigint bigint::operator+(const bigint &b) const
{
    vector<int> v;
    int s;
    if (this->sign == b.sign) {
        s = this->sign;
        v = add(data, b.data);
    } else {
        int s;
        if (cmp(data, b.data) >= 0) {
            s = this->sign;
            v = sub(data, b.data);
        } else {
            s = b.sign;
            v = sub(b.data, data);
        }
    }
    return bigint(s, v);
}

bigint bigint::operator-(const bigint &b) const
{
    vector<int> v;
    int s;
    if (this->sign != b.sign) {
        s = this->sign;
        v = add(data, b.data);
    } else {
        if (cmp(data, b.data) >= 0) {
            s = this->sign;
            v = sub(data, b.data);
        } else {
            s = -b.sign;
            v = sub(b.data, data);
        }
    }
    return bigint(s, v);
}

bigint bigint::operator*(const bigint &b) const
{
    return slow_mult(b);
    // return fast_mult(b);
}

bigint bigint::mult(int b) const
{
    assert(b >= 0);
    vector<int> v(data.size());
    int carry = 0;
    for (int i=0; i<data.size(); ++i) {
        long long t = carry + (long long)b * data[i];
        carry = t / UNIT;
        v[i] = t % UNIT;
    }
    if (carry) v.push_back(carry);
    return bigint(this->sign, v);
}

bigint bigint::slow_mult(const bigint &b) const
{
    int sign = this->sign * b.sign;
    bigint ans;
    for (int i=0; i<data.size(); ++i) {
    cout << "slow_mult " << i << endl;
        bigint tmp = b.mult(data[i]);
        tmp.lshift(i);
        ans = ans + tmp;
    }
    ans.sign = sign;
    return ans;
}

bigint bigint::fast_mult(const bigint &b) const
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
    assert(cmp(v1, v2) >= 0);
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
    for (; n1>0 && v1[n1-1] == 0; n1--) ;
    for (; n2>0 && v2[n2-1] == 0; n2--) ;
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

void bigint::lshift(int p)
{
    int n = data.size();
    for (int i=n-1, j=n+p-1; i>=0; --i, --j)
        data[j] = data[i];
    for (int i=0; i<p; ++i)
        data[i] = 0;
}

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
