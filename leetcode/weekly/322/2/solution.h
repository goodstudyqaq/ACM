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

typedef pair<int, int> pii;
class Solution {
   public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pii>> V(n + 1);

        int m = roads.size();
        for (int i = 0; i < m; i++) {
            int u = roads[i][0], v = roads[i][1], w = roads[i][2];
            V[u].push_back({v, w});
            V[v].push_back({u, w});
        }

        int ans = numeric_limits<int>::max() / 2;

        queue<int> Q;
        vector<bool> vis(n + 1);
        Q.push(1);
        vis[1] = 1;

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (auto [v, w] : V[u]) {
                ans = min(ans, w);
                if (vis[v] == 0) {
                    vis[v] = 1;
                    Q.push(v);
                }
            }
        }
        return ans;
    }
};