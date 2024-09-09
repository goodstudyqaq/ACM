#include <bits/stdc++.h>

#include <functional>
#include <queue>

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
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        Q.push({l, r});
    }
    vector<int> choose(n + 1, -1);
    vector<pair<int, int>> new_interval;

    while (!Q.empty()) {
        auto it1 = Q.top();
        if (Q.size() == 1) {
            new_interval.push_back(it1);
            break;
        }
        Q.pop();
        auto it2 = Q.top();

        if (it1.second < it2.first) {
            new_interval.push_back(it1);
            continue;
        }
        // it1.second >= it2.first
        for (int i = it1.first; i <= it2.first; i++) {
            if (choose[i] == 1) {
                cout << -1 << endl;
                return;
            }
            choose[i] = 0;
        }
        for (int i = min(it1.second, it2.second); i <= max(it1.second, it2.second); i++) {
            if (choose[i] == 0) {
                cout << -1 << endl;
                return;
            }
            choose[i] = 1;
        }
        Q.pop();
        Q.push({max(it1.first, it2.first), min(it1.second, it2.second)});
    }

    vector<int> go(n + 1, -1);
    for (auto it : new_interval) {
        go[it.first] = it.second;
    }
    debug(new_interval);
    debug(choose);

    // dp[i][j] 前 i 个数用了 j 个 0
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1e9));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        if (go[i] == -1) {
            for (int j = 0; j <= i; j++) {
                // dp[i][j]
                if (choose[i] == -1) {
                    if (j > 0) {
                        dp[i][j] = dp[i - 1][j - 1] + (i - j);
                    }
                    dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                } else if (choose[i] == 0 && j > 0) {
                    dp[i][j] = dp[i - 1][j - 1] + (i - j);
                } else if (choose[i] == 1) {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        } else {
            int l = i, r = go[i];
            if (r - l == 0) {
                cout << -1 << endl;
                return;
            }

            int new_l = l, new_r = r;
            for (int j = r; j >= l; j--) {
                if (choose[j] == 0) {
                    new_l = j;
                    break;
                }
            }
            for (int j = l; j <= r; j++) {
                if (choose[j] == 1) {
                    new_r = j;
                    break;
                }
            }
            if (new_l >= new_r) {
                cout << -1 << endl;
                return;
            }


            // debug(l, r);
            for (int j = new_l; j < new_r; j++) {
                // [l, j] 都是 0 [j + 1, r] 都是 1
                for (int k = 0; k <= i - 1; k++) {
                    // dp[i - 1][k] -> dp[r][k + j - l + 1]
                    dp[r][k + j - l + 1] = max(dp[r][k + j - l + 1], dp[i - 1][k] + (i - 1 - k) * (j - l + 1));
                }
            }
            i = go[i];
        }
    }

    int ans = 0;
    // debug(dp[4]);
    for (int i = 0; i <= n; i++) {
        if (dp[n][i] >= 0) {
            ans = max(ans, dp[n][i] + i * (i - 1) / 2 + (n - i) * (n - i - 1) / 2);
        }
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