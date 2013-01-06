class Solution {
public:
    int jump(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int pos, next;
        int cnt;
        pos = next = 0;
        cnt = 0;
        // current region is [pos, next]
        while (next < n-1) {
            cnt++;
            int hop = 0;
            for (int x=pos; x <= next; ++x)
                hop = max(hop, x + A[x]);
            pos = next;
            next = hop;
        }
        return cnt;
    }
};