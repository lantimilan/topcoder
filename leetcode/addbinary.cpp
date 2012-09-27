class Solution {
 public:
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int la, lb;
        la = a.size();
        lb = b.size();
        string c(max(la, lb)+1, '0');
        int carry=0;
        for(int i=0; i<la+1 || i<lb+1; ++i) {
            int sum = carry;
            if (i<la) sum += (a[i]-'0');
            if (i<lb) sum += (b[i]-'0');
            carry = sum>>1;
            sum = sum&1;
            c[i] = char(sum + '0');
        }
        if (c[c.size()-1] == '0')
            c = c.substr(0, c.size()-1);
        reverse(c.begin(), c.end());
        return c;
    }
};
