// two pointers mark range
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct mydate {
    int yy, mon, dd, hh, mm, ss;
};

int compare(mydate d1, mydate d2)
{
    if (d1.yy != d2.yy) return d1.yy - d2.yy;
    if (d1.mon != d2.mon) return d1.mon - d2.mon;
    if (d1.dd != d2.dd) return d1.dd - d2.dd;
    if (d1.hh != d2.hh) return d1.hh - d2.hh;
    if (d1.mm != d2.mm) return d1.mm - d2.mm;
    if (d1.ss != d2.ss) return d1.ss - d2.ss;
    return 0;
}

// advance dnow by incr seconds
mydate advance(mydate dnow, int incr)
{
    int hh, mm, ss, carry;
    ss = incr % 60;
    incr /= 60;
    mm = incr % 60;
    incr /= 60;
    hh = incr;

    carry = 0;
    mydate newdate = dnow;
    // seconds
    newdate.ss += ss;
    carry = newdate.ss / 60;
    newdate.ss = newdate.ss % 60;
    // minutes
    newdate.mm += mm + carry;
    carry = newdate.mm / 60;
    newdate.mm = newdate.mm % 60;
    // hours
    newdate.hh += hh + carry;
    carry = newdate.hh / 24;
    newdate.hh = newdate.hh % 60;
    // days
    int days_of_month[] = {0, 31, 29, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31};  // 2012 is leap year so Feb has 29 days

    // since incr <= 10^4 seconds, will never extend more than one day
    newdate.dd += carry;
    while (newdate.dd > days_of_month[newdate.mon]) {
        newdate.dd -= days_of_month[newdate.mon];
        newdate.mon++;
        if (newdate.mon > 12) {
            newdate.yy++;
            newdate.mon = 1;
        }
    }
    assert(newdate.dd <= days_of_month[newdate.mon]);
    return newdate;
}

char buf[5000000+5];
vector<mydate> vec;

void print(mydate dnow)
{
    printf("%4d-%02d-%02d %02d:%02d:%02d\n",
        dnow.yy, dnow.mon, dnow.dd,
        dnow.hh, dnow.mm, dnow.ss);
}

int main()
{
    int n, m; scanf("%d%d ", &n, &m); //printf("n %d  m %d\n", n, m);
    int i1, i2, cnt;
    while (gets(buf)) {
        // parse buf
        // 2012-MM-DD HH:MM:SS: MESSAGE
        int pos;
        mydate dnow;
        dnow.yy = 2012;
        pos = strlen("2012-");
        dnow.mon = (buf[pos] - '0') * 10 + (buf[pos+1] - '0');
        pos = strlen("2012-MM-");
        dnow.dd = (buf[pos] - '0') * 10 + (buf[pos+1] - '0');
        pos = strlen("2012-MM-DD ");
        dnow.hh = (buf[pos] - '0') * 10 + (buf[pos+1] - '0');
        pos = strlen("2012-MM-DD HH:");
        dnow.mm = (buf[pos] - '0') * 10 + (buf[pos+1] - '0');
        pos = strlen("2012-MM-DD HH:MM:");
        dnow.ss = (buf[pos] - '0') * 10 + (buf[pos+1] - '0');
        vec.push_back(dnow);
    }
    i1 = i2 = cnt = 0;
    while (i1 < vec.size()) {
        mydate next = advance(vec[i1], n-1);
        //print(vec[i1]); print(next); puts("");
        for (; i2 < vec.size() && compare(vec[i2], next) <= 0; ++i2) {
            if (++cnt >= m) break;
        }
        if (cnt >= m) break;
        i1++; cnt--;
    }
    if (i1 >= vec.size()) puts("-1");
    else print(vec[i2]);
}

// to check
