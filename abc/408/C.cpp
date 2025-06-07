#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    vector<int> sum(n + 2);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        sum[l]++;
        sum[r + 1]--;
    }
    int mi = m;
    for (int i = 1; i <= n; i++) {
        sum[i] += sum[i - 1];
        mi = min(mi, sum[i]);
    }
    cout << mi << '\n';
}
