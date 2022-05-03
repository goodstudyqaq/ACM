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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> V(n + 1);
    vector<int> in(n + 1);
    vector<int> out(n + 1);
    vector<int> cur(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        in[v]++;
        out[u]++;
        cur[v]++;
    }
    queue<int> Q;
    vector<int> f(n + 1);
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            Q.push(i);
            f[i] = 0;
        }
    }
    int ans = 0;
    while (!Q.empty()) {
        auto u = Q.front();
        ans = max(ans, f[u]);
        Q.pop();

        for (auto v : V[u]) {
            if (in[v] > 1 && out[u] > 1) {
                f[v] = max(f[v], f[u] + 1);
            }
            cur[v]--;
            if (cur[v] == 0) {
                Q.push(v);
            }
        }
    }
    cout << ans + 1 << endl;
    return 0;
}