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
    vector<int> a(n + 1);
    vector<vector<int>> V(n + 1);
    unordered_set<int> S;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        V[a[i]].push_back(i);
        S.insert(a[i]);
    }

    ll ans = 0;
    vector<int> val(n + 1);
    for (auto i : S) {
        Fenwick<int> fen(n);
        for (auto idx : V[i]) {
            fen.add(idx, 1);
        }
        for (auto j : S) {
            int sz = V[j].size();
            if (i == j) {
                if (sz >= 4) {
                    ans += 1LL * sz * (sz - 1) * (sz - 2) * (sz - 3) / 24;
                }
                continue;
            }
            ll all = 0;
            for (int p = 0; p < sz; p++) {
                val[p] = fen.query(V[j][p]);
                all += val[p];
            }

            for (int p = 0; p < sz; p++) {
                all -= val[p];
                ans += 1LL * val[p] * all - 1LL * val[p] * val[p] * (sz - p - 1);
            }
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