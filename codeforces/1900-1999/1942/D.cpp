#include <bits/stdc++.h>

#include <functional>
#include <queue>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> dp(n + 1);

    dp[0].push_back(0);
    typedef array<int, 3> a3;
    for (int i = 1; i <= n; i++) {
        priority_queue<a3> Q;
        for (int j = i - 1; j >= -1; j--) {
            if (j == -1) {
                Q.push({a[j + 2][i], j, 0});
            } else if (j == i - 1) {
                Q.push({dp[j][0], j, 0});
            } else {
                Q.push({dp[j][0] + a[j + 2][i], j, 0});
            }
        }

        int times = k;
        while (!Q.empty() && times--) {
            auto [val, idx, idx2] = Q.top();
            Q.pop();
            dp[i].push_back(val);

            if (idx == -1) {
                continue;
            }
            if (idx2 == dp[idx].size() - 1) continue;
            if (idx == i - 1) {
                Q.push({dp[idx][idx2 + 1], idx, idx2 + 1});
            } else {
                Q.push({dp[idx][idx2 + 1] + a[idx + 2][i], idx, idx2 + 1});
            }
        }
        sort(dp[i].begin(), dp[i].end(), greater<int>());
    }

    for (int i = 0; i < k; i++) {
        cout << dp[n][i] << ' ';
    }
    cout << endl;
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