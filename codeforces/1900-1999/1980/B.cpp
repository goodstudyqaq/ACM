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
    int n, f, k;
    cin >> n >> f >> k;

    vector<int> a(n + 1);
    vector<int> cnt(101);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    for (int i = 99; i >= 1; i--) {
        cnt[i] += cnt[i + 1];
    }

    int val = a[f];

    if (cnt[val] <= k) {
        cout << "YES" << endl;
    } else if (cnt[val + 1] >= k) {
        cout << "NO" << endl;
    } else {
        cout << "MAYBE" << endl;
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