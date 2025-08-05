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

void solve() {
    int n;
    cin >> n;
    auto ask = [&](vector<int> &idx) {
        cout << "? " << idx.size();
        for (auto it : idx) {
            cout << " " << it;
        }
        cout << endl;
        long long ans;
        cin >> ans;
        return ans;
    };

    auto ask_range = [&](int l, int r) {
        cout << "? " << r - l + 1;
        for (int i = l; i <= r; i++) {
            cout << " " << i;
        }
        cout << endl;
        long long ans;
        cin >> ans;
        return ans;
    };

    auto out = [&](vector<int> res) {
        cout << "! ";
        for (auto it : res) {
            if (it == 0) {
                cout << '(';
            } else {
                cout << ')';
            }
        }
        cout << endl;
    };

    long long ans = ask_range(1, n);

    if (ans == 0) {
        // [2, n]
        int l = 2, r = n;
        int res = -1;
        while (l <= r) {
            int m = l + r >> 1;
            vector<int> idx;
            idx.push_back(m);
            idx.push_back(1);
            auto ans = ask(idx);
            if (ans > 0) {
                res = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        vector<int> result(n);
        for (int i = 1; i < res; i++) {
            result[i - 1] = 1;
        }
        for (int i = res; i <= n; i++) {
            result[i - 1] = 0;
        }
        out(result);

    } else {
        int l = 1, r = n;
        int ans = -1;
        while (l <= r) {
            int m = l + r >> 1;

            auto a1 = ask_range(l, m);

            if (a1 > 0) {
                r = m;
                continue;
            }

            auto a2 = ask_range(m + 1, r);
            if (a2 > 0) {
                l = m + 1;
                continue;
            }
            ans = m;
            break;
        }
        debug(ans);

        vector<int> result(n);

        auto work = [&](int l, int r) {
            int sz = r - l + 1;
            cout << "? " << ((1 << sz) - 1) * 3;
            for (int i = 0; i < sz; i++) {
                int len = (1 << i);
                for (int j = 0; j < len; j++) {
                    cout << ' ' << l + i << ' ' << ans + 1 << ' ' << ans + 1;
                }
            }
            cout << endl;
            int res;
            cin >> res;

            for (int i = 0; i < sz; i++) {
                if ((res >> i) & 1) {
                    result[l + i - 1] = 0;
                } else {
                    result[l + i - 1] = 1;
                }
            }
        };

        const int step = 8;
        for (int i = 1; i <= n; i += step) {
            int r = min(i + step - 1, n);
            work(i, r);
        }
        out(result);
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