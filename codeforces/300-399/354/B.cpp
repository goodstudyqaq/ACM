#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

    int n;
    cin >> n;
    vector<string> s;
    s.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<vector<int>> mask;
    mask.resize(n * 2 - 1, vector<int>(26, 0));

    for (int i = 0; i <= (n - 1) * 2; i++) {
        for (int j = 0; j < 26; j++) {
            for (int x = 0; x < n; x++) {
                int y = i - x;
                if (y >= 0 && y < n && s[x][y] - 'a' == j) {
                    mask[i][j] |= (1 << x);
                }
            }
        }
    }
    debug(mask);

    vector<vector<int>> dp;
    int LIMIT = 1 << n;
    dp.resize(n * 2 - 1, vector<int>(LIMIT, -1e9));

    auto dfs = [&](auto self, int d, int status, char it) -> int {
        // debug(d, status);
        if (dp[d][status] != -1e9) return dp[d][status];
        int turn = d % 2;
        int score = 0;

        if (turn == 0) {
            // second 要动
            if (it == 'a') {
                score = -1;
            } else if (it == 'b') {
                score = 1;
            }
        } else {
            // first 要动
            if (it == 'a') {
                score = 1;
            } else if (it == 'b') {
                score = -1;
            }
        }

        if (d == n * 2 - 2) {
            return dp[d][status] = score;
        }

        int res = 1e9;
        for (int i = 0; i < 26; i++) {
            int tmp = mask[d + 1][i] & (status | (status << 1));
            if (tmp) {
                int tmp2 = self(self, d + 1, tmp, 'a' + i);
                res = min(res, tmp2);
            }
        }
        if (res == 1e9) res = 0;
        return dp[d][status] = score - res;
    };

    dfs(dfs, 0, 1, s[0][0]);
    debug(dp);

    if (dp[0][1] == 0) {
        cout << "DRAW" << endl;
    } else if (dp[0][1] > 0) {
        cout << "SECOND" << endl;
    } else {
        cout << "FIRST" << endl;
    }
    return 0;
}