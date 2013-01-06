class Solution {
public:
    int lengthOfLastWord(const char *s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = 0;
        for (const char *p = s; *p ; ) {
            for (; *p && *p == ' '; ++p)
                ;
            if (!*p) break;
            const char *q;
            for (q = p+1; *q && *q != ' '; ++q)
                ;
            if (q>p)
                len = q-p;
            p = q;
        }
        return len;
    }
};
