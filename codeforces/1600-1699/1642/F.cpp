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

// https://codeforces.com/blog/entry/45223
/*
    F[mask] = \sum_{i \in mask} A[i]
    Time: O(N2^N)
*/

const int N = 16;
const int LIMIT = 1 << N;
const int maxn = 1e5 + 5;

int dp[LIMIT][N + 1];
int F[LIMIT];
int a[maxn][6];
int x[maxn * 5];
int x_cnt;
int status[LIMIT];
const int INF = inf<int>;
int id[maxn * 5];

int iterative_version(int N) {
    //iterative version
    for (int mask = 0; mask < (1 << N); ++mask) {
        dp[mask][0] = status[mask];  //handle base case separately (leaf states)
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                dp[mask][i + 1] = min(dp[mask][i], dp[mask ^ (1 << i)][i]);
            } else {
                dp[mask][i + 1] = dp[mask][i];
            }
        }
        F[mask] = dp[mask][N];
    }

    int ans = 2 * INF;
    for (int i = 1; i < (1 << N); i++) {
        int os = (1 << N) - i - 1;
        if (F[os] == INF || F[i] == INF) continue;
        ans = min(ans, F[os] + F[i]);
    }
    return ans;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            cin >> a[i][j];
            if (j < m) {
                x[x_cnt++] = a[i][j];
            }
        }
    }
    sort(x, x + x_cnt);
    x_cnt = unique(x, x + x_cnt) - x;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = lower_bound(x, x + x_cnt, a[i][j]) - x;
        }
    }

    int sz = x_cnt;

    auto work = [&]() -> int {
        for (int i = 0; i < sz; i++) {
            id[i] = rnd(16);
        }

        for (int i = 0; i < LIMIT; i++) {
            status[i] = INF;
        }

        for (int i = 0; i < n; i++) {
            int s = 0;
            for (int j = 0; j < m; j++) {
                int it = id[a[i][j]];
                s |= (1 << it);
            }
            status[s] = min(status[s], a[i][m]);
        }

        return iterative_version(16);
    };

    int ans = 2 * INF;
    debug(ans);
    for (int t = 1; t <= 250; t++) {
        ans = min(ans, work());
    }
    debug(ans);
    if (ans == 2 * INF) ans = -1;
    cout << ans << endl;
}