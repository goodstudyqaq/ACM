#include <bits/stdc++.h>

#include "./structure/union-find/union-find.hpp"

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
    vector<UnionFind> uf(11, UnionFind(n + 1));

    while (m--) {
        int a, d, k;
        cin >> a >> d >> k;
        // [a, a + k * d]
        if (k == 0) continue;
        int r = a + (k - 1) * d;
        int now = uf[d].find(a);
        while (now <= r) {
            int go = now + d;
            uf[d].unite(now, go);
            now = uf[d].find(now);
        }
    }

    int group = 0;

    vector<set<int>> G(11);
    for (int i = 1; i <= n; i++) {
        bool in = false;
        for (int j = 1; j <= 10; j++) {
            int tmp = uf[j].find(i);
            if (G[j].count(tmp)) {
                in = true;
                break;
            }
        }
        if (!in) {
            group++;
        }
        for (int j = 1; j <= 10; j++) {
            int tmp = uf[j].find(i);
            G[j].insert(tmp);
        }
    }
    cout << group << endl;
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