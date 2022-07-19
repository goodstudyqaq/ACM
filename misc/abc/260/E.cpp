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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(n + 1);
    vector<vector<pii>> V(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        V[a[i]].push_back({b[i], i});
        V[b[i]].push_back({a[i], i});
    }
    vector<ll> ans(m + 2);
    vector<int> vis(n + 1, 0);
    int now_vis = 0;
    int r = 1;

    for (int i = 1; i <= m; i++) {
        while (now_vis < n && r <= m) {
            for (auto v : V[r]) {
                if (vis[v.second] == 0) {
                    now_vis++;
                }
                vis[v.second]++;
            }
            r++;
        }
        if (now_vis == n) {
            int len = r - i;
            ans[len]++;
            len = m - i + 1;
            ans[len + 1]--;
        }
        for (auto v : V[i]) {
            vis[v.second]--;
            if (vis[v.second] == 0) {
                now_vis--;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        ans[i] += ans[i - 1];
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}