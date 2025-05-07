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
    int n;
    cin >> n;
    vector<long long> a(n);
    vector<int> cnt(2);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i] % 2]++;
        sum += a[i] / 2 * 2;
    }
    debug(sum);
    if (cnt[0] == 0 || cnt[1] == 0) {
        cout << *max_element(a.begin(), a.end()) << '\n';
    } else {
        cout << sum + 1 << '\n';
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