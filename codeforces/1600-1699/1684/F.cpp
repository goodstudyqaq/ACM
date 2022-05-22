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
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> L(n + 1);
    for (int i = 1; i <= n; i++) {
        L[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        L[u] = max(L[u], v);
    }

    for (int i = 2; i <= n; i++) {
        L[i] = max(L[i], L[i - 1]);
    }

    map<int, vector<int>> M;
    for (int i = 1; i <= n; i++) {
        M[a[i]].push_back(i);
    }

    bool ok = true;
    int minR = -1, maxL = n + 10;

    vector<int> f(n + 1);
    for (int i = 1; i <= n; i++) {
        f[i] = i;
    }

    for (auto [key, V] : M) {
        // debug(key, V);
        int m = V.size();
        for (int i = 0; i < m - 1; i++) {
            int left = V[i], right = V[i + 1];
            if (L[left] >= right) {
                ok = false;
                minR = max(minR, left);
                maxL = min(maxL, right);
            }
        }
        int j = 0;
        for (int i = 0; i < m; i++) {
            int idx = V[i];
            while (j + 1 < m && L[idx] >= V[j + 1]) {
                j++;
            }
            if (i != j) {
                f[idx + 1] = max(f[idx + 1], V[j]);
            }
        }
    }

    if (ok) {
        cout << 0 << endl;
        return;
    }

    // debug(f);
    for (int i = 2; i <= n; i++) {
        f[i] = max(f[i], f[i - 1]);
    }
    // debug(minR, maxL);
    // debug(f);

    int ans = n;
    for (int l = 1; l <= maxL; l++) {
        ans = min(ans, max(minR, f[l]) - l + 1);
    }
    cout << ans << endl;
    debug(ans);
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