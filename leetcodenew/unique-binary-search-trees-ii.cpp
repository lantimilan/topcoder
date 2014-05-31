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
    vector<TreeNode*> genTreeAtRoot(int start, int end, int rootval) {
        if (start >= end) return vector<TreeNode*>();
        vector<TreeNode*> leftVec = genTrees(start, rootval);
        vector<TreeNode*> rightVec = genTrees(rootval+1, end);

        vector<TreeNode*> nodes;
        if (leftVec.empty() && rightVec.empty()) {
            TreeNode *root = new TreeNode(rootval);
            nodes.push_back(root);
            return nodes;
        }
        if (leftVec.empty()) {
            for (int i = 0; i < rightVec.size(); ++i) {
                TreeNode *root = new TreeNode(rootval);
                root->right = rightVec[i];
                nodes.push_back(root);
            }
            return nodes;
        }
        if (rightVec.empty()) {
            for (int i = 0; i < leftVec.size(); ++i) {
                TreeNode *root = new TreeNode(rootval);
                root->left = leftVec[i];
                nodes.push_back(root);
            }
            return nodes;
        }
        // both vec not empty
        for (int i = 0; i < leftVec.size(); ++i) {
            for (int j = 0; j < rightVec.size(); ++j) {
                TreeNode *root = new TreeNode(rootval);
                root->left = leftVec[i]; root->right = rightVec[j];
                nodes.push_back(root);
            }
        }
        return nodes;
    }
    vector<TreeNode*> genTrees(int start, int end) {
        vector<TreeNode*> roots;
        for (int k = start; k < end; ++k) {
            vector<TreeNode*> cur = genTreeAtRoot(start, end, k);
            for (int i = 0; i < cur.size(); ++i) roots.push_back(cur[i]);
        }
        return roots;
    }
    vector<TreeNode *> generateTrees(int n) {
        vector<TreeNode *> ans; ans.push_back(NULL);  // this is hacky
        // use vector(1, NULL) does not work as the constructor will complain
        // and the special case n = 0 is required by OJ
        if (n == 0) return ans;
        return genTrees(1, n+1);
    }
};
