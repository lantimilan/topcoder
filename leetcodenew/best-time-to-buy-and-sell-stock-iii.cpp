/**
 * profit1[i] is the best profit using only a[0..i], in particular profit1[n] = profit1[n-1]
 * profit2[i] is the best profit using only a[i..n-1], in particular profit2[n] = 0
 * 
 * base case: profit1[0] = 0
 * profit1[i] = profit1[i-1] or prices[i] - {minprice in [0..i-1]}
 * 
 * base case: profit2[n-1] = 0
 * profit2[i] = profit2[i+1] or {maxprice in [i+1..n-1]} - prices[i]
 * 
 * solution is max profit1[s] + profit2[s+1] for s = 0 to n-1 (we use profit2[n] when s = n-1)
 */
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        if (prices.empty()) return 0;
        int n = prices.size();
        vector<int> profit1(n+1, 0), profit2(n+1, 0);
        int minprice = prices[0];
        for (int i = 1; i < n; ++i) {
            int cur = prices[i] - minprice;
            profit1[i] = max(profit1[i-1], cur);
            minprice = min(minprice, prices[i]);
        }
        int maxprice = prices[n-1];
        for (int i = n-2; i >= 0; --i) {
            int cur = maxprice - prices[i];
            profit2[i] = max(profit2[i+1], cur);
            maxprice = max(maxprice, prices[i]);
        }
        int ans = 0;
        for (int s = 0; s < n; ++s) {
            int cur = profit1[s] + profit2[s+1];
            ans = max(ans, cur);
        }
        return ans;
    }
};
