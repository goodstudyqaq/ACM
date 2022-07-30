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

typedef array<ll, 4> a4;
void solve() {
    ll n, m;
    cin >> n >> m;
    m *= 2;
    vector<ll> x(n + 1), p(n + 1);
    map<ll, ll> M;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> p[i];
        x[i] *= 2;
        p[i] *= 2;
        M[x[i] - p[i]]++;
        M[x[i]] -= 2;
        M[x[i] + p[i]]++;
    }
    ll d = 0;
    ll last = -2e9;
    ll last_val = 0;
    const ll inf = numeric_limits<ll>::max() / 2;
    pll interval = {0LL, -inf};

    auto update = [&](pll a, pll b) -> pll {
        ll L = min(a.first - a.second, b.first - b.second);
        ll R = max(a.first + a.second, b.first + b.second);
        return {(L + R) / 2, (R - L) / 2};
    };

    for (auto it : M) {
        ll tmp = last_val + (it.first - last) * d;
        // debug(it, tmp, d);
        if (tmp > m) {
            interval = update(interval, make_pair(it.first, tmp - m));
        }
        last = it.first;
        d = d + it.second;
        last_val = tmp;
    }
    debug(interval);

    string res(n, '0');
    for (int i = 1; i <= n; i++) {
        if (update(interval, {x[i], p[i]}) == make_pair(x[i], p[i])) {
            res[i - 1] = '1';
        }
    }
    cout << res << endl;
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