// continued-fractions.cpp
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

class Frac {
private:
    int64 num, deno;
private:
    void init(int64 a, int64 b);
    int64 gcd(int64 a, int64 b);
public:
    Frac(int64 a, int64 b);
    Frac(const vector<int>& fracs);
    Frac operator+(const Frac &other) const;
    Frac operator-(const Frac &other) const;
    Frac operator*(const Frac &other) const;
    Frac operator/(const Frac &other) const;
    vector<int64> toContinuous() const;

    void print() const;
    void print2() const;
};

Frac::Frac(int64 a, int64 b) {
    init(a, b);
}

Frac::Frac(const vector<int> &fracs) {
    int64 a = 1, b = 0;
    int64 l = fracs.size();
    for (int i = l-1; i >= 0; --i) {
        int64 p = a;
        a = fracs[i] * a + b;
        b = p;
    }
    init(a, b);
}

void Frac::init(int64 a, int64 b) {
    assert(b != 0);
    int64 g = gcd(a, b);
    a /= g; b /= g;
    num = a; deno = b;
}

int64 Frac::gcd(int64 a, int64 b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

Frac Frac::operator+(const Frac &other) const {
    int64 a1 = num;
    int64 b1 = deno;
    int64 a2 = other.num;
    int64 b2 = other.deno;

    int64 c = a1 * b2 + a2 * b1;
    int64 d = b1 * b2;
    return Frac(c, d);
}

Frac Frac::operator-(const Frac &other) const {
    int64 a1 = num;
    int64 b1 = deno;
    int64 a2 = other.num;
    int64 b2 = other.deno;

    int64 c = a1 * b2 - a2 * b1; assert(c >= 0);
    int64 d = b1 * b2;
    return Frac(c, d);
}

Frac Frac::operator*(const Frac &other) const {
    int64 a1 = num;
    int64 b1 = deno;
    int64 a2 = other.num;
    int64 b2 = other.deno;

    int64 c = a1 * a2;
    int64 d = b1 * b2;
    return Frac(c, d);
}

Frac Frac::operator/(const Frac &other) const {
    int64 a1 = num;
    int64 b1 = deno;
    int64 a2 = other.num;
    int64 b2 = other.deno;

    int64 c = a1 * b2;
    int64 d = b1 * a2;
    return Frac(c, d);
}

vector<int64> Frac::toContinuous() const {
    vector<int64> v;
    int64 a = num, b = deno;
    while (b != 0) {
        v.push_back(a / b);
        int64 p = a;
        a = b;
        b = p % a;
    }
    return v;
}

void Frac::print() const {
    cout << "Frac: " << num << " / " << deno << endl;
}

void Frac::print2() const {
    vector<int64> v = toContinuous();
    for (int64 k : v) {
        cout << k << ' ';
    }
    cout << endl;
}

int main() {
    int tcase = 0;
    int n1, n2;
    while (cin >> n1 >> n2) {
        vector<int> v1, v2;
        for (int i = 0; i < n1; ++i) {
            int k; cin >> k; v1.push_back(k);
        }
        for (int i = 0; i < n2; ++i) {
            int k; cin >> k; v2.push_back(k);
        }
        Frac f1(v1); //f1.print();
        Frac f2(v2); //f2.print();

        cout << "Case " << (++tcase) << ":" << endl;
        //(f1+f2).print();
        (f1+f2).print2();
        (f1-f2).print2();
        (f1*f2).print2();
        (f1/f2).print2();
    }
}
