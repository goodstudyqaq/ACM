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
    map<int, int> num;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        num[a[i]]++;
    }

    map<int, vector<int>> V;
    for (auto it : num) {
        V[it.second].push_back(it.first);
    }

    vector<int> V2;
    for (auto it : V) {
        V2.push_back(it.first);
        sort(V[it.first].begin(), V[it.first].end(), greater<int>());
    }

    ll ans = 0;

    set<pii> S;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        S.insert({u, v});
        S.insert({v, u});
    }

    for (int i = 0; i < V2.size(); i++) {
        int cnt1 = V2[i];
        for (int j = i; j < V2.size(); j++) {
            int cnt2 = V2[j];
            for (int p = 0; p < V[V2[i]].size(); p++) {
                int u = V[V2[i]][p];
                int mx_v = V[V2[j]][0];
                if (ans > 1LL * (cnt1 + cnt2) * (u + mx_v)) break;
                for (int q = 0; q < V[V2[j]].size(); q++) {
                    int u = V[V2[i]][p], v = V[V2[j]][q];
                    if (ans > 1LL * (cnt1 + cnt2) * (u + v)) break;
                    if (u == v) continue;
                    if (S.count({u, v})) continue;
                    debug(u, v, cnt1, cnt2);
                    ans = 1LL * (cnt1 + cnt2) * (u + v);
                    break;
                }
            }
        }
    }
    cout << ans << endl;
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
}