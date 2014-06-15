vector<vector<int> > range_min;
class Solution {
public:
    // observation: let s[i..j] be a valid parenthesis segment, then lcnt[j] = lcnt[i-1]
    // this is not enough, lcnt cannot go down during this segment
    // check each pair and range minimum, O(n^3), likely TLE
    int longestValidParentheses(string s) {
        map<int, vector<int> > lcnt_map;  // lcnt, (first, last)
        vector<int> lcnt_vec(s.size());
        int lcnt = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') lcnt++;
            else lcnt--;
            lcnt_vec[i] = lcnt;
            if (lcnt_map.count(lcnt)) {
                lcnt_map[lcnt].push_back(i);
            } else {
                lcnt_map[lcnt] = vector<int>(1, i);
            }
        }
        int n = s.size();
        //vector<vector<int> > range_min(n, vector<int>(n)); // MLE
        range_min.resize(n);
        for (int i = 0; i < n; ++i) range_min[i].resize(n-i+1);  // to address range_min[i][n], you need to allocate n+1

        for (int i = 0; i < n; ++i) range_min[i][1] = lcnt_vec[i];

        for (int len = 2; len <= n; ++len)
        for (int i = 0; i + len <= n; ++i) {
            int j = i+len-1;
            range_min[i][len] = min(range_min[i][len-1], lcnt_vec[j]);
        }

        int maxlen = 0;
        map<int, vector<int> >::const_iterator it;
        for (it = lcnt_map.begin(); it != lcnt_map.end(); ++it) {
            vector<int> vec = it->second;
            for (int i = 0; i < vec.size(); ++i)
            for (int j = i+1; j < vec.size(); ++j) {
                int start = vec[i], end = vec[j];
                int mincnt = range_min[start][end-start+1];
                /*
                int mincnt = it->first;
                for (int k = start; k <= end; ++k) {
                    mincnt = min(mincnt, lcnt_vec[k]);
                }*/
                if (mincnt == it->first) {
                    int len = end - start + 1;
                    maxlen = max(maxlen, len);
                }
            }
        }
        return maxlen;
    }
};

// O(n^2) also TLE
// looks need a O(n) algorithm
