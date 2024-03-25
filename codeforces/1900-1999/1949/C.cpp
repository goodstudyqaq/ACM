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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    typedef pair<int, int> pii;
    priority_queue<pii, vector<pii>, greater<pii>> Q;

    vector<int> sz(n);
    for (int i = 0; i < n; i++) {
        sz[i] = V[i].size();
    }
    vector<int> score(n, 1);

    for (int i = 0; i < n; i++) {
        if (sz[i] == 1) {
            Q.push({score[i], i});
        }
    }
    vector<int> vis(n, 0);

    while (!Q.empty()) {
        auto [s, u] = Q.top();
        debug(s, u);
        Q.pop();
        vis[u] = 1;

        for (auto v : V[u]) {
            if (vis[v]) continue;
            if (score[v] < s) {
                debug(v, score[v]);
                cout << "NO" << endl;
                return 0;
            } else {
                score[v] += s;
                sz[v]--;
                if (sz[v] == 1) {
                    Q.push({score[v], v});
                }
            }
        }
    }
    cout << "YES" << endl;
    return 0;
}