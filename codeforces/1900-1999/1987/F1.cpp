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
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    while (true) {
        int sz = a.size();
        if (sz <= 1) break;
        bool ok = false;
        for (int i = sz - 2; i >= 1; i--) {
            if (a[i] == i) {
                ans++;
                a.erase(a.begin() + i + 1);
                a.erase(a.begin() + i);
                ok = true;
                break;
            }
        }
        if (!ok) break;
    }
    cout << ans << endl;

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