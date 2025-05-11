#include <bits/stdc++.h>
#include <cstdio>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }
    
    i64 ans = std::accumulate(a.begin(), a.end(), 0LL);
    
    std::vector<int> f(1 << m);
    f[0] = (1 << 30) - 1;
    for (int s = 1; s < (1 << m); s++) {
        int u = __builtin_ctz(s);
        f[s] = f[s ^ (1 << u)] & b[u];
    }
    
    std::vector<int> h;
    h.reserve(n * m);
    for (int i = 0; i < n; i++) {
        std::vector<int> g(m + 1);
        for (int s = 0; s < (1 << m); s++) {
            int c = __builtin_popcount(s);
            g[c] = std::max(g[c], a[i] - (a[i] & f[s]));
        }
        for (int j = 1; j <= m; j++) {
            h.push_back(g[j] - g[j - 1]);
        }
    }
    std::sort(h.begin(), h.end(), std::greater());
    
    for (int i = 0; i < h.size() && i < k; i++) {
        ans -= h[i];
    }
    
    std::cout << ans << "\n";
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