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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mx = *max_element(a.begin(), a.end());

    int mx_len = 1;

    int now = 0;
    while (now < n) {
        int go = now;
        while (go < n && a[go] != mx) go++;
        if (go == n) break;
        int go2 = go;
        while (go2 < n && a[go2] == mx) go2++;
        mx_len = max(mx_len, go2 - go);
        now = go2;
    }
    cout << mx_len << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}