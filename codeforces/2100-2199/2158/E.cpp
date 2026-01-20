#include <bits/stdc++.h>

#include "structure/union-find/union-find.hpp"

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
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> node(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            node[i][j] = i * m + j;
        }
    }

    int q;
    cin >> q;
    const int N = n * m + q;
    UnionFind uf(N);

    int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                int i2 = i + d[k][0], j2 = j + d[k][1];
                if (i2 >= 0 && i2 < n && j2 >= 0 && j2 < m && a[i2][j2] == a[i][j]) {
                    uf.unite(node[i][j], node[i2][j2]);
                }
            }
        }
    }

    vector<int> in(N);
    int now_node = n * m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                int i2 = i + d[k][0], j2 = j + d[k][1];
                if (i2 >= 0 && i2 < n && j2 >= 0 && j2 < m && a[i][j] < a[i2][j2]) {
                    in[uf.find(node[i2][j2])]++;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int fa = uf.find(node[i][j]);
            if (fa == node[i][j] && in[fa] == 0) {
                ans++;
            }
        }
    }
    cout << ans << '\n';

    while (q--) {
        int r, c, x;
        cin >> r >> c >> x;
        r--, c--;

        set<int> S;
        S.insert(uf.find(node[r][c]));
        for (int i = 0; i < 4; i++) {
            int r2 = r + d[i][0], c2 = c + d[i][1];
            if (r2 >= 0 && r2 < n && c2 >= 0 && c2 < m) {
                S.insert(uf.find(node[r2][c2]));
            }
        }
        for (auto it : S) {
            if (in[it] == 0) ans--;
        }

        for (int i = 0; i < 4; i++) {
            int r2 = r + d[i][0], c2 = c + d[i][1];
            if (r2 >= 0 && r2 < n && c2 >= 0 && c2 < m && a[r][c] != a[r2][c2]) {
                if (a[r][c] < a[r2][c2]) {
                    in[uf.find(node[r2][c2])]--;
                } else {
                    in[uf.find(node[r][c])]--;
                }
            }
        }

        a[r][c] -= x;
        node[r][c] = now_node++;

        for (int i = 0; i < 4; i++) {
            int r2 = r + d[i][0], c2 = c + d[i][1];
            if (r2 >= 0 && r2 < n && c2 >= 0 && c2 < m && a[r][c] == a[r2][c2]) {
                int fa1 = uf.find(node[r][c]);
                int fa2 = uf.find(node[r2][c2]);
                in[fa2] += in[fa1];
                uf.unite(fa1, fa2);

                // uf.unite(node[r][c], node[r2][c2]);
            }
        }
        for (int i = 0; i < 4; i++) {
            int r2 = r + d[i][0], c2 = c + d[i][1];
            if (r2 >= 0 && r2 < n && c2 >= 0 && c2 < m && a[r][c] != a[r2][c2]) {
                if (a[r][c] < a[r2][c2]) {
                    in[uf.find(node[r2][c2])]++;
                } else {
                    in[uf.find(node[r][c])]++;
                }
            }
        }

        S.clear();

        S.insert(uf.find(node[r][c]));
        for (int i = 0; i < 4; i++) {
            int r2 = r + d[i][0], c2 = c + d[i][1];
            if (r2 >= 0 && r2 < n && c2 >= 0 && c2 < m) {
                S.insert(uf.find(node[r2][c2]));
            }
        }

        for (auto it : S) {
            if (in[it] == 0) {
                ans++;
            }
        }
        cout << ans << '\n';
    }
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