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
    if (n % 2 == 0) {
        cout << -1 << endl;
        return;
    }

    vector<int> a(n);
    a[n / 2] = 1;

    int l = n / 2 + 1;
    int r = n / 2 - 1;
    int now = 2;
    for (int i = 0; i < n / 2; i++) {
        a[l++] = now++;
        a[r--] = now++;
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
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