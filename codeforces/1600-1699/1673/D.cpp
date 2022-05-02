#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
typedef long long ll;

void solve() {
    ll b, q, y;
    ll c, r, z;
    cin >> b >> q >> y;
    cin >> c >> r >> z;

    if (r % q || (c - b) % q) {
        cout << 0 << endl;
        return;
    }

    ll tmp1 = r / q, tmp2 = (c - b) / q;
    ll L = tmp2, R = (z - 1) * tmp1 + tmp2;
    if (L < 0 || L >= y || R < 0 || R >= y) {
        cout << 0 << endl;
        return;
    }
    L -= tmp1, R += tmp1;

    if (L < 0 || L >= y || R < 0 || R >= y) {
        cout << -1 << endl;
        return;
    }

    auto get_s = [&](ll v) -> set<ll> {
        set<ll> S;

        for (ll i = 1; i * i <= v; i++) {
            if (v % i == 0) {
                S.insert(i);
                S.insert(v / i);
            }
        }
        return S;
    };

    long long new_q = q * tmp1;
    auto s1 = get_s(new_q);
    auto s2 = get_s(q);

    ll ans = 0;
    const int mod = 1e9 + 7;
    for (auto it : s1) {
        // if (s2.count(it)) continue;
        if (it * q / __gcd(it, q) == r) {
            ll tmp = new_q / it;
            ans = (ans + tmp % mod * tmp % mod) % mod;
        }
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
}