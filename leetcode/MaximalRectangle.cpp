// use maximum area histogram O(n) algorithm for each row
//
class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (matrix.empty() || matrix[0].empty())
            return 0;
        int n, m;
        n = matrix.size(); m = matrix[0].size();
        vector<vector<int> > height(n+1, vector<int>(m+1));
        
        // height[i][j]
        for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
        if (matrix[i-1][j-1] == '1')
        {
            height[i][j] = height[i-1][j] + 1;
        }
        
        int ans = 0;
        // max histogram
        for(int i=1; i<=n; ++i)
        {
            vector<pair<int,int> > st; // height, pos            
            for(int j=1; j<=m; ++j)
            {
                int h = height[i][j];
                while(!st.empty() && h <= st.back().first) {
                    int h2 = st.back().first;
                    int pos = j-1;
                    st.pop_back();
                    if (st.empty()) {
                        int curr = h2*pos;
                        ans = max(ans, curr);
                    } else {                        
                        int plast = st.back().second;
                        int curr = h2*(pos-plast);
                        ans = max(ans, curr);
                    }                    
                }
                st.push_back(make_pair(h, j));
            }
            for(int x=0; x<(int)st.size(); ++x) {
                int h = st[x].first;
                int p;
                int curr;
                if (x==0) p=0;
                else p = st[x-1].second;
                curr = h * (m-p);
                ans = max(ans, curr);
            }
        }
        return ans;
    }
};
