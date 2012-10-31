class Solution {
public:
    vector<int> gray(int n)
    {
        if (n == 0) return vector<int>(1,0);
        vector<int> v1, v2;
        v1 = gray(n-1);
        v2 = rev(n-1);
        vector<int> ans = v1;
        for (int i=0; i<v2.size(); ++i) {
            ans.push_back(v2[i] | 1<<(n-1));
        }
        return ans;
    }
    vector<int> rev(int n)
    {
        if (n == 0) return vector<int>(1,0);
        vector<int> v1, v2;
        v1 = gray(n-1);
        v2 = rev(n-1);
        vector<int> ans;
        for (int i=0; i<v1.size(); ++i) {
            ans.push_back(v1[i] | 1<<(n-1));
        }
        for (int i=0; i<v2.size(); ++i) {
            ans.push_back(v2[i]);
        }
        return ans;
    }
    vector<int> grayCode(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return gray(n);
    }
};