#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef array<int, 2> a2;

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
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<vector<int>> V2(n);
    vector<int> dep(n), fa(n);

    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        dep[u] = d;
        fa[u] = pre;
        V2[d].push_back(u);
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    };
    dfs(0, -1, 0);
    debug(V2);

    auto work = [&]() {
        vector<int> color(n, -1);
        map<int, vector<int>> M;
        int c = 0;
        color[0] = c;

        for (int i = 1; i < n; i++) {
            int sz = V2[i].size();
            if (sz == 0) break;
            set<int> fa_set;
            vector<int> fa_color;
            vector<int> first;
            for (int u : V2[i]) {
                int pre = fa[u];
                if (fa_set.count(pre)) {
                    continue;
                }
                first.push_back(u);
                fa_set.insert(pre);
                fa_color.push_back(color[pre]);
            }

            set<int> use_color;

            if (fa_set.size() == 1) {
                use_color.insert(fa_color[0]);
            } else {
                int child_sz = first.size();
                for (int j = 0; j < first.size(); j++) {
                    use_color.insert(fa_color[j]);
                    color[first[j]] = fa_color[(j + 1) % child_sz];
                }
            }
            debug(i, use_color);
            int now_color = 0;
            for (int u : V2[i]) {
                if (color[u] != -1) continue;
                while (use_color.count(now_color)) now_color++;
                color[u] = now_color;
                now_color++;
            }
        }

        for (int i = 0; i < n; i++) {
            if (M.count(color[i]) == 0) {
                M[color[i]] = {};
            }
            M[color[i]].push_back(i);
        }
        debug(color);


        int sz = M.size();
        cout << sz << '\n';

        for (auto it : M) {
            cout << it.second.size() << ' ';
            for (auto u : it.second) {
                cout << u + 1 << ' ';
            }
            cout << '\n';
        }
    };
    work();
    // debug("zz");
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