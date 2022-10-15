#include <bits/stdc++.h>

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

void solve(int n, int W) {
    vector<vector<pii>> item(30);
    int s = 0;
    for (int i = 0; i < n; i++) {
        int w, v;
        cin >> w >> v;
        int lev = __builtin_ctz(w);
        w >>= lev;
        item[lev].push_back({w, v});
        s += w;
    }

    const ll inf = numeric_limits<ll>::max() / 2;
    vector<ll> dp(s + 1, -inf);
    dp[0] = 0;  // 第 30 层只有 0 为 0，前面还剩 0 个
    for (int i = 29; i >= 0; i--) {
        vector<ll> ndp(s + 1, -inf);
        for (int j = 0; j <= s; j++) {
            int j2 = min(j * 2 + ((W >> i) & 1), s);
            ndp[j2] = max(ndp[j2], dp[j]);
        }
        for (int j = s - 1; j >= 0; j--) {
            ndp[j] = max(ndp[j], ndp[j + 1]);
        }
        // debug(i, ndp);
        for (auto it : item[i]) {
            int num = it.first, val = it.second;
            for (int j = 0; j + it.first <= s; j++) {
                ndp[j] = max(ndp[j], ndp[j + it.first] + val);
            }
        }
        dp = ndp;
        // debug(i, dp);
    }
    cout << dp[0] << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, W;
    while (true) {
        cin >> n >> W;
        if (n == -1 && W == -1) break;
        solve(n, W);
    }
    return 0;
}