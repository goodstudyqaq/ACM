/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

typedef array<array<int, 2>, 2> a4;

class Solution {
   public:
    a4 dfs(TreeNode* now) {
        int inf = 1e9;
        a4 res = a4{{{{inf, inf}}, {{inf, inf}}}};
        if (now == NULL) {
            res[0][0] = res[0][1] = res[1][0] = res[1][1] = 0;
            return res;
        }
        auto lval = dfs(now->left);
        auto rval = dfs(now->right);

        // 1 -> v1 ^ 1
        // 2 -> v1 ^ 1, 两个 ^ 1
        // 3 -> v1 ^ 1, 第一个 ^ 1
        int v1 = now->val;
        for (int i = 0; i < 2; i++) {
            // 不用
            res[v1][i] = min(res[v1][i], lval[i][i] + rval[i][i]);
            // 1
            res[v1 ^ 1][i] = min(res[v1 ^ 1][i], lval[i][i] + rval[i][i] + 1);
            // 2
            res[v1 ^ 1][i] = min(res[v1 ^ 1][i], lval[i ^ 1][i ^ 1] + rval[i ^ 1][i ^ 1] + 1);
            // 3
            res[v1 ^ 1][i] = min(res[v1 ^ 1][i], lval[i ^ 1][i] + rval[i ^ 1][i] + 1);
            // 1 2
            res[v1][i] = min(res[v1][i], 2 + lval[i ^ 1][i ^ 1] + rval[i ^ 1][i ^ 1]);
            // 1 3
            res[v1][i] = min(res[v1][i], 2 + lval[i ^ 1][i] + rval[i ^ 1][i]);
            // 2 3
            res[v1][i] = min(res[v1][i], 2 + lval[i][i ^ 1] + rval[i][i ^ 1]);
            // 1 2 3
            res[v1 ^ 1][i] = min(res[v1 ^ 1][i], 3 + lval[i][i ^ 1] + rval[i][i ^ 1]);
        }
        return res;
    }

    int closeLampInTree(TreeNode* root) {
        a4 res = dfs(root);
        return res[0][0];
    }
};