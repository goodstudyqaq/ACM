#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
vector<ll> V2;
void init() {
    ll maxn = 1e12;
    ll d = 2;
    for (int i = 3;; i++) {
        d = d * i;
        if (d > maxn) break;
        V2.push_back(d);
    }
    debug(V2.size());
}

int get_one(ll val) {
    int res = 0;
    while (val) {
        if (val % 2) res++;
        val /= 2;
    }
    return res;
}

void solve() {
    ll n;
    cin >> n;
    int sz = V2.size();

    int LIMIT = 1 << sz;
    int ans = 1e9;
    for (int i = 0; i < LIMIT; i++) {
        ll val = 0;
        int cnt = 0;
        for (int j = 0; j < sz; j++) {
            if ((i >> j) & 1) {
                val += V2[j];
                cnt++;
            }
        }
        if (val <= n) {
            ans = min(ans, cnt + get_one(n - val));
        }
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}