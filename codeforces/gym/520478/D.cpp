#include <bits/stdc++.h>

#include <algorithm>
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

struct State {
    int x, y, t;
    bool operator<(const State& s) const {
        int val = t - x - y;
        int val2 = s.t - s.x - s.y;
        return val > val2;
    }
};

void solve() {
    int n, m, r;
    cin >> n >> m >> r;
    typedef array<int, 3> a3;
    set<a3> S;
    for (int i = 0; i < r; i++) {
        int t, d, coord;
        cin >> t >> d >> coord;
        S.insert({t, d, coord});
    }
    vector<vector<vector<bool>>> dp(n + 2, vector<vector<bool>>(m + 2, vector<bool>(r + 1)));
    dp[1][1][0] = 1;

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= m + 1; j++) {
            for (int t = 0; t <= r; t++) {
                if (i == 1 && j == 1 && t == 0) continue;
                int time = i - 1 + j - 1 + t;
                if (S.count({time, 1, i - 1}) || S.count({time, 2, j - 1})) {
                    dp[i][j][t] = false;
                } else {
                    if (t > 0) dp[i][j][t] = dp[i][j][t] | dp[i][j][t - 1];
                    dp[i][j][t] = dp[i][j][t] | dp[i - 1][j][t];
                    dp[i][j][t] = dp[i][j][t] | dp[i][j - 1][t];
                }
            }
        }
    }

    for (int t = 0; t <= r; t++) {
        if (dp[n + 1][m + 1][t]) {
            cout << n + m + t << endl;
            return;
        }
    }
    cout << -1 << endl;
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