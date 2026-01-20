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
typedef array<int, 2> a2;

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
    vector<ll> a1(n);
    for (int i = 0; i < n; i++) {
        cin >> a1[i];
    }
    if (n == 1) {
        cout << 0 << '\n';
        return;
    }

    if (n % k) {
        cout << 0 << '\n';
        return;
    }
    vector<ll> a(n);

    auto work = [&](int idx) {
        for (int i = 0; i < n; i++) {
            a[i] = a1[(i + idx) % n];
        }

        vector<ll> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = a[i] ^ a[(i + 1) % n];
        }
        debug(c);

        vector<ll> d(n);

        for (int i = k; i < n; i++) {
            d[i] = d[i - k] ^ c[i - k];
        }

        debug(d);

        ll now = 0;
        vector<ll> V;

        for (int i = 0; i < n; i++) {
            int idx = n - i - 1;
            now ^= d[idx];
            if (i >= k) {
                now ^= d[idx + k];
            }
            debug(idx, a[idx], now);
            V.push_back(a[idx] ^ now);
        }
        debug(V);

        ll ans = 0;

        const int LIMIT = 29;
        for (int i = LIMIT; i >= 0; i--) {
            int one_num = 0, zero_num = 0;
            for (ll j : V) {
                int f = (j >> i) & 1;
                if (f) {
                    one_num++;
                } else {
                    zero_num++;
                }
            }

            int mi = min(one_num, zero_num);
            if (mi > 0) {
                debug(mi, i);
            }
            ans += (1LL << i) * mi;
        }
        return ans;
    };

    ll ans = numeric_limits<ll>::max();
    for (int i = 0; i < 1; i++) {
        ans = min(ans, work(i));
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