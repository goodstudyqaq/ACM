#include <bits/stdc++.h>

#include <algorithm>

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
    vector<int> a(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    int mx = *max_element(a.begin(), a.end());
    int mi = *min_element(a.begin(), a.end());

    int times = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] - mi > k) {
            times++;
        }
    }
    if (times > 1) {
        cout << "Jerry\n";
        return;
    }

    if (abs(mx - 1 - mi) > k) {
        cout << "Jerry\n";
        return;
    }

    if (sum % 2) {
        cout << "Tom\n";
    } else {
        cout << "Jerry\n";
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
    return 0;
}