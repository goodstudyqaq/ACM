#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        int one_cnt = count_if(s.begin(), s.end(), [&](char it) { return it == '1'; });
        if (1LL * one_cnt * m % n) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> sum(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            sum[i] = (s[i % n] == '1');
            if (i != 0) {
                sum[i] += sum[i - 1];
            }
        }

        int equ = 1LL * one_cnt * m / n;
        for (int i = m - 1; i < 2 * n; i++) {
            int l = i - m + 1;
            int val = sum[i];
            if (l != 0) {
                val -= sum[l - 1];
            }
            if (val == equ) {
                if (i < n) {
                    cout << 1 << '\n';
                    cout << l + 1 << ' ' << i + 1 << '\n';
                } else {
                    cout << 2 << '\n';
                    cout << 1 << ' ' << i % n + 1 << '\n';
                    cout << l + 1 << ' ' << n << '\n';
                }
                break;
            }
        }
    }
}