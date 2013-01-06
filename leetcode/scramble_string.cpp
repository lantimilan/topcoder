class Solution {
public:
    map<pair<string,string>, bool> memo;
    bool isScramble(string s1, string s2) {
        memo.clear();
        return helper(s1, s2);
    }
    
    bool helper(string s1, string s2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s1.empty()) return true;
        if (s1.length() == 1) return s1[0] == s2[0];
        
        if (memo.find(make_pair(s1,s2)) != memo.end())
            return memo[make_pair(s1, s2)];
            
        int n = s1.length();
        string a1, b1, a2, b2;
        
        bool &ans = memo[make_pair(s1,s2)];
        ans = false;
        
        for (int i=1; i<n; ++i) {
        
        a1 = s1.substr(0, i);
        b1 = s1.substr(i);
        a2 = s2.substr(0, i);
        b2 = s2.substr(i);
        
        if (helper(a1, a2) && helper(b1, b2))
        {    ans = true; break; }
        
        // scramble s2
        a2 = s2.substr(n-i);
        b2 = s2.substr(0, n-i);
        if (helper(a1, a2) && helper(b1, b2))
        {    ans = true; break; }
        
        }
        
        return ans;
    }
};