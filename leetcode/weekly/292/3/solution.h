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

class Solution {
   public:
    bool hasValidPath(vector<vector<char>>& g) {
        int n = g.size();
        int m = g[0].size();
        typedef pair<int, int> pii;
        typedef pair<pii, int> piii;
        queue<piii> Q;
        set<piii> vis;
        if (g[0][0] == ')') {
            return false;
        }
        Q.push({{0, 0}, 1});
        vis.insert({{0, 0}, 1});
        int d[4][2] = {1, 0, 0, 1};

        while (!Q.empty()) {
            auto it = Q.front();
            Q.pop();

            if (it.first.first == n - 1 && it.first.second == m - 1 && it.second == 0) {
                return true;
            }
            int x = it.first.first, y = it.first.second;
            int val = it.second;

            int can_go = (n - 1 - x) + (m - 1 - y);
            if (val % 2 != can_go % 2) continue;
            if (val > can_go) continue;

            for (int i = 0; i < 2; i++) {
                int x2 = x + d[i][0], y2 = y + d[i][1];
                if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m) {
                    char it = g[x2][y2];
                    int tmp = (it == '(' ? 1 : -1);
                    int nxt_val = val + tmp;
                    if (nxt_val >= 0) {
                        piii nxt = {{x2, y2}, nxt_val};
                        if (vis.count(nxt) == 0) {
                            vis.insert(nxt);
                            Q.push(nxt);
                        }
                    }
                }
            }
        }
        return false;
    }
};