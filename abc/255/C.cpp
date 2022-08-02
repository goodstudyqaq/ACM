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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    ll x, a, d, n;
    cin >> x >> a >> d >> n;

    // a + dy y in [0, n - 1]
    ll mx = a + d * (n - 1);
    if (mx < a) {
        swap(mx, a);
        d = -d;
    }
    ll chose;
    if (x <= a) {
        chose = a;
    } else if (x >= mx) {
        chose = mx;
    } else {
        ll y1 = (x - a) / d;
        ll tmp1 = a + d * y1;
        ll tmp2 = a + d * (y1 + 1);
        if (abs(tmp1 - x) < abs(tmp2 - x)) {
            chose = tmp1;
        } else {
            chose = tmp2;
        }
    }

    cout << abs(chose - x) << endl;
}