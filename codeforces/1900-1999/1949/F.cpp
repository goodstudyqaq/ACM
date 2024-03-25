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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> V2(m + 1);
    vector<set<int>> V1(n + 1);
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            V1[i].insert(a);
            V2[a].push_back(i);
        }
    }

    typedef pair<int, int> pii;
    set<pii> vis;
    for (int i = 1; i <= m; i++) {
        if (V2[i].size() <= 1) continue;

        sort(V2[i].begin(), V2[i].end(), [&](int x, int y) {
            return V1[x].size() < V1[y].size();
        });

        for (int j = 0; j < V2[i].size() - 1; j++) {
            int u = V2[i][j];
            int v = V2[i][j + 1];
            if (vis.count({min(u, v), max(u, v)})) continue;
            vis.insert({min(u, v), max(u, v)});
            for (auto it : V1[V2[i][j]]) {
                if (V1[V2[i][j + 1]].count(it) == 0) {
                    cout << "YES" << endl;
                    cout << V2[i][j] << ' ' << V2[i][j + 1] << endl;
                    return 0;
                }
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}