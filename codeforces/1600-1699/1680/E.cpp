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

void solve() {
    int n;
    cin >> n;
    vector<string> s(2);
    cin >> s[0] >> s[1];

    int real_L = n + 1, real_R = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            if (s[j][i] == '*') {
                real_L = min(real_L, i);
                real_R = max(real_R, i);
            }
        }
    }

    auto work = [&](int L, int R) -> int {
        vector dp = vector(n + 1, vector(2, n * 20));
        dp[L][0] = dp[L][1] = 0;
        if (s[0][L] == '*') {
            dp[L][1] = 1;
        }
        if (s[1][L] == '*') {
            dp[L][0] = 1;
        }

        for (int i = L + 1; i <= R; i++) {
            for (int j = 0; j < 2; j++) {
                int other = 1 - j;
                int flag = 0;
                if (s[other][i] == '*') {
                    flag = 1;
                }
                for (int k = 0; k < 2; k++) {
                    int tmp;
                    if (k == j) {
                        tmp = flag + dp[i - 1][k] + 1;
                    } else {
                        tmp = dp[i - 1][k] + 2;
                    }
                    dp[i][j] = min(dp[i][j], tmp);
                }
            }
        }
        return min(dp[R][0], dp[R][1]);
    };

    cout << work(real_L, real_R) << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}