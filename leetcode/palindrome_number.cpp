class Solution {
public:
    bool isPalindrome(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (x < 0) return false;
        int t = x;
        int y = 0;
        while (t) {
            y = y*10 + t % 10;
            t /= 10;
        }
        return x == y;
    }
};

// this one has integer overflow
// although it is Accepted
