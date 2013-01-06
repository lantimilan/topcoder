class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function        
        int n, m, i, j;        
        if (matrix.empty()) return false;
        n = matrix.size(); m = matrix[0].size();
        
        i=0; j=m-1;
        while (i < n && j >= 0) {
            if (matrix[i][j] == target) return true;
            else if (matrix[i][j] < target) i++;
            else j--;
        }
        return false;
    }
};