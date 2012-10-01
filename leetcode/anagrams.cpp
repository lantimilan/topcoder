class Solution {
 public:
    vector<string> anagrams(vector<string> &strs) {
        vector<string> ans;
        map<string, vector<string> > mp;
        for(int i=0; i<(int)strs.size(); ++i) {
            string key = strs[i];
            sort(key.begin(), key.end());
            mp[key].push_back(strs[i]);
        }
        for(map<string, vector<string> >::iterator it=mp.begin(); it != mp.end(); ++it) {
            if (it->second.size() > 1) {
                for(int x=0; x<it->second.size(); ++x)
                    ans.push_back(it->second[x]);
            }
        }
        return ans;
    }
};

// Accepted
