#include <bits/stdc++.h>

#include <limits>

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
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<long long> dp(n, -1);

    function<long long(int)> dfs = [&](int i) -> long long {
        if (dp[i] != -1) return dp[i];
        if (i == -1) return 0;

        long long mi = a[i];
        int idx = i;
        long long res = numeric_limits<long long>::max() / 2;
        for (int j = i; j >= 0; j--) {
            if (mi > a[j]) {
                mi = a[j];
                idx = j;
            }
            int num = i - idx;
            res = min(res, dfs(j - 1) + i - idx + (num + 1) * mi + num);
        }
        return dp[i] = res;
    };
    cout << dfs(n - 1) << '\n';
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