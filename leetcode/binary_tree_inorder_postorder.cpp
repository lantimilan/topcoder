/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *buildHelp(vector<int>::iterator in1, vector<int>::iterator in2,
        vector<int>::iterator post1, vector<int>::iterator post2)
        {
            if (in1 == in2) return NULL;
            int last = *--post2;
            vector<int>::iterator in_end, post_end;
            for(in_end = in1; in_end != in2 && *in_end != last; ++in_end)
                ;
            vector<int>::iterator it1, it2;
            for(it1 = in1, it2 = post1; it1 != in_end; ++it1, ++it2)
                ;
            TreeNode *left, *right;
            left = buildHelp(in1, in_end, post1, it2);
            right = buildHelp(++in_end, in2, it2, post2);
            
            TreeNode *root = new TreeNode(last);
            root->left = left;
            root->right = right;
            return root;
        }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return buildHelp(inorder.begin(), inorder.end(),
            postorder.begin(), postorder.end());
    }
};