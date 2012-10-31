class Solution {
public:
    
    bool canJump(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function        
        int end = 0;
        for (int i=0; i<=end; ++i) {
            end = max(end, i+A[i]);
            if (end >= n-1) return true;
        }
        return false;
    }
};