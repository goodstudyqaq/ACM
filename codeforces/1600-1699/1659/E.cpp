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

struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    vector dsu = vector(30, DSU(n));

    vector<int> good(n);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        for (int j = 29; j >= 0; j--) {
            if ((w >> j) & 1) {
                dsu[j].merge(u, v);
            }
        }
        if (w % 2 == 0) {
            good[u] = good[v] = 1;
        }
    }
    debug(good);

    vector goodr = vector(30, vector(n, 0));
    for (int i = 0; i < n; i++) {
        if (good[i]) {
            for (int j = 1; j < 30; j++) {
                goodr[j][dsu[j].leader(i)] = true;
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int ans = 2;

        for (int i = 0; i < 30; i++) {
            if (dsu[i].same(u, v)) {
                ans = 0;
            }
        }
        if (ans == 0) {
            cout << ans << endl;
            continue;
        }

        for (int i = 1; i < 30; i++) {
            if (goodr[i][dsu[i].leader(u)]) {
                ans = 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}