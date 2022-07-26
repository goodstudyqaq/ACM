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

    int n, m, first;
    cin >> n >> m >> first;

    vector<vector<pii>> V1(n + 1), V2(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        V1[a].push_back({b, c});
        V2[b].push_back({a, c});
    }

    set<pair<ll, int>> Q;
    const ll inf = numeric_limits<ll>::max() / 2;
    vector<ll> d(n + 1, inf);

    vector<ll> mx(n + 1, 0);
    vector<int> out(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        out[i] = V1[i].size();
    }

    for (int i = 1; i <= n; i++) {
        if (V1[i].size() == 0) {
            Q.insert({0, i});
            Q.insert({0, i + n});
        }
    }

    while (!Q.empty()) {
        auto it = *Q.begin();
        // debug(it);
        Q.erase(Q.begin());
        if (it.second <= n) {
            if (d[it.second] > it.first) {
                d[it.second] = it.first;
            } else {
                continue;
            }
        }
        if (it.second <= n) {
            for (auto v : V2[it.second]) {
                mx[v.first] = max(mx[v.first], it.first + v.second);
                out[v.first]--;
                if (out[v.first] == 0) {
                    Q.insert({mx[v.first], v.first + n});
                }
            }

        } else {
            for (auto v : V2[it.second - n]) {
                Q.insert({it.first + v.second, v.first});
            }
        }
    }

    if (d[first] == inf) {
        cout << "INFINITY" << endl;
    } else {
        cout << d[first] << endl;
    }
    return 0;
}