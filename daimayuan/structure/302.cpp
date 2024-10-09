#include <bits/stdc++.h>

#include "./structure/others/binary-indexed-tree.hpp"

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
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<pair<int, int>>> qur(n + 1);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        qur[r].push_back({l, i});
    }

    vector<int> pos(n + 1);
    BIT<long long> bit(n);

    vector<long long> ans(q);
    for (int i = 1; i <= n; i++) {
        int l = pos[a[i]];
        bit.add(l + 1, a[i]);
        bit.add(i + 1, -a[i]);
        pos[a[i]] = i;
        for (auto &it : qur[i]) {
            ans[it.second] = bit.query(it.first);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}