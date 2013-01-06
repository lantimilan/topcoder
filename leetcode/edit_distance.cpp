class Solution {
public:
    vector<vector<int> > dp;
    int calc(const string &w1, const string w2, int l1, int l2)
    {
        int n1, n2;
        n1 = w1.size(); n2 = w2.size();
        if (l1>=n1) return n2-l2;
        if (l2>=n2) return n1-l1;
        
        if (dp[l1][l2] >= 0) return dp[l1][l2];
        int s1, s2, s3;
        s1 = calc(w1, w2, l1+1, l2);
        s2 = calc(w1, w2, l1, l2+1);
        s3 = calc(w1, w2, l1+1, l2+1);
        if (w1[l1] != w2[l2]) s3++;
        int ans = min(s1, s2) + 1;
        ans = min(ans, s3);
        
        return dp[l1][l2] = ans;
    }
    int minDistance(string word1, string word2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n1, n2;
        n1 = word1.size(); n2 = word2.size();
        dp.clear();
        dp.resize(n1);
        for(int i=0; i<n1; ++i)
            dp[i] = vector<int>(n2, -1);
        return calc(word1, word2, 0, 0);
    }
};