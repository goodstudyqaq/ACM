#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
struct DSU {
    std::vector<int> f;
    DSU(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
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
        return true;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    const int LIMIT = 22;
    const int m = 1 << LIMIT;

    vector<int> dp(m, -1);

    for (int i = 0; i < n; i++) dp[a[i]] = a[i];

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < LIMIT; j++) {
            if (((i >> j) & 1) && dp[i - (1 << j)] != -1) {
                dp[i] = dp[i - (1 << j)];
            }
        }
    }

    int rev = (1 << LIMIT) - 1;
    for (int i = 0; i < n; i++) {
        int rev_a = rev - a[i];
        cout << dp[rev_a] << ' ';
    }
    cout << endl;
    return 0;
}