// Manacher's algorithm
//
// finds maximal palindrome in all substring

#include <cstdio>
#include <cstring>
using namespace std;

void manacher(const char *str, int pal[])
{
    int center, span, pos, curr;
    int n = strlen(str)*2;
    pal[0] = 0;
    pal[1] = 1;
    center = 1; span = 1;
    for (pos=2; pos <= 2*n; ++pos) {
        int left, right, ll, rr;
        right = (center-1)/2 + span/2;
        curr = pal[2*center - pos];  // span of left image
        rr = (pos-1)/2 + curr/2;
        if (rr >= right) { // extend
            ll = pos/2 + curr/2;
            while (0<=ll && rr<n && str[--ll] == str[++rr])
                curr += 2;
            pal[pos] = curr;
            center = pos;
        } else {
            pal[pos] = curr;
        }
    }
}

void print(int v[], int n)
{
    for (int i=0; i<n; ++i)
        printf("%d ", v[i]);
    putchar('\n');
}

int main()
{
    int pal[100];
    const char *s;
    s = "a"; manacher(s, pal); print(pal, 2*strlen(s)+1);
    s = "aba"; manacher(s, pal); print(pal, 2*strlen(s)+1);
    s = "abababa"; manacher(s, pal); print(pal, 2*strlen(s)+1);
    s = "ccbbaa"; manacher(s, pal); print(pal, 2*strlen(s)+1);
    s = "cbaabc"; manacher(s, pal); print(pal, 2*strlen(s)+1);
}

// http://tristan-interview.blogspot.com/2011/11/longest-palindrome-substring-manachers.html
