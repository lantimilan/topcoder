class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (haystack == NULL) return NULL;
        if (needle == NULL) return haystack;
        
        if (*haystack == 0) {
            if (*needle == 0) return haystack;
            else return NULL;
        }
        if (*needle == 0) return haystack;
        
        int n, m;
        n = strlen(haystack);
        m = strlen(needle);
        char *text, *patt;
        text = haystack; patt = needle;
        
        vector<int> q(m, -1);
        for (int i=1; i<m; ++i) {
            int p = i-1;
            while (p>=0 && patt[i] != patt[q[p]+1])
                p = q[p];
            if (p>=0) q[i] = q[p]+1;
        }
        
        for(int i=0, j=0; i<n; ++i) {            
            while (j>0 && text[i] != patt[j]) {
                j = q[j-1]+1;
            }
            if (text[i] == patt[j]) j++;
            if (j>=m) return text + i - (m-1);
        }
        return NULL;
    }
};