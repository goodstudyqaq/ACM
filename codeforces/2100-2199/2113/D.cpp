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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<int> pre_min_b(n + 1);
    pre_min_b[0] = 1e9;
    for (int i = 1; i <= n; i++) {
        pre_min_b[i] = min(pre_min_b[i - 1], b[i]);
    }

    vector<int> suf_max_a(n + 2);
    for (int i = n; i >= 1; i--) {
        suf_max_a[i] = max(suf_max_a[i + 1], a[i]);
    }

    int min1 = 1e9, min2 = 1e9;
    // 最小值和次小值
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] < min2) {
            min2 = a[i];
        }
        if (min2 < min1) {
            swap(min1, min2);
        }

        if (min1 > pre_min_b[n - i + 1] || min(min2, suf_max_a[i + 1]) > pre_min_b[n - i + 1]) {
            ans = i;
        }
    }

    cout << ans << '\n';
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