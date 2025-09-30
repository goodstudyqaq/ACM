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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int l, r;
    for (int i = 0; i < n; i++) {
        if (a[i] == n) {
            l = i, r = i;
            break;
        }
    }

    int now = n - 1;
    while (now >= 1) {
        if (l - 1 >= 0 && a[l - 1] == now) {
            l--;
            now--;
            continue;
        }
        if (r + 1 < n && a[r + 1] == now) {
            r++;
            now--;
            continue;
        }
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
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