#include <bits/stdc++.h>

#include <algorithm>
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

    const int n = 1e5;
    vector<int> v(n, 1);
    int ans1 = ask(v);

    if (ans1 == 1) {
        out(n);
        return;
    }

    int L = (n + ans1 - 1) / ans1;
    int R = n / (ans1 - 1);
    debug(L, R);
    if (L == R) {
        out(L);
        return;
    }
    // [L, R]
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