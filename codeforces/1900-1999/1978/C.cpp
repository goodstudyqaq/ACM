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
    long long n, k;
    cin >> n >> k;

    if (k % 2) {
        cout << "NO" << endl;
        return;
    }

    int lnow = 1;
    int rnow = n;
    vector<int> ans(n + 1);
    while (k) {
        if (lnow >= rnow) break;
        int val = rnow - lnow;
        if (k >= val * 2) {
            ans[lnow] = rnow;
            ans[rnow] = lnow;
            k -= val * 2;
            lnow++;
            rnow--;
        } else {
            ans[lnow] = lnow + k / 2;
            ans[lnow + k / 2] = lnow;
            k = 0;
            break;
        }
    }
    if (k) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0)
            cout << i << ' ';
        else {
            cout << ans[i] << ' ';
        }
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