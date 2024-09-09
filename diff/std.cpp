#include <bits/stdc++.h>

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + a[i];
    }
    
    i64 ans = 0;
    std::map<int, int> cnt;
    for (int l = 0; l < n; l++) {
        for (int r = l + 1; r <= n; r++) {
            ans += r - l + 1;
            ans -= 2 * ++cnt[pre[l] + pre[r]];
        }
    }
    for (int i = 0; i <= n; i++) {
        ans -= cnt[2 * pre[i]];
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}