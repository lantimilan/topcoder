class Solution {
public:
    string countAndSay(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        string str = "1";
        for(int i=1; i<n; ++i) {
            string next;
            char buf[8096] = {0};
            char ch = str[0];
            int cnt=1;
            for(int p=1; p<str.size(); p++) {
                if (str[p] == ch) cnt++;
                else {                    
                    sprintf(buf+strlen(buf), "%d", cnt);
                    buf[strlen(buf)] = ch;
                    ch = str[p];
                    cnt = 1;                    
                }
            }
            sprintf(buf+strlen(buf), "%d", cnt);
            buf[strlen(buf)] = ch;
            str = buf;
        }
        return str;
    }
};