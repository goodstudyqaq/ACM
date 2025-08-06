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
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 1e9;
    for (int i = 1; i <= n; i++) {
        int mi = 1e9;
        int mx = 0;
        for (int j = i; j <= n; j++) {
            mi = min(mi, a[j]);
            mx = max(mx, a[j]);

            // [mi, mx]
            if (i != 1) {
                int val = a[i - 1];
                // [val - 1, val + 1] 和 [mi, mx] 有交
                int l = max(val - 1, mi);
                int r = min(val + 1, mx);
                if (l <= r) {
                    ans = min(ans, j - i);
                }
            }

            if (j != n) {
                int val = a[j + 1];
                int l = max(val - 1, mi);
                int r = min(val + 1, mx);
                if (l <= r) {
                    ans = min(ans, j - i);
                }
            }
        }
    }
    if (ans == 1e9) {
        ans = -1;
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