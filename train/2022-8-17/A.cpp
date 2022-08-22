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
    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    int q;
    cin >> q;
    vector<vector<int>> node(n + 1);
    vector<int> num(q);
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int p;
            cin >> p;
            node[p].push_back(i);
        }
        num[i] = k;
    }

    vector<bool> ans(q, false);

    auto merge = [&](unordered_map<int, int> &a, unordered_map<int, int> &b, unordered_map<int, int> &c) {
        if (a.size() < b.size()) {
            swap(a, b);
        }
        for (auto it : b) {
            int idx = it.first, val = it.second;
            if (a.count(idx)) {
                int a_val = a[idx];
                if (a_val + val + c[idx] == num[idx]) {
                    ans[idx] = true;
                } else {
                    ans[idx] = false;
                }
                a.erase(idx);
                c.erase(idx);
            } else {
                a[idx] = val;
            }
        }
    };

    function<unordered_map<int, int>(int, int)> dfs = [&](int u, int pre) -> unordered_map<int, int> {
        unordered_map<int, int> res;
        unordered_map<int, int> u_info;

        for (auto it : node[u]) {
            u_info[it]++;
        }

        for (auto v : V[u]) {
            if (v == pre) continue;
            auto it = dfs(v, u);
            merge(res, it, u_info);
        }

        for (auto it : u_info) {
            res[it.first] += it.second;
            if (res[it.first] == num[it.first]) {
                ans[it.first] = true;
                res.erase(it.first);
            }
        }
        debug(u, res);

        return res;
    };
    dfs(1, 0);
    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    solve();
}