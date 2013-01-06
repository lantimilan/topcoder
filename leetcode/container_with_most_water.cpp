class Solution {
public:
    int maxArea(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        typedef pair<int,int> pii; // height, pos
        vector<pii> left, right;
        int ans = 0;

        // for each col, need to find rightmost bar with h>=hcol
        for(int i=0; i<height.size(); ++i) {
            if (left.empty() || height[i] > left.back().first)
                left.push_back(pii(height[i], i));
        }
        for(int i=height.size()-1; i>=0; --i) {
            if (right.empty() || height[i] > right.back().first)
                right.push_back(pii(height[i], i));
        }
        int i, j;
        for(i=0, j=0; i < left.size() && j < right.size(); ) {
            int curr;
            int width = right[j].second - left[i].second;
            if (width <= 0) break;
            if (left[i].first <= right[j].first) {
                curr = left[i].first * width;
                ++i;
            } else {
                curr = right[j].first * width;
                ++j;
            }
            ans = max(curr, ans);
        }
        return ans;
    }
};