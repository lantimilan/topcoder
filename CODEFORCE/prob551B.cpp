// prob551B.cpp
#include <cstdio>
#include <climits>
#include <cstring>
using namespace std;

const int M = 100000+5;
char a[M], b[M], c[M];
int A[30], B[30], C[30];

void extract(const char *s, int cnt[]) {
    for (; *s; ++s) {
        cnt[*s - 'a']++;
    }
}

void chmin(int &x, int y) {
    if (x > y) x = y;
}

void genstr(char *src, int srccnt[],
    const char *first, const int cnt1[],
    const char *second, const int cnt2[],
    int nfirst) {
    int pos = 0;
    int n1 = strlen(first);
    int n2 = strlen(second);
    for (int i = 0; i < nfirst; ++i) {
        for (int x = 0; x < 26; ++x) {
            srccnt[x] -= cnt1[x];
        }
        for (int p = 0; p < n1; ++p) {
            src[pos++] = first[p];
        }
    }
    while (true) {
        bool hasMore = true;
        for (int x = 0; x < 26; ++x) {
            if (srccnt[x] < cnt2[x]) {
                hasMore = false; break;
            }
        }
        if (!hasMore) break;
        for (int x = 0; x < 26; ++x) {
            srccnt[x] -= cnt2[x];
        }
        for (int p = 0; p < n2; ++p) {
            src[pos++] = second[p];
        }
    }
    int n = strlen(src);
    for (; pos < n; ++pos) {
        int x;
        for (x = 0; x < 26; ++x) if (srccnt[x]) break;
        src[pos] = char(x + 'a');
        srccnt[x]--;
    }
}

int calc(int first) {
    int ans = 100000;
    for (int x = 0; x < 26; ++x) {
        long long rem = A[x] - 1LL * B[x] * first;
        if (rem < 0) return -1;
        if (C[x]) chmin(ans, rem / C[x]);
    }
    return ans;
}

int main() {
    scanf("%s", a);
    //fgets(a, M, stdin);
    extract(a, A);
    scanf("%s", b);
    //fgets(b, M, stdin);
    extract(b, B);
    scanf("%s", c);
    //fgets(c, M, stdin);
    extract(c, C);

    //printf("%d %d %d\n", strlen(a), strlen(b), strlen(c));

    int n = strlen(a);
    int best = -1;
    int bestfirst = -1;
    for (int first = 0; first <= n; ++first) {
        int curr = calc(first);
        if (curr < 0) { continue; }
        curr += first;
        if (curr > best) {
            best = curr;
            bestfirst = first;
        }
    }
    //printf("%d\n", LINE_MAX);
    //printf("best %d bestfirst %d\n", best, bestfirst);
    genstr(a, A, b, B, c, C, bestfirst);
    puts(a);
}
