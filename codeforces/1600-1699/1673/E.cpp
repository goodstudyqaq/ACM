#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    int n, k;
    cin >> n >> k;
    int LIMIT = 1 << 20;

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<bool> ans(LIMIT);
    int all = n - 1;

    for (int i = 0; i < n; i++) {
        long long now = 1;
        for (int j = i; j < n; j++) {
            if (j == i) {
                now *= b[j];
            } else {
                if (b[j] >= 20) break;
                now *= (1 << b[j]);
            }
            if (now >= LIMIT) break;
            int usea = j - i, useb = 0;
            if (i != 0) {
                useb++;
            }
            if (j != n - 1) {
                useb++;
            }
            int have = all - (usea + useb);

            int need = max(0, k - useb);
            if (need == 0) {
                // 一定是偶数
                if (have == 0) {
                    ans[now] = ans[now] ^ 1;
                }

            } else {
                if (need > have) {
                } else {
                    have--, need--;
                    if ((have | need) == have) {
                        debug(i, j, now);
                        ans[now] = ans[now] ^ 1;
                    }
                }
                // C(have, need) + C(have, need + 1) + ... + C(have, have) 奇偶性
            }
        }
    }
    int start = LIMIT - 1;
    while (start >= 0 && ans[start] == 0) start--;
    if (start == -1) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = start; i >= 0; i--) {
        cout << ans[i];
    }
    cout << endl;
    return 0;
}