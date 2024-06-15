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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> r(k + 1), c(k + 1);
    map<int, int> M;
    map<int, int> Midx;

    for (int i = 1; i <= k; i++) {
        cin >> r[i] >> c[i];
        if (M[c[i]] < r[i]) {
            M[c[i]] = r[i];
            Midx[c[i]] = i;
        }
    }

    long long ans = 0;
    int row = 0;
    int last_cow = 1;

    vector<int> vis(k + 1);

    for (auto it : M) {
        int tmp = it.second;
        if (tmp > row) {
            ans += 1LL * (it.first - last_cow) * (n - row);

            int idx = Midx[it.first];
            vis[idx] = 1;

            last_cow = it.first;
            row = tmp;
        } 
    }
    ans += 1LL * (m - last_cow + 1) * (n - row);
    cout << ans << endl;

    for (int i = 1; i <= k; i++) {
        cout << vis[i] << ' ';
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