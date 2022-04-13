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

vector<int> f;
int find(int u) {
    return f[u] == u ? u : f[u] = find(f[u]);
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    const int mod = 998244353;
    const int maxn = 2e5;
    vector<int> f1, g;
    f1.resize(maxn + 1);
    g.resize(maxn + 1);

    f1[1] = 2, f1[2] = 3;
    for (int i = 3; i <= maxn; i++) {
        f1[i] = (f1[i - 1] + f1[i - 2]) % mod;
    }

    g[1] = 1, g[2] = 3, g[3] = 4;
    for (int i = 4; i <= maxn; i++) {
        g[i] = (f1[i - 1] + f1[i - 3]) % mod;
        if (i <= 10) {
            debug(i, g[i]);
        }
    }

    int n;
    cin >> n;
    vector<int> p, q;
    p.resize(n + 1);
    q.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> q[i];
    }

    f.resize(n + 1);
    iota(f.begin(), f.end(), 0);

    for (int i = 1; i <= n; i++) {
        int u = p[i], v = q[i];
        int fu = find(u), fv = find(v);
        f[fu] = fv;
    }

    vector<int> V(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int fi = find(i);
        V[fi]++;
    }
    long long ans = 1;
    for (int i = 1; i <= n; i++) {
        if (V[i] > 0) {
            ans = ans * g[V[i]] % mod;
        }
    }
    cout << ans << endl;
    return 0;
}