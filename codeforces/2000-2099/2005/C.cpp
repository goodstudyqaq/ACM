#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(5, -1e9));

    // for (int i = 0; i < 5; i++) {
    //     dp[0][i] = -1e9;
    // }
    dp[0][4] = 0;

    vector<char> V({'n', 'a', 'r', 'e', 'k'});
    set<char> S({'n', 'a', 'r', 'e', 'k'});

    auto get_score = [&](int idx, int status) -> pair<int, int> {
        int score = 0;
        status = (status + 1) % 5;
        for (int i = 0; i < m; i++) {
            if (s[idx][i] == V[status]) {
                score++;
                status = (status + 1) % 5;
            } else if (S.count(s[idx][i])) {
                score--;
            }
        }
        status = (status + 4) % 5;
        return {score, status};
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            // if (dp[i][j] < 0) continue;
            debug(i, j, dp[i][j]);
            // 不选 s[i + 1]
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            // 选择 s[i + 1]
            auto [score, status] = get_score(i + 1, j);
            dp[i + 1][status] = max(dp[i + 1][status], dp[i][j] + score);
        }
    }

    int ans = 0;
    for (int i = 0; i < 5; i++) {
        debug(i, dp[n][i]);
        ans = max(ans, dp[n][i] - 2 * ((i + 1) % 5));
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}