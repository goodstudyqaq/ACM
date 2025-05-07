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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (k == 1) {
        long long res = a[0] + a[n - 1];
        for (int i = 1; i < n - 1; i++) {
            long long tmp = a[i] + max(a[0], a[n - 1]);
            res = max(res, tmp);
        }
        cout << res << '\n';
        return;
    }

    sort(a.begin(), a.end());

    long long ans = 0;
    for (int i = 0; i < k + 1; i++) {
        ans += a[n - i - 1];
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