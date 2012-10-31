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
    typedef vector<int>::iterator ittype;
    TreeNode *buildHelp(ittype pre1, ittype pre2, ittype in1, ittype in2)
    {
        if (pre1 == pre2) return NULL;
        int top = *pre1;
        ittype pre_split, in_split;
        for(in_split = in1; in_split != in2 && *in_split != top; ++in_split)
            ;
        ++pre1;
        ittype it1, it2;        
        for(it1=in1, it2=pre1; it1!=in_split; ++it1, ++it2)
            ;
        pre_split = it2;
        TreeNode *left, *right;        
        left = buildHelp(pre1, pre_split, in1, in_split);
        right = buildHelp(pre_split, pre2, ++in_split, in2);
        
        TreeNode *root = new TreeNode(top);
        root->left = left;
        root->right = right;
        return root;
    }
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return buildHelp(preorder.begin(), preorder.end(),
            inorder.begin(), inorder.end());
    }
};