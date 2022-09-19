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
vector<vector<pii>> V;
const int maxn = 1e5 + 5;
int DFN[maxn], LOW[maxn];
int fa[maxn];
int id;
const int maxm = 3e5 + 5;
int vis[maxm];
vector<pii> edges;
vector<pii> ans;

void tarjan(int u, int pre) {
    DFN[u] = LOW[u] = ++id;
    fa[u] = pre;
    for (auto e : V[u]) {
        auto [v, idx] = e;
        if (vis[idx] == 0) {
            ans.push_back({u, v});
            vis[idx] = 1;
        }
        if (!DFN[v]) {
            tarjan(v, u);
            LOW[u] = min(LOW[u], LOW[v]);
        } else if (v != pre) {
            LOW[u] = min(LOW[u], DFN[v]);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    V.resize(n + 1);
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back({v, i});
        V[v].push_back({u, i});
        edges[i] = {u, v};
    }

    for (int i = 1; i <= n; i++) {
        if (!DFN[i]) {
            id = 0;
            tarjan(i, -1);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (fa[i] == -1) continue;
        if (DFN[fa[i]] < LOW[i]) {
            cout << 0 << endl;
            return 0;
        }
    }

    for (auto it : ans) {
        cout << it.first << ' ' << it.second << endl;
    }
    return 0;
}