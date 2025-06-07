#include <bits/stdc++.h>

#include "./structure/segment-tree/segment-tree.hpp"

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

struct Info {
    // 默认值
    int sum;
    Info(int sum = 0) : sum(sum) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info(left_info.sum + right_info.sum);
    }
    string to_string() {
        return "";
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<vector<int>> V(n);
    vector<pair<int, int>> edge(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
        edge[i] = {u, v};
    }

    vector<int> L(n), R(n);
    vector<int> fa(n);
    int ts = 0;
    function<void(int, int)> dfs = [&](int u, int pre) {
        L[u] = ts++;
        fa[u] = pre;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
        }
        R[u] = ts;
    };
    dfs(0, -1);

    vector<Info> infos(n, Info(1));
    SegmentTree<Info> seg(infos);
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, w;
            cin >> x >> w;
            x--;
            int idx = L[x];
            seg.update(idx, Info(w));
        } else {
            int y;
            cin >> y;
            y--;

            auto [u, v] = edge[y];
            if (fa[u] == v) {
                swap(u, v);
            }
            int l = L[v], r = R[v];
            int sum1 = seg.rangeQuery(0, n).sum;
            int sum2 = seg.rangeQuery(l, r).sum;
            int sum3 = sum1 - sum2;
            cout << abs(sum3 - sum2) << '\n';
        }
    }
}