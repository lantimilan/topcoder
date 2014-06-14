// arithmetic.cpp

#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;

int intdiv(int a, int b)
{
    assert(a >= 0 && b > 0);
    int q = 0;
    int d = b;
    while (d <= a) d *= 2;
    d /= 2;
    while (d >= b) {
        int cur;
        if (a >= d) { cur = 1; a -= d; }
        else { cur = 0; }
        q = (q << 1) | cur;
        d /= 2;
    }
    return q;
}

string division(int a, int b)
{
    // assume a>=0 and b > 0, otherwise handle signs
    string ans;
    // get integral part
    int integral = intdiv(a, b);
    // done with integral part
    ostringstream oss; oss << integral;
    string intstr = oss.str();
    ans = intstr;
    a = a - integral * b;
    if (a == 0) return ans;
    map<int, int> rem_map;
    int pos = 0;
    string frac;
    while (!rem_map.count(a) && a > 0) {
        rem_map[a] = pos++;
        a *= 10;
        int q = intdiv(a, b);
        frac += char('0' + q);
        a -= q * b;
    }
    if (a > 0) {
        frac.insert(rem_map[a], 1, '(');
        frac += ")";
    }
    ans += "." + frac;
    return ans;
}

int main()
{
    int a, b; cin >> a >> b;
    cout << division(a,b) << endl;
}

// interesting testcase
// lyan@lyan-ThinkPad-T430:~/github/topcoder/misc$ ./a.out
// 123484  8238
// 14.(98956057295460063122117018693857732459334789997572226268511774702597717892692401068220441854819130857004127215343529983005583879582422918184025248846807477543092983733915999028890507404709881039087157076960427288176741927652342801650886137411993202233551832969167273610099538722991017237193493566399611556202961883952415634862830784170915270696771060937120660354454964797280893420733187666909444039815489196406894877397426559844622481184753580966253945132313668366108278708424374848264141781985918912357368293275066763777615926195678562757950958970623937848992473901432386501578052925467346443311483369749939305656712794367564942947317310026705511046370478271425103180383588249575139596)

