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

void solve() {
    int n;
    cin >> n;
    vector<ll> h(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    if (n % 2) {
        ll ans = 0;
        for (int i = 2; i <= n; i += 2) {
            ll mx = max(h[i - 1], h[i + 1]);
            if (h[i] <= mx) {
                ans += mx - h[i] + 1;
            }
        }
        cout << ans << endl;
    } else {
        vector<ll> sum1(n + 1, 0);
        vector<ll> sum2(n + 2, 0);
        for (int i = 2; i < n; i += 2) {
            ll mx = max(h[i - 1], h[i + 1]);
            ll tmp = 0;
            if (h[i] <= mx) {
                tmp = mx - h[i] + 1;
            }
            sum1[i] = tmp + sum1[i - 2];
        }

        for (int i = n - 1; i > 1; i -= 2) {
            ll mx = max(h[i - 1], h[i + 1]);
            ll tmp = 0;
            if (h[i] <= mx) {
                tmp = mx - h[i] + 1;
            }
            sum2[i] = tmp + sum2[i + 2];
        }

        ll ans = numeric_limits<ll>::max() / 2;
        for (int i = 1; i <= n; i += 2) {
            ll tmp = sum1[i - 1] + sum2[i + 2];
            ans = min(ans, tmp);
        }
        cout << ans << endl;
    }
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
}