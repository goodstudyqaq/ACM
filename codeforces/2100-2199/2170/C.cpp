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
    ll k;
    cin >> n >> k;
    vector<ll> q(n), r(n);

    multiset<ll> S;
    for (int i = 0; i < n; i++) {
        cin >> q[i];
        S.insert(q[i]);
    }
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }
    sort(r.begin(), r.end());

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ll val = r[i];
        ll y = val + 1;
        if (y > k) break;

        // y * q + val = x <= k

        ll mx_q = (k - val) / y;
        auto it = S.upper_bound(mx_q);
        if (it == S.begin()) {
            continue;
        }
        it--;
        ans++;
        S.erase(it);
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