#include <bits/stdc++.h>
#include <cstdio>

using i64 = long long;
using u32 = unsigned;

u32 P;
void inc(u32 &a, u32 b) {
    a += b;
    if (a >= P) {
        a -= P;
    }
}

void solve() {
    int n, k;
    std::cin >> n >> k >> P;

    std::vector f(n + 1, std::vector<u32>(k + 1));
    std::vector g(n + 1, std::vector<u32>(k + 1));
    for (int i = 0; i <= k; i++) {
        f[1][i] = 1;
        g[1][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int a = 0; a <= k; a++) {
            for (int b = 0; a + b <= k; b++) {
                inc(g[i][a + b], 1ULL * g[i - 1][a] * g[i - 1][b] % P);
                if (a > b) {
                    inc(f[i][a + b], 1ULL * f[i - 1][a] * g[i - 1][b] % P);
                }
                if (a < b) {
                    inc(f[i][a + b], 1ULL * g[i - 1][a] * f[i - 1][b] % P);
                }
            }
        }
        for (int a = 1; a <= k; a++) {
            inc(g[i][a], g[i][a - 1]);
            inc(f[i][a], f[i][a - 1]);
        }
    }

    std::cout << f[n][k] << "\n";
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