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

    auto ask_throw = [&](int idx) {
        cout << "throw " << idx << '\n';
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    auto ask_swap = [&](int idx) {
        cout << "swap " << idx << '\n';
        fflush(stdout);
    };

    vector<int> ans(n + 1, -1);

    vector<int> jump(n + 1);

    jump[n] = 1;
    jump[n - 1] = ask_throw(n - 1);

    // 用 n / 2 次
    for (int i = n - 2; i >= 1; i--) {
        if (jump[i + 1] == jump[i + 2]) {
            jump[i] = jump[i + 1] + 1;
        } else {
            jump[i] = ask_throw(i);
        }
    }

    // 确定 n / 2 个点的值
    for (int i = n - 1; i >= 1; i--) {
        if (i == n - 1) {
            if (jump[i] == 1) {
                ans[i] = 2;
            } else {
                ans[i] = 1;
            }
        } else {
            if (jump[i + 1] != jump[i + 2]) {
                if (jump[i] == jump[i + 1] + 1) {
                    ans[i] = 1;
                } else {
                    ans[i] = 2;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i == n) {
            ask_swap(n - 1);
            int val = ask_throw(n - 1);
            if (val == 1) {
                ans[n] = 2;
            } else {
                ans[n] = 1;
            }
        } else {
            if (ans[i] == -1) {
                ask_swap(i);
                int val = ask_throw(i + 1);
                if (val == jump[i + 2] + 1) {
                    ans[i] = 1;
                } else {
                    ans[i] = 2;
                }
            }
        }
    }

    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    fflush(stdout);
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