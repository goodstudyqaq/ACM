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
template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

const int maxn = 52;
int mp[maxn][maxn];
int fastest[maxn], slowest[maxn];
bool G[maxn], B[maxn], S[maxn];
long long dp[maxn][maxn][maxn];
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    auto INF = inf<int>;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mp[i][j] = INF;
        }
        mp[i][i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        mp[u][v] = mp[v][u] = c;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            mp[i][j] = mp[i][j] * n + i;
        }
    }

    int g1, g2, s1, s2;
    cin >> g1 >> g2 >> s1 >> s2;

    for (int i = 1; i <= n; i++) {
        fastest[i] = INF;
        slowest[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            fastest[i] = min(fastest[i], mp[i][j]);
            slowest[i] = max(slowest[i], mp[i][j]);
        }
    }

    auto work = [&](int gold_line, int bronze_line, int silver_up, int silver_down) -> long long {
        for (int i = 1; i <= n; i++) {
            G[i] = B[i] = S[i] = false;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) continue;
                G[i] = G[i] | (mp[i][j] <= gold_line);
                B[i] = B[i] | (mp[i][j] >= bronze_line);
                S[i] = S[i] | (mp[i][j] > silver_up && mp[i][j] < silver_down);
            }
        }
        // debug(G);
        // debug(B);
        // debug(S);

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= n; k++) {
                    dp[i][j][k] = 0;
                }
            }
        }

        dp[0][0][0] = 1;
        // debug(dp);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                for (int k = 0; k + j <= i; k++) {
                    if (G[i] && j) {
                        dp[i][j][k] += dp[i - 1][j - 1][k];
                    }
                    if (S[i] && k) {
                        dp[i][j][k] += dp[i - 1][j][k - 1];
                    }
                    if (B[i] && k + j != i) {
                        dp[i][j][k] += dp[i - 1][j][k];
                    }
                }
            }
        }
        long long ans = 0;

        for (int g = g1; g <= g2; g++) {
            for (int s = s1; s <= s2; s++) {
                ans += dp[n][g][s];
            }
        }
        // debug(gold_line, bronze_line, silver_up, silver_down, ans);
        return ans;
    };

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            ans += work(fastest[i], slowest[j], fastest[i], slowest[j]) - work(fastest[i] - 1, slowest[j], fastest[i], slowest[j]) - work(fastest[i], slowest[j] + 1, fastest[i], slowest[j]) + work(fastest[i] - 1, slowest[j] + 1, fastest[i], slowest[j]);
        }
    }
    cout << ans << endl;
    return 0;
}