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

vector<int> f;
int find(int u) {
    return f[u] == u ? u : f[u] = find(f[u]);
}

void Union(int u, int v) {
    int fu = find(u), fv = find(v);
    f[fu] = fv;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(n + 1);
    f.resize(n + 2);
    iota(f.begin(), f.end(), 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<int> l(m), r(m), d(m);
    vector<vector<int>> G(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        l[i]--;
        d[i] = 2;
        G[l[i]].push_back(i);
        G[r[i]].push_back(i);
    }

    vector<ll> sa(n + 1), sb(n + 1);
    for (int i = 1; i <= n; i++) {
        sa[i] = sa[i - 1] + a[i];
        sb[i] = sb[i - 1] + b[i];
    }
    // 0 能遍布到的右下标
    function<void(int)> set = [&](int u) {
        Union(u, u + 1);
        for (auto it : G[u]) {
            d[it]--;
            if (d[it] == 0) {
                int x = find(l[it]);
                while (x <= r[it]) {
                    set(x);
                    x = find(x);
                }
            }
        }
    };

    for (int i = 0; i <= n; i++) {
        if (sa[i] == sb[i]) {
            set(i);
        }
    }
    if (find(0) != n + 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
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