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

vector<vector<int>> V, V2;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    V.resize(n + 1);
    V2.resize(n + 1);
    map<pii, int> M;

    vector<int> cnt(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V2[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cnt[i] = V[i].size();
    }

    const int inf = numeric_limits<int>::max() / 2;
    vector<int> dis(n + 1, inf), vis(n + 1, 0);

    priority_queue<pii, vector<pii>, greater<pii>> Q;
    dis[n] = 0;
    Q.push({0, n});

    while (!Q.empty()) {
        auto it = Q.top();
        debug(it);
        Q.pop();
        int d = it.first, u = it.second;
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto v : V2[u]) {
            int sz = cnt[v];
            if (dis[v] > d + sz) {
                dis[v] = d + sz;
                Q.push({dis[v], v});
            }
            cnt[v]--;
        }
    }
    cout << dis[1] << endl;
    return 0;
}