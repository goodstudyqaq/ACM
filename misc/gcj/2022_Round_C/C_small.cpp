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

const int mod = 1e9 + 7;
const int maxn = 51;

long long quick(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b % 2) res = res * a % mod;
        b /= 2;
        a = a * a % mod;
    }
    return res;
}

vector<long long> A, B;
void init() {
    A.resize(maxn);
    B.resize(maxn);
    A[0] = 1;
    for (int i = 1; i < maxn; i++) {
        A[i] = A[i - 1] * i % mod;
    }
    B[maxn - 1] = quick(A[maxn - 1], mod - 2);
    for (int i = maxn - 2; i >= 0; i--) {
        B[i] = B[i + 1] * (i + 1) % mod;
    }
}

int C(int n, int m) {
    if (n < m) return 0;
    return A[n] * B[m] % mod * B[n - m] % mod;
}

void solve() {
    int N, K;
    cin >> N >> K;

    int m = N * (N - 1) / 2;

    vector dp = vector(m + 1, vector(N + 1, vector(K + 1, 0)));
    dp[0][0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k <= K; k++) {
                if (dp[i][j][k] == 0) continue;
                // debug(i, j, k, dp[i][j][k]);
                // u v 都不在点集
                if (j + 2 <= N && k + 1 <= K) {
                    long long tmp = C(N - j, 2);
                    (dp[i + 1][j + 2][k + 1] += (tmp * dp[i][j][k]) % mod) %= mod;
                }

                // u 在 v 不在
                if (j + 1 <= N && j > 0) {
                    long long tmp = C(j, 1) * C(N - j, 1);
                    (dp[i + 1][j + 1][k] += (tmp * dp[i][j][k] % mod)) %= mod;
                }

                // u v 都在
                if (j >= 2 && j * (j - 1) / 2 > i) {
                    long long tmp = C(j, 2) - i;
                    (dp[i + 1][j][k] += (tmp * dp[i][j][k] % mod)) %= mod;
                }
            }
        }
    }

    long long tmp = 1;
    for (int i = 1; i <= m; i++) {
        tmp = tmp * i % mod;
    }
    debug(tmp, dp[m][N][K]);
    long long res = dp[m][N][K] * quick(tmp, mod - 2) % mod;

    cout << res << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}