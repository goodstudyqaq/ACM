#include <bits/stdc++.h>

#include "./graph/connected-components/strongly-connected-components.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    StronglyConnectedComponents<int> g(n);
    g.read(m, -1, false, true);
    g.build();

    auto dag = g.dag;

    int n2 = dag.size();
    vector<int> in(n2);
    for (int i = 0; i < n2; i++) {
        for (auto v : dag[i]) {
            in[v]++;
        }
    }

    vector<long long> sum(n2);
    for (int i = 0; i < n; i++) {
        sum[g.comp[i]] += a[i];
    }

    queue<int> Q;
    vector<pair<int, long long>> res(n2);
    for (int i = 0; i < n2; i++) {
        if (in[i] == 0) {
            Q.push(i);
            res[i] = {g.group[i].size(), sum[i]};
        }
    }

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto v : dag[u]) {
            in[v]--;
            if (res[v].first < res[u].first + g.group[v].size()) {
                res[v].first = res[u].first + g.group[v].size();
                res[v].second = res[u].second + sum[v];
            } else if (res[v].first == res[u].first + g.group[v].size()) {
                res[v].second = min(res[v].second, res[u].second + sum[v]);
            }
            if (in[v] == 0) {
                Q.push(v);
            }
        }
    }
    pair<int, long long> ans = {0, 0};
    for (int i = 0; i < n2; i++) {
        if (ans.first < res[i].first) {
            ans = res[i];
        } else if (ans.first == res[i].first) {
            ans = min(ans, res[i]);
        }
    }
    cout << ans.first << ' ' << ans.second << endl;
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