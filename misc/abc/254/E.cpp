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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> V(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    int q;
    cin >> q;

    while (q--) {
        int x, k;
        cin >> x >> k;
        set<int> S;
        queue<pii> Q;
        Q.push({x, 0});
        int ans = 0;
        S.insert(x);
        while (!Q.empty()) {
            auto it = Q.front();
            Q.pop();
            ans += it.first;
            if (it.second == k) continue;
            for (auto v : V[it.first]) {
                if (S.count(v)) continue;
                Q.push({v, it.second + 1});
                S.insert(v);
            }
        }
        cout << ans << endl;
    }
    return 0;
}