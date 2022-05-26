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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<vector<int>> V(n);
    map<array<int, 2>, int> ID;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        V[x].push_back(y);
        V[y].push_back(x);
        ID[{x, y}] = ID[{y, x}] = i;
    }
    vector<int> score(n);
    vector<bool> vis(n);
    vector<int> node;
    function<void(int, int)> dfs = [&](int now, int s) {
        node.push_back(now);
        score[now] = s;
        vis[now] = 1;
        int val = a[now];
        int next_location = val;
        if (!vis[next_location]) {
            dfs(next_location, s + 1);
        }
    };

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            node.clear();
            dfs(i, 0);
            int sz = node.size();
            for (int u : node) {
                sort(V[u].begin(), V[u].end(), [&](int v1, int v2) {
                    return (score[v1] - score[u] + sz) % sz < (score[v2] - score[u] + sz) % sz;
                });
            }
        }
    }

    vector<int> cur(n);

    function<void(int)> work = [&](int x) {
        int sz = V[x].size();
        if (cur[x] == sz) return;
        int y = V[x][cur[x]];
        if (V[y][cur[y]] != x) return;
        cout << ID[{x, y}] + 1 << ' ';

        // cout << x + 1 << ' ' << y + 1 << endl;
        cur[x]++, cur[y]++;
        work(x);
        work(y);
    };

    for (int i = 0; i < n; i++) {
        work(i);
    }
    cout << endl;
    return 0;
}