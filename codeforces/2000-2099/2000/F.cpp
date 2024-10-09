#include <bits/stdc++.h>

#include <limits>
#include <numeric>

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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        if (a[i] > b[i]) swap(a[i], b[i]);
    }
    const int inf = numeric_limits<int>::max() / 2;
    vector<long long> dp(k + 1, inf);
    dp[0] = 0;

    auto get_score = [&](int a, int b) -> vector<long long> {
        vector<long long> res;
        res.push_back(0);
        long long use = 0;
        while (a != 1 || b != 1) {
            if (a > b) swap(a, b);
            use += a;
            res.push_back(use);
            b--;
        }
        res.push_back(inf);
        use++;
        res.push_back(use);
        return res;
    };

    for (int i = 1; i <= n; i++) {
        int _a = a[i - 1], _b = b[i - 1];
        auto score = get_score(_a, _b);

        vector<long long> ndp(k + 1, inf);
        for (int j = 0; j <= k; j++) {
            for (int p = 0; p <= _a + _b; p++) {
                ndp[min(j + p, k)] = min(ndp[min(j + p, k)], dp[j] + score[p]);
            }
        }
        dp = ndp;
    }

    if (dp[k] == inf) dp[k] = -1;
    cout << dp[k] << endl;
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