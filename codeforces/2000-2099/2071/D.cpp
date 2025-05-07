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
    int n;
    cin >> n;
    long long l, r;
    cin >> l >> r;
    vector<int> a(n + 1);
    map<long long, int> dp;
    vector<int> xor_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp[i] = a[i];
        xor_sum[i] = xor_sum[i - 1] ^ a[i];
    }
    function<int(long long)> work = [&](long long idx) -> int {
        if (dp.count(idx)) return dp[idx];
        // idx > n
        // a1 ^ a2 ^ a3 ^ ... a ^ (idx / 2)
        if (idx / 2 <= n) {
            return xor_sum[idx / 2];
        }

        // idx / 2 > n
        // n 是偶数的话 n + 1, (n + 2, n + 3), (n + 4, n + 5)
        // n 是奇数的话 (n + 1, n + 2), (n + 3, n + 4)
        long long idx2 = idx / 2;
        int res = xor_sum[n];
        if (n % 2 == 0) {
            if (idx2 % 2 == 0) {
                // 需要算
                res ^= work(n + 1) ^ work(idx2);
            } else {
                res ^= work(n + 1);
            }
        } else {
            if (idx2 % 2 == 0) {
                res ^= work(idx2);
            } else {
                
            }
        }
        return dp[idx] = res;
    };

    cout << work(l) << '\n';
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