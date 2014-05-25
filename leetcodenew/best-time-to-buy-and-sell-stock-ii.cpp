/**
* best-time-to-buy-and-sell-stock-ii.cpp
* https://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
*
*/
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        int profit = 0;
        int low, high;
        for (low = 0; low < n; low = high+1) {
            while (low + 1 < n && prices[low+1] < prices[low]) low++;
            if (low + 1 >= n) break;
            for (high = low + 1; high < n; ++high)
                if (high+1 < n && prices[high] >= prices[high+1])
                    break;
            if (high >= n) high = n-1;
            if (low < high) profit += prices[high] - prices[low];
        }
        return profit;
    }
};
