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
    TreeNode *arrayBST(vector<int>::iterator it1, vector<int>::iterator it2)
    {
        if (it1 == it2) return NULL;
        int n = it2-it1;
        vector<int>::iterator mid = it1 + n/2;
        int val = *mid;
        TreeNode *left, *right;
        left = arrayBST(it1, mid);
        right = arrayBST(++mid, it2);
        TreeNode *root = new TreeNode(val);
        root->left = left;
        root->right = right;
        return root;
    }
    TreeNode *sortedArrayToBST(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return arrayBST(num.begin(), num.end());
    }
};