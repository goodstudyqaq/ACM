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

    int n;
    cin >> n;
    vector<vector<int>> V(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    ll ans = 0;
    vector<int> vis(2 * n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        vector<int> a;
        auto dfs = [&](auto self, int u) -> void {
            a.push_back(u);
            vis[u] = 1;
            for (auto v : V[u]) {
                if (vis[v] == 0) {
                    self(self, v);
                }
            }
        };
        dfs(dfs, i);
        debug(a);
        int ml = n, Ml = -1, mr = n, Mr = -1;
        int N = a.size();

        for (int j = 0; j < N; j++) {
            if (a[j] < n) {
                ml = min(ml, a[j]);
                Ml = max(Ml, a[j]);
            } else {
                mr = min(mr, a[j] - n);
                Mr = max(Mr, a[j] - n);
            }
        }
        debug(ml, Ml, mr, Mr);
        ans += 1LL * N / 2 * (ml + 1) * (n - Ml) * (mr + 1) * (n - Mr);
        debug(ans);

        for (int j = 0; j < N; j++) {
            int ml = n, Ml = -1, mr = n, Mr = -1;
            for (int k = 0; k < N; k++) {
                int val = a[(j + k) % N];
                if (val < n) {
                    ml = min(ml, val);
                    Ml = max(Ml, val);
                } else {
                    mr = min(mr, val - n);
                    Mr = max(Mr, val - n);
                }
                if (k % 2) {
                    int tmp = a[(j - 1 + N) % N];
                    debug(k, ml, Ml, mr, Mr, tmp);
                    int tmp_ml = ml, tmp_Ml = Ml;
                    int tmp_mr = mr, tmp_Mr = Mr;
                    if (tmp < n) {
                        swap(tmp_ml, tmp_mr);
                        swap(tmp_Ml, tmp_Mr);
                    } else {
                        tmp -= n;
                    }
                    if (tmp < tmp_mr) {
                        ans += 1LL * (tmp_ml + 1) * (n - tmp_Ml) * (tmp_mr - tmp) * (n - tmp_Mr);
                    }
                    if (tmp > tmp_Mr) {
                        ans += 1LL * (tmp_ml + 1) * (n - tmp_Ml) * (tmp_mr + 1) * (tmp - tmp_Mr);
                    }
                    debug(ans);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}