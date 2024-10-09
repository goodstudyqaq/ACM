#include <bits/stdc++.h>

#include "./graph/others/cartesian-tree.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto p = cartesian_tree(a);
    int root = -1;

    vector<vector<int>> V(n);
    for (int i = 0; i < n; i++) {
        if (p[i] == -1) {
            root = i;
        } else {
            V[p[i]].push_back(i);
        }
    }

    int now = 1;
    vector<int> ans(n);
    function<void(int)> dfs = [&](int u) {
        ans[u] = now++;
        for (auto v : V[u]) {
            dfs(v);
        }
    };

    dfs(root);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}