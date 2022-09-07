#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    int sum_a = 0;
    int sum_b = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        sum_a += a[i];
        sum_b += b[i];
    }
    const int inf = numeric_limits<int>::max() / 2;
    vector dp = vector(n + 1, vector(n + 1, vector(sum_a + 1, -inf)));
    dp[0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int A = 0; A <= sum_a; A++) {
                if (dp[i][j][A] == -inf) continue;
                dp[i + 1][j][A] = max(dp[i + 1][j][A], dp[i][j][A]);
                dp[i + 1][j + 1][A + a[i + 1]] = max(dp[i + 1][j + 1][A + a[i + 1]], dp[i][j][A] + b[i + 1]);
            }
        }
    }

    vector ans = vector(n + 1, 0.0);
    for (int i = 1; i <= n; i++) {
        for (int A = 0; A <= sum_a; A++) {
            if (dp[n][i][A] == -inf) continue;
            ans[i] = max(ans[i], min(1.0 * A, 1.0 * (dp[n][i][A] + sum_b) / 2.0));
        }
        cout << ans[i] << ' ';
    }
    cout << endl;
}