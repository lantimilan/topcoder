class Solution {
public:
    int longestValidParentheses(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        // every rparen has a unique matched lparen
        typedef pair<int,int> pii;  // paren, pos
        int ans = 0;
        
        stack<int> st;  // lparen pos
        vector<pii> pre;  // all maximual matched parens
        for (int i=0; i<s.size(); ++i) {
            if (s[i] == '(') st.push(i);
            else {
                if (!st.empty()) {
                    int pos = st.top();                   
                    st.pop();
                    
                    while (!pre.empty() && 
                        pos < pre.back().first && pre.back().second < i) 
                    {
                        pre.pop_back();                    
                    }
                    pre.push_back(pii(pos, i));                    
                }
            }
        }
        vector<pii> merge;  // merge consecutive pairs
        if (pre.empty()) return 0;
        merge.push_back(pre[0]);
        for (int i=1; i<pre.size(); ++i) {            
            if (merge.back().second + 1 == pre[i].first)
                merge.back().second = pre[i].second;
            else
                merge.push_back(pre[i]);
        }
        
        for (int i=0; i<merge.size(); ++i) {
            ans = max(ans, merge[i].second - merge[i].first +1);
        }
        return ans;
    }
};
