/**
* jump-game.cpp
* https://oj.leetcode.com/problems/jump-game/
*/
class Solution {
public:
    bool canJump(int A[], int n) {
        int maxdist = 0;
        for (int i = 0; i < n; ++i) {
            if (i > maxdist) break;
            int d = i + A[i];
            maxdist = max(d, maxdist);
        }
        return maxdist >= n-1;
    }
};
