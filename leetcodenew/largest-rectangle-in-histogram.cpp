/**
* largest-rectangle-in-histogram.cpp
* https://oj.leetcode.com/problems/largest-rectangle-in-histogram/
*
*/
class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        int maxRect = 0;
        stack<int> st;  // a list with increasing height, keep only rightmost column for equal height
        for (int i = 0; i < height.size(); ++i) {
            int h = height[i];
            while (!st.empty()) {
                int htop = height[st.top()];
                if (htop < h) break;
                // pop st to get histogram
                st.pop();
                int left, right = i;
                if (!st.empty()) left = st.top() + 1;
                else left = 0;
                int area = htop * (right - left);
                maxRect = max(maxRect, area);
            }
            st.push(i);
        }
        int end = height.size();
        while (!st.empty()) {
            int h = height[st.top()]; st.pop();
            int start;
            if (!st.empty()) start = st.top() + 1;
            else start = 0;
            int area = h * (end - start);
            maxRect = max(maxRect, area);
        }
        return maxRect;
    }
};
