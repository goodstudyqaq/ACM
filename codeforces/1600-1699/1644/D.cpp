#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    const int mod = 998244353;
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    typedef pair<int, int> pii;
    vector<pii> query(q + 1);
    for (int i = 1; i <= q; i++) {
        cin >> query[i].first >> query[i].second;
    }

    vector<bool> vis1(n + 1), vis2(m + 1);
    int cnt1 = 0, cnt2 = 0;
    long long ans = 1;
    for (int i = q; i >= 1; i--) {
        int r = query[i].first, c = query[i].second;

        bool flag = false;
        if (vis1[r] == 0 && cnt2 != m) {
            cnt1++;
            vis1[r] = 1;
            flag = true;
        }

        if (vis2[c] == 0 && cnt1 != n) {
            cnt2++;
            vis2[c] = 1;
            flag = true;
        }
        if (flag) {
            ans = ans * k % mod;
        }
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
}