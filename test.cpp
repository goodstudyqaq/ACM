#include <bits/stdc++.h>

#include <cstdio>

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

void solve() {
    int n, k;
    cin >> n >> k;
    auto ask = [&](int idx) {
        cout << "? " << idx << '\n';
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };
    auto out1 = [&]() {
        cout << "! -1" << endl;
        fflush(stdout);
    };
    auto out2 = [&](int l, int r) {
        cout << "! " << l << ' ' << r << endl;
        fflush(stdout);
    };

    vector<int> pre(k + 1);
    for (int i = 1; i <= k; i++) {
        pre[i] = ask(i);
    }

    vector<int> suf(k + 1);
    for (int i = 1; i <= k; i++) {
        suf[i] = ask(n - k + i);
    }

    bool eq = true;
    int idx = -1;
    for (int i = 1; i <= k; i++) {
        if (pre[i] != suf[i]) {
            idx = i;
            eq = false;
            break;
        }
    }
    if (eq) {
        if (n == 2 * k) {
            out2(k, k);
        } else {
            out1();
        }
        return;
    }

    int t = (n - 1) / k + 1;

    // [2, t - 1]

    int l = 2, r = t - 1;
    int ans = -1;
    while (l <= r) {
        int m = l + r >> 1;
        int idx2 = (m - 1) * k + idx;
        int val = ask(idx2);
        if (val == pre[idx]) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    int start = (ans - 1) * k + idx + 1;
    int end = ans * k;
    for (int i = start; i <= end; i++) {
        int val = ask(i);
        if (val != pre[i - (ans - 1) * k]) {
            out2(i, n - i);
            return;
        }
    }
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