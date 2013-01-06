#include <cstdio>
#include <cstring>
using namespace std;

char buf[100000+5];

int main()
{
    int i, j, n;
    const char *p;
    gets(buf);
    n = strlen(buf);
    for (i=0; i<n; ++i)
        if (buf[i] == '0') break;
    if (i>=n) p = buf+1;
    else {
        for (j=i; j>0; --j)
            buf[j] = buf[j-1];
        p = buf+1;
    }
    puts(p);
}
