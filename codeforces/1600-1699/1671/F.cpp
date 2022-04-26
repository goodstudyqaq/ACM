#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;
const int N = 20;
struct BIT {
    int n, c[N];
    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; ++i) c[i] = 0;
    }
    int lowbit(int x) { return x & (-x); }
    void update(int i, int x) {
        while (i <= n) {
            c[i] += x;
            i += lowbit(i);
        }
    }
    int query(int i) {
        int ret = 0;
        while (i) {
            ret += c[i];
            i -= lowbit(i);
        }
        return ret;
    }
} bit;

vector<vector<vector<int>>> cnt;
int len;

vector<int> premax, sufmin;
vector<int> vis, p;
const int INF = 200;
void dfs(int u, int curk, int curx) {
    if ((curk > 11) || (curx > 11)) return;
    if (u == len + 1) {
        premax[0] = 0;
        sufmin[len + 1] = INF;
        for (int i = 1; i <= len; ++i) premax[i] = max(premax[i - 1], p[i]);
        for (int i = len; i >= 1; --i) sufmin[i] = min(sufmin[i + 1], p[i]);
        for (int i = 1; i <= len - 1; ++i)
            if (premax[i] < sufmin[i + 1]) return;
        // for (int i = 1;i <= len;++i) cout << p[i] << " "; cout << ": " << curk << ' ' << curx << endl;
        cnt[len][curx][curk]++;
        return;
    }

    for (int i = 1; i <= len; ++i)
        if (vis[i] == 0) {
            if ((u == 1) && (i == 1)) continue;
            if ((u == len) && (i == len)) continue;
            vis[i] = 1;
            bit.update(i, 1);

            p[u] = i;
            dfs(u + 1, curk + (i - bit.query(i)), curx + ((u >= 2) && (p[u - 1] > p[u])));

            vis[i] = 0;
            bit.update(i, -1);
        }
}

void get_table() {
    cnt = vector(13, vector(12, vector(12, 0)));
    premax.resize(14);
    sufmin.resize(14);
    vis.resize(14);
    p.resize(14);
    for (len = 2; len <= 12; len++) {
        bit.init(len);
        for (int i = 0; i < 14; i++) p[i] = 0;
        dfs(1, 0, 0);
    }
}

const int mod = 998244353;
vector<vector<vector<vector<int>>>> dp;
vector<int> inv;

int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) {
            res = 1LL * res * a % mod;
        }
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}

void init() {
    dp = vector(12, vector(23, vector(12, vector(12, 0))));
    dp[0][0][0][0] = 1;
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 22; j++) {
            for (int a = 0; a <= 11; a++) {
                for (int b = 0; b <= 11; b++) {
                    if (dp[i][j][a][b] == 0) continue;
                    for (int k = 2; k + j <= 22 && k <= 12; k++) {
                        for (int p = 0; p + a <= 11; p++) {
                            for (int q = 0; q + b <= 11; q++) {
                                int& nw = dp[i + 1][k + j][p + a][q + b];
                                nw = (nw + 1LL * dp[i][j][a][b] * cnt[k][p][q] % mod) % mod;
                            }
                        }
                    }
                }
            }
        }
    }

    inv.resize(12);
    for (int i = 1; i <= 11; i++) {
        inv[i] = quick(i, mod - 2);
    }
}

long long C(long long a, long long b) {
    long long res = 1;
    for (int i = 0; i < b; i++) {
        res = res * (a - i) % mod;
        res = res * inv[b - i] % mod;
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
    // freopen("./data.out", "w", stdout);
#endif
    get_table();
    init();
    int T;
    cin >> T;
    while (T--) {
        int n, k, x;
        cin >> n >> k >> x;
        int ans = 0;
        for (int i = 1; i <= 11; i++) {
            for (int j = i; j <= 22 && n >= j; j++) {
                ans = (ans + 1LL * dp[i][j][x][k] % mod * C(n - j + i, i) % mod) % mod;
            }
        }
        cout << ans << endl;
    }
    return 0;
}