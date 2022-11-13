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
    ll ab = 1LL * a * b;

    bool flag = false;
    for (int x = a + 1; x <= c; x++) {
        ll tmp = ab / __gcd(1LL * x, ab);
        ll tmp1 = (b + 1) / tmp, tmp2 = d / tmp;
        if (tmp1 != tmp2) {
            int y = tmp2 * tmp;
            cout << x << ' ' << y << endl;
            flag = true;
            break;
        } else {
            if (tmp1 * tmp > b && tmp1 * tmp <= d) {
                int y = tmp1 * tmp;
                cout << x << ' ' << y << endl;
                flag = true;
                break;
            }
        }
    }
    if (!flag) {
        cout << -1 << ' ' << -1 << endl;
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