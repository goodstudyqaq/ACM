#include <bits/stdc++.h>

#include "./structure/bbst/treap.hpp"

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
    NonRotatingTreap<long long> treap;

    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<long long> r(n), b(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> r[i];
        ans += r[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        ans += b[i];
    }

    auto del_zero = [&]() {
        int x, y;
        treap.split_by_value(treap.root, 0, x, y);
        treap.root = y;
    };

    auto del_kmax = [&](long long k) {
        int sz = treap.nodes[treap.root].size;
        k = min(k, 1LL * sz);
        if (k == 0) {
            return 0LL;
        }
        int x, y;
        treap.split_by_rank(treap.root, sz - k, x, y);
        int left_mx = treap.qmax(x);
        int right_mi = treap.qmin(y);
        if (left_mx < right_mi) {
            treap.push_tag(y, -1);
            treap.root = treap.merge(x, y);
        } else {
            // 相等
            int left_x, right_x;
            int left_y, right_y;

            treap.split_by_value(x, left_mx - 1, left_x, right_x);
            treap.split_by_value(y, left_mx, left_y, right_y);

            treap.push_tag(left_y, -1);
            treap.push_tag(right_y, -1);
            treap.merge(treap.merge(left_x, left_y), treap.merge(right_x, right_y));
        }
        return k;
    };

    for (int i = 0; i < n; i++) {
        long long tmp = min(r[i], b[i]);
        ans -= tmp;
        if (s[i] == '0') {
            tmp = r[i] - tmp;
            long long k = del_kmax(tmp);
            ans -= k;
            del_zero();
        } else {
            tmp = r[i] - tmp;
            if (tmp) {
                treap.insert(tmp);
            }
        }
    }
    cout << ans << endl;
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