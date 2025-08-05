#include <bits/stdc++.h>

#include <cassert>
#include <numeric>

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

vector<int> base;
vector<int> pre_sum_base;
const int step = 13;
void init() {
    base.push_back(1);
    int sum = 1;

    int now = 2;
    while (base.size() < step) {
        int have = now * (now + 1) / 2;

        if (have > sum) {
            base.push_back(now);
            sum += have;
        }
        now++;
    }
    pre_sum_base.resize(step);
    for (int i = 0; i < step; i++) {
        pre_sum_base[i] = base[i];
        if (i) pre_sum_base[i] += pre_sum_base[i - 1];
    }
    debug(base);
    int sum2 = accumulate(base.begin(), base.end(), 0);
    debug(sum2 * 2 + base.size());
}
void solve() {
    int n;
    cin >> n;
    int ask_num = 0;
    const int limit = 100;
    auto ask = [&](vector<int> &idx) {
        ask_num++;
        assert(ask_num <= limit);
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
        ask_num++;
        assert(ask_num <= limit);
        cout << "? " << r - l + 1;
        for (int i = l; i <= r; i++) {
            cout << " " << i;
        }
        cout << endl;
        long long ans;
        cin >> ans;
        return ans;
    };

    auto out = [&](vector<int> &res) {
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
    auto out2 = [&](int res) {
        cout << "! ";
        for (int i = 0; i < res; i++) {
            cout << ')';
        }
        for (int i = 0; i < n - res; i++) {
            cout << '(';
        }
        cout << endl;
    };



    long long ans = ask_range(1, n);

    if (ans == 0) {
        // [2, n]
        int l = 2, r = n;
        int res = -1;
        vector<int> idx(2);
        idx[1] = 1;
        while (l <= r) {
            int m = l + r >> 1;
            idx[0] = m;
            auto ans = ask(idx);
            if (ans > 0) {
                res = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        out2(res - 1);
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
            int sum = pre_sum_base[sz - 1];
            cout << "? " << sum * 2 + sz;
            for (int i = 0; i < sz; i++) {
                int len = base[i];
                for (int j = 0; j < len; j++) {
                    cout << ' ' << l + i << ' ' << ans + 1;
                }
                cout << ' ' << ans + 1;
            }
            cout << endl;
            int res;
            cin >> res;
            for (int i = sz - 1; i >= 0; i--) {
                int val = base[i] * (base[i] + 1) / 2;
                if (res >= val) {
                    result[l + i - 1] = 0;
                    res -= val;
                } else {
                    result[l + i - 1] = 1;
                }
            }
        };

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
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}