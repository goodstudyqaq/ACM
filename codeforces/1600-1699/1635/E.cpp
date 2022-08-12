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
typedef array<int, 3> a3;

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
    vector<a3> edges;
    vector<vector<int>> V(n + 1);

    for (int i = 0; i < m; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        edges.push_back({t, x, y});
        V[x].push_back(y);
        V[y].push_back(x);
    }

    vector<int> color(n + 1, -1);

    function<bool(int, int)> dfs = [&](int u, int pre) -> bool {
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (color[v] == -1) {
                color[v] = color[u] ^ 1;
                bool res = dfs(v, u);
                if (!res) return false;
            } else {
                if (color[u] == color[v]) return false;
            }
        }
        return true;
    };

    auto check1 = [&]() -> bool {
        for (int i = 1; i <= n; i++) {
            if (color[i] == -1) {
                color[i] = 0;
                if (!dfs(i, -1)) return false;
            }
        }
        return true;
    };

    if (!check1()) {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        V[i].clear();
    }
    vector<int> in(n + 1);

    for (int i = 0; i < m; i++) {
        auto [t, x, y] = edges[i];
        if (color[x] == 1) {
            swap(x, y);
        }
        if (t == 1) {
            V[x].push_back(y);
            in[y]++;
        } else {
            V[y].push_back(x);
            in[x]++;
        }
    }

    vector<int> ans;

    auto check2 = [&]() -> bool {
        queue<int> Q;
        for (int i = 1; i <= n; i++) {
            if (in[i] == 0) {
                Q.push(i);
            }
        }

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            ans.push_back(u);

            for (auto v : V[u]) {
                in[v]--;
                if (in[v] == 0) {
                    Q.push(v);
                }
            }
        }
        return ans.size() == n;
    };

    if (!check2()) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    vector<int> real_ans(n + 1);

    for (int i = 0; i < n; i++) {
        int it = ans[i];
        real_ans[it] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            cout << "L " << real_ans[i] << endl;
        } else {
            cout << "R " << real_ans[i] << endl;
        }
    }
    return 0;
}