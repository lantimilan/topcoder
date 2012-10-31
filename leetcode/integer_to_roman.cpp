class Solution {
public:
    string intToRoman(int num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function    
        string ans;
        if (num >= 1000) {
            int d = num / 1000;
            ans += string(d, 'M');
            num %= 1000;
        }
        if (num >= 100) {
            int d = num / 100;
            switch (d) {
                case 9: ans += "CM"; break;
                case 8: ans += "DCCC"; break;
                case 7: ans += "DCC"; break;
                case 6: ans += "DC"; break;
                case 5: ans += "D"; break;
                case 4: ans += "CD"; break;
                case 3: ans += "CCC"; break;
                case 2: ans += "CC"; break;
                case 1: ans += "C"; break;
            }
            num %= 100;
        }
        if (num >= 10) {
            int d = num / 10;
            switch (d) {
                case 9: ans += "XC"; break;
                case 8: ans += "LXXX"; break;
                case 7: ans += "LXX"; break;
                case 6: ans += "LX"; break;
                case 5: ans += "L"; break;
                case 4: ans += "XL"; break;
                case 3: ans += "XXX"; break;
                case 2: ans += "XX"; break;
                case 1: ans += "X"; break;
            }
            num %= 10;
        }
        if (num > 0) {
            int d = num;
            switch (d) {
                case 9: ans += "IX"; break;
                case 8: ans += "VIII"; break;
                case 7: ans += "VII"; break;
                case 6: ans += "VI"; break;
                case 5: ans += "V"; break;
                case 4: ans += "IV"; break;
                case 3: ans += "III"; break;
                case 2: ans += "II"; break;
                case 1: ans += "I"; break;
            }
        }
        return ans;
    }
};