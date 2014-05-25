/**
* candy.cpp
* https://oj.leetcode.com/problems/candy/
*/
class Solution {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();
        vector<int> candies(n, 0);
        vector<pair<int,int> > children(n);  // rating, pos
        for (int i = 0; i < n; ++i) children[i] = make_pair(ratings[i], i);
        sort(children.begin(), children.end());
        for (int i = 0; i < children.size(); ++i) {
            int pos = children[i].second;
            int left = 0; if (pos > 0 && ratings[pos] > ratings[pos-1]) left = candies[pos-1];
            int right = 0; if (pos+1 < n && ratings[pos] > ratings[pos+1]) right = candies[pos+1];
            candies[pos] = max(left, right) + 1;
        }
        int total = 0;
        for (int i = 0; i < n; ++i) total += candies[i];
        return total;
    }
};
