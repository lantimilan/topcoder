class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (prices.empty()) return 0;
        typedef pair<int, int> pii; // price, pos
        deque<pii> maxp;
        maxp.push_back(pii(prices[0], 0));
        for(int i=1; i<prices.size(); ++i) {
            int p = prices[i];
            while(!maxp.empty() && p >= maxp.back().first)
                maxp.pop_back();
            maxp.push_back(pii(p, i));            
        }
        int ans = 0;
        for(int i=0; i<prices.size(); ++i) {
            if (i<maxp.front().second) {
                ans = max(ans, maxp.front().first - prices[i]);                
            } else {
                maxp.pop_front();
                if (maxp.empty()) break;
                ans = max(ans, maxp.front().first - prices[i]);
            }
        }
        return ans;
    }
};