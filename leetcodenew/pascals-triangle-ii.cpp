/**
* pascals-triangle-ii.cpp
* https://oj.leetcode.com/problems/pascals-triangle-ii/
*/
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> first(1,1);
        vector<int> second;
        if (rowIndex == 0) return first;
        for (int row = 1; row <= rowIndex; ++row) {
            second.resize(row+1);
            second[0] = second[second.size()-1] = 1;
            for (int j = 1; j < row; ++j) {
                second[j] = first[j-1] + first[j];
            }
            first = second;
        }
        return first;
    }
};
