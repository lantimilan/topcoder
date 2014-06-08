/**
* text-justification.cpp
* https://oj.leetcode.com/problems/text-justification/
*
*
*/
class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        vector<string> text;
        int i, j;
        for (i = 0; i < words.size(); i = j) {
            int len = words[i].length();
            for (j = i+1; j < words.size(); ++j) {
                len += 1 + words[j].length();
                if (len > L) break;
            }
            // words[i..j-1] are in current line
            len = 0;
            for (int k = i; k < j; ++k) len += words[k].length();
            int space = L - len;
            int gap = j - i - 1;
            if (gap == 0) { text.push_back(words[i] + string(space, ' ')); continue; }
            if (j >= words.size()) {  // last line
                string line = words[i];
                for (int k = i+1; k < j; ++k) { line += " " + words[k]; --space; }
                text.push_back(line + string(space, ' ')); continue;
            }
            int q = space / gap;
            int rem = space % gap;
            string line = words[i];
            for (int k = 1; k <= gap; ++k) {
                int pre = q; if (k <= rem) pre++;
                line += string(pre, ' ') + words[i+k];
            }
            text.push_back(line);
        }
        return text;
    }
};
