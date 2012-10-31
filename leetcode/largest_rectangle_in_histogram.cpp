class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        typedef pair<int,int> pii;  // height, pos
        if (height.empty()) return 0;
        int ans = 0;
        stack<pii> st;
        for (int i=0; i<height.size(); ++i) {
            int h = height[i];
            while (!st.empty() && h <= st.top().first) {  // kill all higher columns
                int h2 = st.top().first;
                int p2 = st.top().second;
                st.pop();
                int l, r;
                r = i;
                if (!st.empty()) { l = st.top().second+1; }
                else l = 0;  // extend to the first column
                int area = h2 * (r-l);
                ans = max(ans, area);
            }
            st.push(pii(h, i));
        }
        
        while (!st.empty()) { // last column must be height[n-1]
            int h;
            h = st.top().first; st.pop();
            int l, r;
            r = height.size();
            if (!st.empty()) l = st.top().second + 1;
            else l = 0;  // extend to first column
            int area = h * (r-l);
            ans = max(ans, area);
        }
        return ans;
    }
};