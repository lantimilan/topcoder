class Solution {
public:
    int getid(char ch)
    {
        if ('A' <= ch && ch <= 'Z') return ch - 'A';
        else return 26 + ch - 'a';
    }
    bool valid(int cnt1[], int cnt2[], int n)
    {
        for (int i=0; i<n; ++i)
            if (cnt1[i] < cnt2[i]) return false;
        return true;
    }
    string minWindow(string S, string T) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (T.empty()) return "";
        
        int n, m;
        n = S.size(); m = T.size();
        int len = n+1;
        
        int cnt1[60] = {0};
        int cnt2[60] = {0};
        for (int i=0; i<m; ++i) {
            cnt2[getid(T[i])]++;
        }
        
        int begin, end;
        int i, j;
        for (i=j=0; i<n; ) {  // current substring is [i..j) from i to j-1
            while (j<n && !valid(cnt1, cnt2, 52)) {
                cnt1[getid(S[j])]++;
                j++;
            }
            if (!valid(cnt1, cnt2, 52)) break;            
            // [i..j-1] is valid
            while (valid(cnt1, cnt2, 52)) {
                cnt1[getid(S[i])]--;
                i++;
            }
            // [i-1..j-1] is valid
            int curr = j-i+1;
            if (curr < len) {
                len = curr;
                begin = i-1;
                end = j;
            }
        }
        if (len > n) return "";
        else return S.substr(begin, end-begin);
    }
};