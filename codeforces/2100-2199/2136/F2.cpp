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

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void table2() {
    const int MAXN = 2.5e4;
    const int MAXB = 1e3;
    const int MAXW = 1e5;
    for (int n = 1; n <= MAXN; n++) {
        for (int b = 1; b <= MAXB; b++) {
            n = 80;
            b = 157;
            // 首先来 n 个 b
            // 1. res = 0 -> w < b -> 用 b^2 个 1
            if (n + b * b > MAXN) continue;
            // 2. w >= b

            int last_val = -1;
            int cnt = 0;
            int mx_cnt = 0;
            int mx_val = -1;
            for (int w = b; w <= MAXW; w++) {
                int tmp = w / b;
                int tmp2 = (n + tmp - 1) / tmp;
                if (last_val == tmp2) {
                    cnt++;
                } else {
                    cnt = 1;
                }
                if (mx_cnt < cnt) {
                    mx_cnt = cnt;
                    mx_val = tmp2;
                }
                last_val = tmp2;
            }
            debug(mx_cnt, mx_val);
        }
    }
}

void table() {
    const int MAXN = 2.5e4;
    const int MAXB = 1e3;
    const int MAXW = 1e5;
    for (int n = 1; n <= MAXN; n++) {
        for (int b = 1; b <= MAXB; b++) {
            // n = 11343;
            // b = 116;
            // 首先来 n 个 b
            // 1. res = 0 -> w < b -> 用 b^2 个 1
            if (n + b * b > MAXN) continue;
            // 2. w >= b
            int tmp_l = 1, tmp_r = MAXW / b;
            // tmp \in [tmp_l, tmp_r]
            // n / tmp 向上取整

            int mi_r = (n + tmp_r - 1) / tmp_r;
            if (mi_r == 1) {
                continue;
            }

            while (true) {
                int L = b * (n - 1 + mi_r) / mi_r;
                int R = b * (n - 1 + mi_r - 1 - 1) / (mi_r - 1) - 1;
                if (L <= MAXW) break;
                mi_r++;
            }
            int L = b * ((n - 1 + mi_r) / mi_r);
            int R = min(MAXW, b * ((n - 1 + mi_r - 1) / (mi_r - 1)) - 1);
            int len = R - L + 1;

            mi_r++;
            L = b * ((n - 1 + mi_r) / mi_r);
            R = min(MAXW, b * ((n - 1 + mi_r - 1) / (mi_r - 1)) - 1);
            len = max(len, R - L + 1);

            if (len * 2 + n <= MAXN) {
                debug(n, b, len, L, R, mi_r, R - L + 1);
                return;
            }
        }
    }
}

void solve() {
    auto ask = [&](const vector<int> &v) {
        cout << "? " << v.size();
        for (auto a : v) {
            cout << " " << a;
        }
        cout << '\n';
        fflush(stdout);
        int l;
        cin >> l;
        return l;
    };
    auto out = [&](int w) {
        cout << "! " << w << '\n';
        fflush(stdout);
    };
    int n = 5896;
    int b = 138;
    vector<int> v1(n, b);
    int ans1 = ask(v1);

    if (ans1 == 0) {
        // w < b
        n = b * b;
        vector<int> v2(n, 1);
        int ans2 = ask(v2);

        for (int w = 1; w < b; w++) {
            int l = (n + w - 1) / w;
            if (l == ans2) {
                out(w);
                return;
            }
        }
    } else {
        // w >= b
        // [L, R]

        const int MAXW = 1e5;
        int L = b * ((n - 1 + ans1) / ans1);
        int R = ans1 == 1 ? MAXW : min(MAXW, b * ((n - 1 + ans1 - 1) / (ans1 - 1)) - 1);

        vector<int> v2;
        for (int i = L + 1; i <= R; i++) {
            v2.push_back(L);
            v2.push_back(i - L);
        }
        int ans2 = ask(v2);
        int len = R - L;
        // 小于等于 w 的可以放 1 行，后面的就是一次放一行

        // w - L + (R - w) * 2 = ans2
        int w = -(ans2 + L - R * 2);
        out(w);
    }
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    table();

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}