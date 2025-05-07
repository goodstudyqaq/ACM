#include <bits/stdc++.h>

#include <utility>

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
    vector<long long> a(n * 2);
    long long sum = 0;
    for (int i = 0; i < n * 2; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n * 2; i++) {
        if (i < n - 1) {
            sum -= a[i];
        } else {
            sum += a[i];
        }
    }

    cout << a[n * 2 - 1] << ' ' << sum << ' ';
    for (int i = 0; i < n - 1; i++) {
        cout << a[i + n] << ' ' << a[i] << ' ';
    }
    cout << a[n - 1];
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