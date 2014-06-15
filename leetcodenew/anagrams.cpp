/**
* anagrams.cpp
* https://oj.leetcode.com/problems/anagrams/
*
*/
class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        vector<string> ans;
        if (strs.size() <= 1) return ans;
        map<string, vector<string> > anagrams;
        for (int i = 0; i < strs.size(); ++i) {
            string s = strs[i]; sort(s.begin(), s.end());
            anagrams[s].push_back(strs[i]);
        }
        map<string, vector<string> >::const_iterator it;
        for (it = anagrams.begin(); it != anagrams.end(); ++it) {
            const vector<string> &vec = it->second;
            if (vec.size() > 1) {
                for (int k = 0; k < vec.size(); ++k)
                    ans.push_back(vec[k]);
            }
        }
        return ans;
    }
};
