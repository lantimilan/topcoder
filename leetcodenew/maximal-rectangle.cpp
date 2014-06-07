class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int> > height(n, vector<int>(m));
        for (int j = 0; j < m; ++j) height[0][j] = (matrix[0][j] == '1');
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (matrix[i][j] == '1') height[i][j] = 1 + height[i-1][j];
        int maxRect = 0;
        for (int i = 0; i < n; ++i) {  // maximum area histogram for each row
            stack<int> st;  // st keeps a list of increasing columns, equal height columns only keep rightmost one
            for (int j = 0; j < m; ++j) {
                while (!st.empty()) {  // pop higher columns because we know their right edge now
                    int htop = height[i][st.top()];
                    if (htop < height[i][j]) break;
                    st.pop();
                    int left, right = j;
                    if (!st.empty()) left = st.top() + 1;
                    else left = 0;
                    int area = htop * (right - left);
                    chmax(maxRect, area);
                }
                st.push(j);
            }
            // now count all st element to extend to right edge of matrix
            int end = m;
            while (!st.empty()) {
                int pos = st.top(); st.pop();
                int start;
                if (!st.empty()) start = st.top() + 1;
                else start = 0;
                int h = height[i][pos];
                int area = (end - start) * h;
                chmax(maxRect, area);
            }
        }
        return maxRect;
    }
    void chmax(int &a, int b) {
        if (a < b) a = b;
    }
};
