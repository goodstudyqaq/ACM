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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    bool odd = false;
    int even = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] % 2) {
            odd = true;
        } else {
            even++;
        }
    }
    if (odd) {
        cout << even << endl;
        return;
    }

    int mi = 1e9;
    for (int i = 1; i <= n; i++) {
        int val = a[i];

        int cnt = 0;
        while (val % 2 == 0) {
            cnt++;
            val /= 2;
        }
        mi = min(mi, cnt);
    }
    cout << mi + n - 1 << endl;
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