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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
}
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

typedef pair<long long, int> pli;
struct Result {
    unordered_map<int, pli> M;
    unordered_set<int> pending;

    void merge(Result &b) {
        assert(M.size() >= b.M.size());

        for (auto it : b.M) {
            int dep = it.first;
            M[dep].first += it.second.first;
            M[dep].second += it.second.second;
            pending.insert(dep);
        }
        for (auto it : b.pending) {
            pending.insert(it);
        }
    }
};

class Solution {
   public:
    vector<int> cnt;
    vector<long long> sum;
    long long ans;
    int getMaxLayerSum(TreeNode *root) {
        function<void(TreeNode *, int)> dfs = [&](TreeNode *u, int d) {
            if (cnt.size() <= d) {
                cnt.push_back(0);
                sum.push_back(0);
            }
            cnt[d]++;
            sum[d] += u->val;

            if (u->left != NULL) {
                dfs(u->left, d + 1);
            }
            if (u->right != NULL) {
                dfs(u->right, d + 1);
            }
        };

        function<Result(TreeNode *, int)> dfs2 = [&](TreeNode *u, int d) -> Result {
            if (u->left == NULL && u->right == NULL) {
                Result res;
                res.M[d] = {-u->val, -1};
                if (cnt[d] - 1 > 0) {
                    ans = max(ans, sum[d] - u->val);
                }
                return res;
            } else if ((u->left == NULL) + (u->right == NULL) == 1) {
                TreeNode *nxt = (u->left == NULL ? u->right : u->left);
                Result res = dfs2(nxt, d + 1);
                for (auto p : res.pending) {
                    auto it = res.M[p];
                    if (it.second + cnt[p] > 0) {
                        ans = max(ans, it.first + sum[p]);
                    }
                }
                res.M[d] = {nxt->val - u->val, 0};
                ans = max(ans, sum[d] + res.M[d].first);
                res.pending.clear();
                return res;
            } else {
                Result res1 = dfs2(u->left, d + 1);
                Result res2 = dfs2(u->right, d + 1);
                if (res1.M.size() < res2.M.size()) {
                    swap(res1, res2);
                }
                res1.merge(res2);
                res1.M[d] = {u->left->val + u->right->val - u->val, 1};
                res1.pending.insert(d);
                return res1;
            }
        };
        cnt.clear();
        sum.clear();

        dfs(root, 0);
        ans = sum[0];
        for (auto it : sum) {
            ans = max(ans, it);
        }
        dfs2(root, 0);
        return ans;
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    typedef pair<long long, int> pli;
    vector<long long> sm;
    vector<int> sz;
    long long ans;

    // 先计算每个点的深度，以及统计每一层原有的和
    void dfs1(TreeNode *node, int d) {
        if (node == nullptr) return;
        if (sm.size() <= d) sm.push_back(0), sz.push_back(0);
        sm[d] += node->val;
        sz[d]++;
        dfs1(node->left, d + 1);
        dfs1(node->right, d + 1);
    }

    struct Result {
        // mp[d].first 表示深度 d 的变化值，mp[d].second 表示深度 d 的节点变化数量
        unordered_map<int, pli> mp;
        // 哪些深度的答案有待计入答案
        unordered_set<int> pending;

        // 合并两个 Result，为了保证复杂度正确，mp.size() >= r.mp.size() 必须成立
        void merge(Result &r) {
            for (auto it = r.mp.begin(); it != r.mp.end(); it++) {
                auto &p = mp[it->first];
                p.first += it->second.first;
                p.second += it->second.second;
                // 深度 it->first 的结果更新了，等待计入答案
                pending.insert(it->first);
            }
            for (int x : r.pending) pending.insert(x);
        }
    };

    Result dfs2(TreeNode *node, int d) {
        if (node->left == nullptr && node->right == nullptr) {
            // 叶子节点
            Result ret;
            if (sz[d] > 1) {
                // 删掉这个叶子节点不会掏空这一层，允许统计答案
                ans = max(ans, sm[d] - node->val);
                ret.mp[d] = pli(-node->val, -1);
            }
            return ret;
        } else if (node->left != nullptr && node->right != nullptr) {
            // 两个子节点
            Result a = dfs2(node->left, d + 1);
            Result b = dfs2(node->right, d + 1);
            if (a.mp.size() < b.mp.size()) swap(a, b);
            a.merge(b);

            // 自己这层的变化量也要算
            a.mp[d] = pli(node->left->val + node->right->val - node->val, 1);
            // 不能马上计算答案（因为这个点有两个子节点，不能删掉），先记下来
            a.pending.insert(d);
            return a;
        } else {
            // 只有一个子节点
            TreeNode *ch = node->left == nullptr ? node->right : node->left;
            Result ret = dfs2(ch, d + 1);
            // 删掉这个子节点，开始统计所有受影响的层的答案
            for (int x : ret.pending) {
                pli p = ret.mp[x];
                // 深度 x 的变化不能导致深度 x 整层被掏空
                if (sz[x] + p.second > 0) ans = max(ans, sm[x] + p.first);
            }
            ret.pending.clear();

            // 自己这层的变化量也要算
            long long delta = ch->val - node->val;
            ans = max(ans, sm[d] + delta);
            ret.mp[d] = pli(delta, 0);
            return ret;
        }
    }

   public:
    int getMaxLayerSum(TreeNode *root) {
        dfs1(root, 0);
        ans = sm[0];
        for (long long x : sm) ans = max(ans, x);
        dfs2(root, 0);
        return ans;
    }
};
