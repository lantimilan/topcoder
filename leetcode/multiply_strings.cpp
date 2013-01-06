class Solution {
public:
    vector<int> add(const vector<int> &v1, const vector<int> &v2)
    {
        int n1, n2;
        vector<int> ans;
        
        n1 = v1.size(); n2 = v2.size();        
        int carry = 0;
        for (int i=0; i<n1 || i<n2; ++i) {
            int sum = carry;
            if (i<n1) sum += v1[i];
            if (i<n2) sum += v2[i];
            carry = sum / 10;
            ans.push_back(sum % 10);
        }
        if (carry) ans.push_back(carry);
        return ans;
    }
    
    vector<int> mult(const vector<int> &v1, const vector<int> &v2) {
        vector<int> ans;
        for (int i=0; i<v1.size(); ++i) {
            vector<int> row(i, 0);  // padding 0 as shift to higher bits
            int carry = 0;
            for (int j=0; j<v2.size(); ++j) {
                int prod = v1[i] * v2[j] + carry;
                carry = prod / 10;
                row.push_back(prod % 10);
            }
            if (carry) row.push_back(carry);            
            ans = add(ans, row);
        }
        return ans;
    }
    
    string multiply(string num1, string num2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        string ans;
        vector<int> v1, v2, v3;
        for (int i=0; i<num1.size(); ++i)
            v1.push_back(num1[i]-'0');
        for (int i=0; i<num2.size(); ++i)
            v2.push_back(num2[i]-'0');
        reverse(v1.begin(), v1.end());
        reverse(v2.begin(), v2.end());
        
        v3 = mult(v1, v2);
        while (!v3.empty() && v3.back() == 0) // remove trailing zero
            v3.pop_back();
        if (v3.empty()) v3.push_back(0);
        reverse(v3.begin(), v3.end());
        ans = string(v3.size(), ' ');
        for (int i=0; i<v3.size(); ++i)
            ans[i] = char(v3[i] + '0');
        return ans;
    }
};