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

    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
        idx[i] = i + 1;
    }
    long long ans = ask(idx);

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
            auto a2 = ask_range(m + 1, r);

            if (a1 > 0) {
                r = m;
            } else if (a2 > 0) {
                l = m + 1;
            } else {
                ans = m;
                break;
            }
        }

        // s[ans] = '(' s[ans + 1] = ')'
        vector<int> idx(8);

        idx[1] = ans + 1;
        idx[2] = ans + 1;
        idx[4] = ans + 1;
        idx[5] = ans + 1;
        idx[7] = ans + 1;
        vector<int> result(n);

        for (int i = 1; i <= n; i += 2) {
            if (i + 1 <= n) {
                idx[0] = i;
                idx[3] = i + 1;
                idx[6] = i;
                auto res = ask(idx);
                if (res == 0) {
                    result[i - 1] = result[i] = 1;
                } else if (res == 1) {
                    result[i - 1] = 1;
                    result[i] = 0;
                } else if (res == 2) {
                    result[i - 1] = 0;
                    result[i] = 1;
                } else {
                    result[i - 1] = result[i] = 0;
                }
            } else {
                vector<int> tmp;
                tmp.push_back(i);
                tmp.push_back(ans + 1);
                auto res = ask(tmp);
                if (res == 1) {
                    result[i - 1] = 0;
                } else {
                    result[i - 1] = 1;
                }
            }
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