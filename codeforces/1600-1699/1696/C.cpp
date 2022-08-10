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

ll quick(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b % 2)
            res = res * a;
        b /= 2;
        a = a * a;
    }
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    ll sum_a = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum_a += a[i];
    }

    int k;
    cin >> k;
    vector<ll> b(k + 1);
    ll sum_b = 0;
    for (int i = 1; i <= k; i++) {
        cin >> b[i];
        sum_b += b[i];
    }
    if (sum_a != sum_b) {
        cout << "No" << endl;
        return;
    }

    vector<pll> new_a, new_b;

    auto work = [&](vector<ll> &v, vector<pll> &new_v) {
        int sz = v.size();
        for (int i = 1; i < sz; i++) {
            if (v[i] % m == 0) {
                int cnt = 0;
                ll tmp = v[i];
                while (tmp % m == 0) {
                    tmp /= m;
                    cnt++;
                }
                new_v.emplace_back(make_pair(tmp, quick(m, cnt)));
            } else {
                new_v.emplace_back(make_pair(v[i], 1));
            }
        }

        int now = 0;
        sz = new_v.size();

        int new_sz = 0;
        debug(new_v);

        while (now < sz) {
            int go = now;
            ll cnt = 0;
            while (go < sz && new_v[go].first == new_v[now].first) {
                cnt += new_v[go].second;
                go++;
            }
            new_v[new_sz++] = {new_v[now].first, cnt};
            now = go;
        }
        new_v.resize(new_sz);
    };

    work(a, new_a);
    work(b, new_b);
    debug(new_a);
    debug(new_b);

    if (new_a.size() != new_b.size()) {
        cout << "No" << endl;
        return;
    }
    for (int i = 0; i < new_a.size(); i++) {
        if (new_a[i] != new_b[i]) {
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;
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