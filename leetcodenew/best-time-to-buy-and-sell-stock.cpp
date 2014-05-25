/**
* best-time-to-buy-and-sell-stock.cpp
* https://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock/
*
*/
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        if (prices.empty()) return 0;
        // for each i, need to know max in [i+1..n-1]
        // best[i] = j if j > i and prices[j] is max in [i+1..n-1]
        int n = prices.size();
        vector<int> best(n, -1);
        // best[i] is either best[i+1] or i+1
        for (int i = n-2; i >= 0; --i) {
            if (best[i+1] >= 0) best[i] = best[i+1];
            if (best[i] < 0 || prices[best[i]] < prices[i+1]) best[i] = i+1;
        }
        int profit = 0;
        for (int i = 0; i < n-1; ++i) {
            profit = max(profit, prices[best[i]] - prices[i]);
        }
        return profit;
    }
};
