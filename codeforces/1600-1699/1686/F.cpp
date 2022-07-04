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
    int n;
    cin >> n;
    vector<int> p(n), h(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        h[p[i]] = i;
    }

    vector<int> f(n);
    iota(f.begin(), f.end(), 0);

    function<int(int)> find = [&](int u) -> int {
        return f[u] == u ? u : f[u] = find(f[u]);
    };
    auto Union = [&](int u, int v) {
        int fu = find(u);
        int fv = find(v);
        f[fu] = fv;
    };
    vector<bool> vis(n);

    for (int i = 0; i < n; i++) {
        if (vis[i] == 0) {
            for (int j = p[i]; vis[j] == 0; j = p[j]) {
                vis[j] = 1;
                Union(i, j);
            }
        }
    }
    int times = 0;

    for (int i = 0; i + 1 < n; i++) {
        int fi = find(i), fi2 = find(i + 1);
        if (fi != fi2) {
            times++;
            int x = h[i], y = h[i + 1];
            swap(h[i], h[i + 1]);
            swap(p[x], p[y]);
            Union(i, i + 1);
        }
    }
    debug(p);
    debug(times);
    debug(h);

    for (int i = h[0];; i = h[i]) {
        cout << i + 1 << ' ';
        if (i == 0) {
            cout << endl;
            break;
        }
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