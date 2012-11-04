#include <cstdio>
#include <cstring>
using namespace std;

char code[105];
char tmp[105];

void solve()
{
    int n = strlen(tmp); //puts(tmp);
    int pos = 0;
    int dir = +1;
    int cnt[10] = {0};
    while (0<=pos && pos<n) {
        int oldpos = pos;
        if (tmp[pos] == '<') dir = -1;
        else if (tmp[pos] == '>') dir = 1;

        pos += dir;
        while (0<= pos && pos < n && tmp[pos] == 'X')
            pos += dir;

        if ('0' <= tmp[oldpos] && tmp[oldpos] <= '9') {
            cnt[tmp[oldpos]-'0']++;
            if (tmp[oldpos] > '0') tmp[oldpos]--;
            else tmp[oldpos] = 'X';
        } else {
            if (0<=pos && pos<n)
                if (tmp[pos] == '<' || tmp[pos] == '>')
                    tmp[oldpos] = 'X';
        }
    }
    for (int i=0; i<=9; ++i) {
        if (i) putchar(' ');
        printf("%d", cnt[i]);
    }
    putchar('\n');
}

int main()
{
    int n, q; scanf("%d%d ", &n, &q);
    gets(code);

    for (int i=0; i<q; ++i) {
        int l, r; scanf("%d%d", &l, &r);
        --l;
        strncpy(tmp, code+l, r-l);
        tmp[r-l]='\0';
        solve();
    }
}
