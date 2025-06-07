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
    int n, k;
    cin >> n >> k;

    vector<int> cache(n, -1);
    auto ask = [&](int idx) {
        if (cache[idx] != -1) {
            return cache[idx];
        }
        cout << "? " << idx + 1 << '\n';
        fflush(stdout);
        int res;
        cin >> res;
        cache[idx] = res;
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
    if (n == 2 * k) {
        out2(k, k);
        return;
    }

    vector<int> pre(k);
    for (int i = 0; i < k; i++) {
        pre[i] = ask(i);
    }

    vector<int> suf(k);
    for (int i = 0; i < k; i++) {
        suf[i] = ask(n - i - 1);
    }

    vector<int> different;
    for (int i = k; i < n - k; i++) {
        int idx1 = i % k;
        int idx2 = (n - i - 1) % k;

        if (pre[idx1] != suf[idx2]) {
            different.push_back(i);
        }
    }

    if (different.size() == 0) {
        out1();
        return;
    }

    int l = 0, r = different.size() - 1;
    int ans = -1;
    while (l <= r) {
        int m = l + r >> 1;
        int idx = different[m];

        int val = ask(idx);

        if (val == pre[idx % k]) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    int R = (ans != different.size() - 1 ? different[ans + 1] : n - k);
    int L = (ans != -1 ? different[ans] : k - 1);

    if (L + 1 == R) {
        out2(L + 1, n - (L + 1));
    } else {
        out1();
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