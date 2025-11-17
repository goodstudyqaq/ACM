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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long ans = 0;

    if (a[0] >= a[1]) {
        a[1] = a[0];
        a[0] -= 1;
        ans++;
    }

    int mx = max(a[0], a[1]);
    for (int i = 2; i < n; i++) {
        if (i % 2 == 0) {
            if (a[i] >= mx) {
                ans += a[i] - mx + 1;
                // a[i] = mx - 1;
            }
            mx = max(mx, a[i]);
        } else {
            mx = max(mx, a[i]);
            a[i] = mx;
        }
        debug(i, ans);
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