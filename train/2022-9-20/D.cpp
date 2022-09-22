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

template <typename T>
struct Fenwick {
#define lowbit(x) x & -x
    const int n;
    vector<T> a;
    Fenwick(int n) : n(n), a(n + 1) {}
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    Fenwick<int> fen(n);

    vector<vector<int>> V(26);
    for (int i = n - 1; i >= 0; i--) {
        V[s[i] - 'a'].push_back(i + 1);
    }
    const ll inf = numeric_limits<ll>::max() / 2;
    ll res = inf;
    ll now = 0;
    for (int i = 0; i < n; i++) {
        int need = t[i] - 'a';
        int now_idx = 1e9;
        for (int j = 0; j < need; j++) {
            if (V[j].size()) {
                int idx = V[j].back();
                now_idx = min(now_idx, idx);
            }
        }

        if (now_idx != 1e9) {
            int cnt = fen.query(now_idx);
            res = min(res, now + now_idx - cnt - 1);
        }

        if (V[need].size()) {
            int idx = V[need].back();
            int cnt = fen.query(idx);
            now += idx - cnt - 1;
            V[need].pop_back();
            fen.add(idx, 1);
        } else {
            break;
        }
    }
    if (res == inf) res = -1;
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