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
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    const ll inf = numeric_limits<ll>::max() / 2;
    ll mx1 = inf, mx2 = inf, mx3 = inf, mx4 = inf;
    for (int i = 0; i < n; i++) {
        mx1 = min(mx1, abs(a[0] - b[i]));
        mx2 = min(mx2, abs(a[n - 1] - b[i]));
        mx3 = min(mx3, abs(b[0] - a[i]));
        mx4 = min(mx4, abs(b[n - 1] - a[i]));
    }

    ll ans = inf;
    ll tmp1 = min(abs(a[0] - b[0]), mx1 + mx3) + min(abs(a[n - 1] - b[n - 1]), mx2 + mx4);
    ans = min(ans, tmp1);
    tmp1 = min(abs(a[0] - b[n - 1]), mx1 + mx4) + min(abs(a[n - 1] - b[0]), mx2 + mx3);
    ans = min(ans, tmp1);
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
}