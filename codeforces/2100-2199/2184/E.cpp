#include <bits/stdc++.h>

#include "structure/union-find/union-find.hpp"

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
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    UnionFind uf_left(n), uf_right(n);

    vector<a2> V(n - 1);
    for (int i = 0; i < n - 1; i++) {
        V[i] = {abs(p[i] - p[i + 1]), i};
    }
    sort(V.begin(), V.end());
    reverse(V.begin(), V.end());

    set<a2> S;
    ll ans = 0;
    int now = 0;

    auto rm = [&](int l, int r) {
        S.erase({l, r});
        int n = r - l + 1;
        ans -= 1LL * n * (n - 1) / 2;
    };

    auto add = [&](int l, int r) {
        S.insert({l, r});
        int n = r - l + 1;
        ans += 1LL * n * (n - 1) / 2;
    };
    vector<ll> res;

    for (int i = n - 1; i >= 1; i--) {
        while (now < n - 1 && V[now][0] >= i) {
            int l = V[now][1];
            int r = l + 1;

            int l2 = uf_left.find(l);
            int r2 = uf_right.find(r);

            if (l2 != l) {
                rm(l2, l);
            }
            if (r2 != r) {
                rm(r, r2);
            }
            add(l2, r2);
            uf_left.unite(r, l);
            uf_right.unite(l, r);
            now++;
        }
        // debug(S, ans);
        res.push_back(ans);
        // cout << ans << ' ';
    }

    reverse(res.begin(), res.end());
    for (auto it : res) {
        cout << it << ' ';
    }

    cout << '\n';
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