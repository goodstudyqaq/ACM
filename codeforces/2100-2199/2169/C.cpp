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
    vector<long long> a(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    set<long long> S;
    long long ans = sum[n];
    for (int r = 1; r <= n; r++) {
        // 选自己
        long long tmp = sum[n] - a[r] + r + r;
        ans = max(ans, tmp);
        if (S.size()) {
            tmp = sum[n] + 1LL * r * (r + 1) - sum[r] + *S.rbegin();
            ans = max(ans, tmp);
            // debug(sum[n] + 1LL * r * (r + 1) - sum[r], S);
        }
        S.insert(sum[r - 1] - 1LL * r * (r - 1));
    }
    cout << ans << '\n';
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