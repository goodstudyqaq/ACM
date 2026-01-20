#include <bits/stdc++.h>
 
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
 
using u128 = unsigned __int128;
using i128 = __int128;
 
void solve() {
    i64 l, r;
    std::cin >> l >> r;
    r++;
    
    i64 ans = 0;
    for (i64 i = 1; i < (1LL << 60); i *= 2) {
        if (l % (2 * i) == 0 && r % (2 * i) == 0) {
            ans += i;
        } else if (l / (2 * i) == r / (2 * i) && (l + r) % (2 * i) == 0) {
            ans += l & -l;
        }
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