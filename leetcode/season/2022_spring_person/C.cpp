#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
   public:
    int getNumber(TreeNode* root, vector<vector<int>>& ops) {
        set<int> V;
        function<void(TreeNode*)> dfs = [&](TreeNode* now) -> void {
            V.insert(now->val);
            if (now->left != NULL) {
                dfs(now->left);
            }
            if (now->right != NULL) {
                dfs(now->right);
            }
        };
        dfs(root);
        int n = ops.size();

        int res = 0;
        for (int i = n - 1; i >= 0; i--) {
            int t = ops[i][0], l = ops[i][1], r = ops[i][2];
            auto it1 = V.lower_bound(l);
            auto it2 = V.lower_bound(r + 1);
            while (it1 != it2) {
                if (t == 1) {
                    res++;
                }
                V.erase(it1++);
            }
        }
        return res;
    }
};

int main() {
}