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
    int n;
    cin >> n;

    map<int, ll> cache;
    int ask_times = 0;

    auto ask = [&](int r) {
        if (cache.count(r)) {
            return cache[r];
        }
        if (r == 0) return 0LL;
        ask_times++;
        cout << "? 1 " << r << '\n';
        fflush(stdout);
        ll res;
        cin >> res;
        cache[r] = res;
        return res;
    };

    auto out = [&](ll ans) {
        cout << "! " << ans << '\n';
        fflush(stdout);
    };

    auto ask_range = [&](int l, int r) {
        return ask(r) - ask(l - 1);
    };

    int l = 1, r = n;

    auto get_mid = [&](int L, int R, ll res) {
        int l = L, r = R - 1;
        ll need = res / 2;  // res 有没有可能是奇数？？？
        while (l <= r) {
            int m = l + r >> 1;
            ll tmp = ask_range(L, m);
            if (tmp == need) {
                return m;
            } else if (tmp > need) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return -1;
    };

    while (l <= r) {
        debug(l, r);
        ll res = ask_range(l, r);
        if (l == r) {
            out(res);
            return;
        }

        int m = get_mid(l, r, res);

        int len1 = m - l + 1;
        int len2 = r - m;
        if (len1 <= len2) {
            r = m;
        } else {
            l = m + 1;
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