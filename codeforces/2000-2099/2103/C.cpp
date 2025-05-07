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
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    vector<int> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > k) {
            a[i] = -1;
        } else {
            a[i] = 1;
        }
    }

    auto check = [&]() {
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + a[i];
        }

        int small = 1e9;
        int first_idx = -1;
        for (int i = 1; i <= n; i++) {
            if (sum[i] >= 0) {
                if (first_idx == -1) first_idx = i;
                if (sum[i] >= small) {
                    return 1;
                }
                small = sum[i];
            }
        }
        if(first_idx == -1) {
            return 0;
        }

        for (int i = n; i >= 1; i--) {
            // [i, n]
            int _sum = sum[n] - sum[i - 1];
            if (_sum >= 0 && i > first_idx) {
                return 1;
            }
        }
        return 0;
    };

    if (check()) {
        cout << "YES\n";
        return;
    }
    for (int i = 1; i <= n / 2; i++) {
        swap(a[i], a[n + 1 - i]);
    }
    if(check()) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";

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