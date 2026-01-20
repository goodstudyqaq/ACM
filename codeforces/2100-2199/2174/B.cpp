#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, l, r;
    cin >> n >> l >> r;

    int now = 1;
    vector<int> a(n + 1);
    vector<int> xor_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        if (i == r) {
            a[i] = xor_sum[r - 1] ^ xor_sum[l - 1];
        } else {
            a[i] = xor_sum[i - 1] ^ now;
            now++;
        }
        xor_sum[i] = xor_sum[i - 1] ^ a[i];
        cout << a[i] << ' ';
    }
    cout << '\n';
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