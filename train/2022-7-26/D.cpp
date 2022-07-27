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
    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    if (a > b * c) {
        cout << -1 << endl;
        return;
    }

    int times = c / d;

    if (times == 0) {
        cout << a << endl;
        return;
    }

    ll ans = a;

    int i = a / (1LL * d * b);

    ans = ans + 1LL * a * i - 1LL * d * b * (1 + i) * i / 2;

    // for (int i = 1; i <= times; i++) {
    //     if (a > 1LL * i * d * b) {
    //         ans = ans + a - 1LL * i * d * b;
    //     } else {
    //         break;
    //     }
    // }
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