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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m;
    cin >> n >> m;
    /*
        计算一个数组的贡献也很困难，所以要换个思路。
        考虑最后 remove 的 token 有哪些，然后针对一个删掉的 token 计算有多少个数组对此有贡献。-> 一个新思路(正难则反)

        假设删掉的 token 为 t, 那么它一定是在[t, n] 中的一个位置删掉的，并且该位置上的值一定是小于等于 t 的。-> 合理。
        设 dp[i][j] 表示 从 n 到 i (从右到左) 删掉的个数为 j 个的方案。
        dp[i][j] = dp[i + 1][j]
        dp[i][j] = dp[i + 1][j - 1] * (n - i + 1 - j) * i
    */
    vector<long long> dp(n + 1);
    dp[0] = 1;
    for (int i = n; i >= 1; i--) {
        vector<long long> ndp(n + 1);
        for (int j = 0; j <= n - i + 1; j++) {
            (ndp[j] += dp[j]) %= m;
            if (j > 0) {
                (ndp[j] += dp[j - 1] * (n - i + 1 - j + 1) % m * i % m) %= m;
            }
        }

        dp = ndp;
    }

    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        (ans += dp[i]) %= m;
    }
    cout << ans << '\n';
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
    return 0;
}