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
    int n, x;
    cin >> n >> x;
    vector<ll> a(n);
    map<ll, vector<int>> M;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        M[a[i]].push_back(i);
    }
    vector<bool> vis(n);
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (vis[i] == 0) {
            ll val = a[i];
            if (val % x) {
                ans++;
            } else {
                ll tmp = val / x;
                if (M[tmp].size() > 0) {
                    int idx2 = M[tmp].back();
                    vis[idx2] = 1;
                    M[tmp].pop_back();
                } else {
                    ans++;
                }
            }
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