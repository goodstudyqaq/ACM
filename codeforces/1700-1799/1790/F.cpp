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
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        c[i]--;
    }

    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    int ans = n;
    vector<int> dis(n, n);
    for (int i = 0; i < n; i++) {
        // debug(i, dis);
        ans = min(ans, dis[c[i]]);
        if (i) {
            cout << ans << ' ';
        }
        dis[c[i]] = 0;
        queue<int> Q;
        Q.push(c[i]);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (auto v : V[u]) {
                if (dis[v] > dis[u] + 1 && dis[u] + 1 < ans) {
                    dis[v] = dis[u] + 1;
                    Q.push(v);
                }
            }
        }
    }
    cout << endl;
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