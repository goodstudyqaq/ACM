#include <bits/stdc++.h>

#include <utility>

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
struct DSU {
    std::vector<int> f;
    std::vector<int> cnt;
    DSU(int n) : f(n), cnt(n) {
        std::iota(f.begin(), f.end(), 0);
        for (int i = 0; i < n; i++) cnt[i] = 1;
    }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        cnt[y] += cnt[x];
        return true;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

    auto get_idx = [&](int x, int y) {
        return x * m + y;
    };
    vector<int> sum(n), sum2(m);

    DSU dsu(n * m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '#') {
                sum[i]++;
                sum2[j]++;
                for (int k = 0; k < 4; k++) {
                    int i2 = i + d[k][0], j2 = j + d[k][1];
                    if (i2 >= 0 && i2 < n && j2 >= 0 && j2 < m && s[i2][j2] == '#') {
                        int idx1 = get_idx(i, j);
                        int idx2 = get_idx(i2, j2);
                        dsu.merge(idx1, idx2);
                    }
                }
            }
        }
    }

    int ans = 0;
    set<int> status;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '#') {
                int idx = get_idx(i, j);
                int fidx = dsu.leader(idx);
                status.insert(fidx);
                ans = max(ans, dsu.cnt[fidx]);
            }
        }
    }
    debug(ans);

    for (int i = 0; i < n; i++) {
        sum[i] = m - sum[i];
    }
    for (int i = 0; i < m; i++) {
        sum2[i] = n - sum2[i];
    }
    debug(sum, sum2);

    vector<set<int>> vis(n), vis2(m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '#') {
                int leader = dsu.leader(get_idx(i, j));

                for (int k = -1; k <= 1; k++) {
                    int i2 = i + k;
                    if (i2 >= 0 && i2 < n) {
                        if (vis[i2].count(leader) == 0) {
                            vis[i2].insert(leader);
                            sum[i2] += dsu.cnt[leader];
                        }
                    }
                    int j2 = j + k;
                    if (j2 >= 0 && j2 < m) {
                        if (vis2[j2].count(leader) == 0) {
                            vis2[j2].insert(leader);
                            sum2[j2] += dsu.cnt[leader];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int tmp = sum[i];
        // debug(i, j, sum[i], sum2[j], sum3[i][j], tmp);
        ans = max(ans, tmp);
    }
    for (int i = 0; i < m; i++) {
        int tmp = sum2[i];
        ans = max(ans, tmp);
    }

    cout << ans << endl;
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