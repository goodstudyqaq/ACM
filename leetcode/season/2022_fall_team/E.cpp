#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC optimize("no-stack-protector,fast-math")

#include <bits/stdc++.h>

using namespace std;

static constexpr int N = 1e5 + 7;
constexpr int M = 998244353;

#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define int long long
#define ll long long
#define pii pair<int, int>
#define cpii const pair<int, int>&
#define fi first
#define se second
#define SZ(x) ((int)(x.size()))

#ifdef int
#define INF 0x3f3f3f3f3f3f3f3f
#define INF2 (int)(0xcfcfcfcfcfcfcfcf)
#else
#define INF 0x3f3f3f3f
#define INF2 0xcfcfcfcf
#endif

//#include <atcoder/all>

// using namespace atcoder;

// using mint = modint998244353;

signed main() {
    fastio int ans = INF;
    vector<pii> ps[2] = {
        {pii{0, -1}, {-1, 0}, {0, 1}},
        {pii{0, -1}, {1, 0}, {0, 1}}};
    auto f = [&](int n, bool print) {
        ;
        for (int mask = 0; mask < (1 << n * n); mask++) {
            vector<vector<int>> a(n, vector<int>(n * 2 + 1));
            vector<vector<int>> need(n, vector<int>(n * 2 + 1, 2));
            queue<pii> q;
            int tot = 0;
            int cost = 0;
            for (int i = 0; i < n; i++) {
                for (int l = n - 1, r = n - 1; r <= n - 1 + i && l >= n - 1 - i; l--, r++) {
                    if (mask >> tot & 1) {
                        a[i][l] = 1;
                        cost++;
                        q.emplace(i, l);
                        need[i][l] = 0;
                    }
                    tot++;
                    if (l != r) {
                        if (mask >> tot & 1) {
                            a[i][r] = 1;
                            cost++;
                            q.emplace(i, r);
                            need[i][r] = 0;
                        }
                        tot++;
                    }
                }
            }
            assert(tot == n * n);
            int vis = cost;
            while (!q.empty()) {
                auto [i, j] = q.front();
                q.pop();
                for (pii p : ps[(i + j) % 2 == (n - 1) % 2]) {
                    int i2 = i + p.fi;
                    int j2 = j + p.se;
                    if (i2 < 0 || i2 >= n || j2 < n - 1 - i2 || j2 > n - 1 + i2) continue;
                    need[i2][j2]--;
                    if (need[i2][j2] == 0) {
                        vis++;
                        q.emplace(i2, j2);
                        a[i2][j2] = 2;
                    }
                }
            }
            if (vis == n * n) {
                ans = min(ans, cost);
                if (ans == cost && print) {
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < 2 * n - 1; j++) {
                            cout << a[i][j] << " ";
                        }
                        cout << "\n";
                    }
                    break;
                }
            }
        }
    };
    f(6, false);
    cout << ans << endl;
    f(6, true);
    return 0;
}
#pragma clang diagnostic pop