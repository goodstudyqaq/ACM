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

typedef pair<int, int> pii;
vector<vector<pii>> dp;
vector<vector<vector<int>>> path;

vector<vector<int>> V;
pii dfs(int u, int pre, int choose) {
    if (dp[u][choose].first != -1) return dp[u][choose];
    pii res = {choose, (choose ? -V[u].size() : -1)};
    for (int i = 0; i < V[u].size(); i++) {
        int v = V[u][i];
        if (v == pre) continue;
        pii nxt = dfs(v, u, 0);
        path[u][choose][i] = 0;
        if (choose == 0) {
            pii nxt2 = dfs(v, u, 1);
            if (nxt < nxt2) {
                nxt = nxt2;
                path[u][choose][i] = 1;
            }
        }
        res.first += nxt.first;
        res.second += nxt.second;
    }
    return dp[u][choose] = res;
}
vector<int> good;

void dfs2(int u, int pre, int choose) {
    good[u] = choose;
    for (int i = 0; i < V[u].size(); i++) {
        int v = V[u][i];
        if (v == pre) continue;
        int c2 = path[u][choose][i];
        dfs2(v, u, c2);
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    V.resize(n + 1);
    dp.resize(n + 1, vector<pii>(2, {-1, -1}));
    good.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    path.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        path[i].resize(2, vector<int>((int)V[i].size()));
    }
    if (n == 2) {
        cout << "2 2" << endl
             << "1 1" << endl;
        return 0;
    }
    pii res1 = dfs(1, 0, 0);
    pii res2 = dfs(1, 0, 1);
    pii res = max(res1, res2);
    cout << res.first << ' ' << -res.second << endl;
    if (res == res1) {
        dfs2(1, 0, 0);
    } else {
        dfs2(1, 0, 1);
    }

    for (int i = 1; i <= n; i++) {
        if (good[i]) {
            cout << V[i].size() << ' ';
        } else {
            cout << 1 << ' ';
        }
    }
    cout << endl;
}