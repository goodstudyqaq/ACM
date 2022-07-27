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
    int n, c, q;
    cin >> n >> c >> q;
    string s;
    cin >> s;

    ll now = n;
    vector<pll> V;

    while (c--) {
        ll l, r;
        cin >> l >> r;
        ll len = r - l + 1;
        V.push_back({now, l - 1});
        now += len;
    }

    const ll inf = numeric_limits<long long>::max() / 2;

    auto work = [&](ll idx) -> char {
        while (idx >= n) {
            int it = lower_bound(V.begin(), V.end(), make_pair(idx + 1, -1LL)) - V.begin();
            it--;

            auto it2 = V[it];
            ll tmp1 = it2.first, tmp2 = it2.second;
            ll tmp = idx - tmp1;
            idx = tmp2 + tmp;
        }
        return s[idx];
    };

    while (q--) {
        ll k;
        cin >> k;
        cout << work(k - 1) << endl;
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