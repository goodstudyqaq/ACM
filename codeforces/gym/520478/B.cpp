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
    int n, m;
    cin >> n >> m;

    vector<vector<int>> V(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[v].push_back(u);
    }

    const int inf = 1e9;
    vector<int> d(n + 1, inf);
    d[1] = 1;
    queue<int> Q;
    Q.push(1);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (auto v : V[u]) {
            if (d[v] > d[u] + 1) {
                d[v] = d[u] + 1;
                Q.push(v);
            }
        }
    }

    vector<vector<int>> T(n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i] == inf) {
            cout << "INFINITE" << endl;
            return;
        }
        T[d[i]].push_back(i);
        ans += d[i];
    }

    cout << "FINITE" << endl;
    cout << ans << endl;

    for (int i = n; i >= 1; i--) {
        for (int j = i; j <= n; j++) {
            for (auto u : T[j]) {
                cout << u << ' ';
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