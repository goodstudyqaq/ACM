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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    map<int, vector<int>> M;
    vector<int> idx(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        idx[i] = M[a[i]].size();
        M[a[i]].push_back(i);
    }

    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        // 不拿
        dp[i] = dp[i - 1];
        // 拿
        int val = a[i];
        int _idx = idx[i];
        if (_idx >= val - 1) {
            dp[i] = max(dp[i], dp[M[a[i]][_idx - val + 1] - 1] + val);
        }
    }
    cout << dp[n] << '\n';
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