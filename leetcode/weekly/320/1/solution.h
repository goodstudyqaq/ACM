/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        vector<int> V;
        function<void(TreeNode*)> dfs = [&](TreeNode* now) {
            V.push_back(now->val);
            if (now->left != NULL) {
                dfs(now->left);
            }
            if (now->right != NULL) {
                dfs(now->right);
            }
        };
        dfs(root);
        sort(V.begin(), V.end());

        int m = queries.size();
        vector<vector<int>> ans(m);
        for (int i = 0; i < m; i++) {
            int val = queries[i];
            int a = -1, b = -1;

            auto it = lower_bound(V.begin(), V.end(), val);

            if (it != V.end()) {
                b = *it;
            }
            if (it != V.end() && *it == val) {
                a = *it;
            } else if (it != V.begin()) {
                it--;
                a = *it;
            }
            ans[i] = {a, b};
        }
        return ans;
    }
};