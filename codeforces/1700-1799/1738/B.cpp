#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    vector<ll> sum(n + 1);
    for (int i = n - k + 1; i <= n; i++) {
        cin >> sum[i];
    }

    if (k == 1) {
        cout << "Yes" << endl;
        return;
    }

    vector<ll> a(n + 1);

    for (int i = n - k + 2; i <= n; i++) {
        a[i] = sum[i] - sum[i - 1];
    }

    for (int i = n - k + 2; i < n; i++) {
        if (a[i] > a[i + 1]) {
            cout << "No" << endl;
            return;
        }
    }

    // 后面的可以
    ll mi = a[n - k + 2];
    ll the_sum = sum[n - k + 1];
    ll the_num = n - k + 1;
    if (the_num * mi >= the_sum) {
        cout << "Yes" << endl;

    } else {
        cout << "No" << endl;
    }
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
}