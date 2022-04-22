#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        string res = s;

        int now = 0;
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            if (k % 2) {
                if (s[i] == '1') {
                    if (now < k) {
                        now++;
                        ans[i] = 1;
                    } else {
                        res[i] = '0';
                    }
                } else {
                    res[i] = '1';
                }
            } else {
                if (s[i] == '0') {
                    if (now < k) {
                        now++;
                        ans[i] = 1;
                        res[i] = '1';
                    }
                }
            }
        }
        if (now < k) {
            int tmp = k - now;
            ans[n - 1] += tmp;
            if (tmp % 2) {
                res[n - 1] = '0';
            }
        }
        cout << res << endl;
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    return 0;
}