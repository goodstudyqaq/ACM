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

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<a2> V(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        V[i] = {l, r};
    }

    map<a2, int> cache;
    int ask_times = 0;
    auto ask = [&](int l, int r) {
        if (cache.count({l, r})) {
            return cache[{l, r}];
        }
        ask_times++;
        cout << "? " << l << ' ' << r << '\n';
        int res;
        cin >> res;
        return cache[{l, r}] = res;
    };
    auto out = [&](int ans) {
        cout << "! " << ans << '\n';
        fflush(stdout);
    };

    int l = 1, r = n;
    int ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        int val = ask(1, mid);
        if (val == 0) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    debug(ans);
    // ans + 1 就是 0 所在的位置
    int zero_idx = ans + 1;
    int val = ask(1, zero_idx);

    // 找到包括 zero_idx 的区间
    vector<a2> valid;
    for (int i = 0; i < q; i++) {
        if (V[i][0] <= zero_idx && V[i][1] >= zero_idx) {
            valid.push_back(V[i]);
        }
    }
    if (valid.size() == 0) {
        out(0);
        return;
    }
    sort(valid.begin(), valid.end(), [&](a2 x, a2 y) {
        if (x[0] != y[0]) {
            return x[0] < y[0];
        }
        return x[1] > y[1];
    });

    vector<a2> valid2;

    int now = 0;
    while (now < valid.size()) {
        valid2.push_back(valid[now]);
        int go = now;
        while (go < valid.size() && valid[go][1] <= valid[now][1]) {
            go++;
        }
        now = go;
    }
    debug(valid2);

    int sz = valid2.size();
    l = 0, r = sz - 2;
    ans = -1;
    while (l <= r) {
        int m = l + r >> 1;
        int tmp1 = ask(valid2[m][0], valid2[m][1]);
        int tmp2 = ask(valid2[m + 1][0], valid2[m + 1][1]);
        if (tmp1 < tmp2) {
            ans = m;
            l = m + 1;
        } else if (tmp1 > tmp2) {
            r = m - 1;
        } else {
            int tmp3 = ask(valid2[m][0], n);
            if (tmp3 > tmp1) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
    }

    int res = ask(valid2[ans + 1][0], valid2[ans + 1][1]);
    out(res);
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}