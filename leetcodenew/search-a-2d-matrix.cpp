/**
* search-a-2d-matrix.cpp
* https://oj.leetcode.com/problems/search-a-2d-matrix/
*
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int n = matrix.size();
        int m = matrix[0].size();
        int lo = -1, hi = n*m;  // imagine two fictious element, A[-1] <= target and A[n*m] > target
        while (lo + 1 < hi) {  // A[lo] <= target and A[hi] > target
            int mid = (lo + hi) / 2;  // lo < mid < hi, therefore mid is valid and ensures progress, that is, either lo or hi is updated
            pair<int,int> p = indexToRowCol(mid, m);
            int val = matrix[p.first][p.second];
            if (val <= target) lo = mid;
            else hi = mid;
        }

        if (lo >= 0) {
            pair<int,int> p = indexToRowCol(lo, m);
            return matrix[p.first][p.second] == target;
        }
        return false;
    }

    pair<int,int> indexToRowCol(int index, int m) {
        int row = index / m;
        int col = index % m;
        return make_pair(row, col);
    }
};
