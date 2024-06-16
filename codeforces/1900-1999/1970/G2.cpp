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

struct DSU {
    std::vector<int> f;
    DSU(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
    void clear() {
        for (int i = 0; i < f.size(); i++) f[i] = i;
    }
};

void solve() {
    int n, m, c;
    cin >> n >> m >> c;

    vector<pii> edges(m);
    DSU dsu(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        dsu.merge(u, v);
    }

    map<int, int> M;
    for (int i = 1; i <= n; i++) {
        M[dsu.leader(i)]++;
    }
    debug(M);

    long long ans = 1LL * (M.size() - 1) * c;
    int ans2 = 1e9;

    for (int i = 0; i < m; i++) {
        dsu.clear();
        for (int j = 0; j < m; j++) {
            if (i == j) continue;
            dsu.merge(edges[j].first, edges[j].second);
        }
        map<int, int> M2;
        for (int i = 1; i <= n; i++) {
            M2[dsu.leader(i)]++;
        }
        if (M2.size() == M.size() + 1) {
            // debug(edges[i]);
            bitset<301> bs;
            bs[0] = 1;
            for (auto it : M2) {
                int num = it.second;
                bs |= (bs << num);
            }

            for (int j = 0; j <= n; j++) {
                if (bs[j]) {
                    ans2 = min(ans2, j * j + (n - j) * (n - j));
                }
            }
        }
    }

    bitset<301> bs;
    bs[0] = 1;
    if (M.size() > 1) {
        for (auto it : M) {
            int num = it.second;
            bs |= (bs << num);
        }
        for (int j = 0; j <= n; j++) {
            if (bs[j]) {
                ans2 = min(ans2, j * j + (n - j) * (n - j));
            }
        }
    }

    if (ans2 == 1e9) {
        cout << -1 << endl;
        return;
    }
    ans += ans2;
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
    return 0;
}