/**
* rotate-image.cpp
* https://oj.leetcode.com/problems/rotate-image/
*
*/
class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        // the key is to observe that we can first do the outermost layer,
        // then do inner layer
        // and each layer is independent and can recurse
        // (0,0) to (0,n-1) to (n-1,n-1) to (n-1,0)
        // (0,1) to (1,n-1) to (n-1,n-2) to (n-2,0)
        // ...
        // (0,n-2) to (n-2,n-1) to (n-1,1) to (1,0)
        int n = matrix.size();
        for (int i = 0, len = n; i < n/2; ++i, len -= 2) {
            process(matrix, i, len);
        }
    }

    void process(vector<vector<int> > &matrix, int offset, int n) {
        for (int j = 0; j < n-1; ++j) {
            int r[4], c[4];
            r[0] = 0; c[0] = j;
            r[1] = j; c[1] = n-1;
            r[2] = n-1; c[2] = n-1-j;
            r[3] = n-1-j; c[3] = 0;
            swap(matrix, offset, r, c);
        }
    }

    void swap(vector<vector<int> > &matrix, int offset, int row[], int col[]) {
        int r, c, r2, c2;
        r = offset + row[3]; c = offset + col[3];
        int tmp = matrix[r][c];
        for (int x = 2; x >= 0; --x) {
            r = offset + row[x]; c = offset + col[x];
            r2 = offset + row[x+1], c2 = offset + col[x+1];
            matrix[r2][c2] = matrix[r][c];
        }
        r = offset + row[0]; c = offset + col[0];
        matrix[r][c] = tmp;
    }
};
