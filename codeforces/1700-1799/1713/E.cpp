#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct DSU {
    std::vector<int> f, g;
    DSU(int n) : f(n), g(n) { std::iota(f.begin(), f.end(), 0); }
    std::array<int, 2> leader(int x) {
        if (f[x] == x) {
            return {x, 0};
        }
        auto [y, z] = leader(f[x]);
        f[x] = y;
        g[x] ^= z;
        return {f[x], g[x]};
    }
    bool merge(int a, int b, int z) {
        auto [x, u] = leader(a);
        auto [y, v] = leader(b);
        if (x == y) {
            return (u ^ v ^ z) == 0;
        }
        f[x] = y;
        g[x] = u ^ v ^ z;
        return true;
    }
};

void solve() {
    int n;
    std::cin >> n;

    std::vector a(n, std::vector<int>(n));
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i][j] == a[j][i]) {
                continue;
            }
            dsu.merge(i, j, a[i][j] > a[j][i]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i][j] == a[j][i]) continue;
            auto [f, flag1] = dsu.leader(i);
            auto [f2, flag2] = dsu.leader(j);

            if ((flag1 ^ flag2)) {
                if (a[i][j] > a[j][i]) {
                    swap(a[i][j], a[j][i]);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    freopen("data.in", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
