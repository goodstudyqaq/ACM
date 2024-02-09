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

const int maxn = 3002;
int pre[maxn][maxn][2];
int suf[maxn][maxn][2];
void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) pre[i][j][0] = pre[i][j][1] = suf[i][j][0] = suf[i][j][1] = 0;
    }

    auto sum = vect(0, n + 1, 2);
    for (int i = 0; i < n; i++) {
        sum[i + 1][0] = sum[i][0];
        sum[i + 1][1] = sum[i][1];
        sum[i + 1][s[i] - '0']++;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            for (int p = 0; p < 2; p++) {
                int v = sum[j][p] - sum[i - 1][p];
                if (v <= k) {
                    pre[j][v][p ^ 1] = max(pre[j][v][p ^ 1], j - i + 1);
                    suf[i][v][p ^ 1] = max(suf[i][v][p ^ 1], j - i + 1);
                }
            }
        }
    }

    for (int p = 0; p < 2; p++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                pre[i][j][p] = max(pre[i][j][p], pre[i - 1][j][p]);
                if (j != 0) {
                    pre[i][j][p] = max(pre[i][j][p], pre[i][j - 1][p]);
                }
            }
        }
    }

    for (int p = 0; p < 2; p++) {
        for (int i = n; i >= 1; i--) {
            for (int j = 0; j <= k; j++) {
                if (i != n) {
                    suf[i][j][p] = max(suf[i][j][p], suf[i + 1][j][p]);
                }
                if (j != 0) {
                    suf[i][j][p] = max(suf[i][j][p], suf[i][j - 1][p]);
                }
            }
        }
    }

    vector<int> mx(n + 1, -1);
    vector<int> ans(n + 1);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            int v1 = pre[i][j][0];
            int v2 = (i == n ? 0 : suf[i + 1][k - j][1]);
            mx[v1] = max(mx[v1], v2);
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            int v1 = suf[i][j][0];
            int v2 = (i == 0 ? 0 : pre[i - 1][k - j][1]);
            mx[v1] = max(mx[v1], v2);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (mx[j] == -1) continue;
            ans[i] = max(ans[i], j * i + mx[j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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